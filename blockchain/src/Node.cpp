#include "Node.h"
#include "Utils.h"
#include <random>
#include <limits>
#include <future>
#include <iostream>

Node::Node(Blockchain blockchain, Wallet wallet) : blockchain(blockchain), wallet(wallet) { }

void Node::send(Node& recipient, double amount)
{
	pendingTransactions.emplace_back(wallet, recipient.wallet, amount);
}

std::pair<Block, std::string> Node::broadcast(std::string previousHash)
{
	Block block(previousHash);
	for (const auto& transaction : pendingTransactions)
		block.addTransaction(transaction);
	pendingTransactions.clear();
	std::string signature = Utils::sign(wallet.getPrivateKey(), block.hash());
	return { block, signature };
}

bool Node::receive(Node sender, const Block& block, const std::string& signature)
{
	if (!Utils::verify(sender.getWallet().getPublicKey(), block.hash(), signature)) return false;
	if (!block.validate()) return false;
	return true;
}

Wallet Node::getWallet() const
{
	return wallet;
}

Block Node::mine(Block block)
{
	std::string target = "0";

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(1, std::numeric_limits<int>::max());

	while (true)
	{
		if (block.hash().substr(0, target.size()) == target)
		{
			return block;
		}
		else
		{
			block.setNonce(distribution(gen));
		}
	}
}

void Node::sync()
{
	std::promise<Node> nodePromise;
	std::promise<Block> blockPromise;

	auto [block, signature] = broadcast(blockchain.getLastBlock().hash());

	auto validate = [&](Node node) {
		if (!node.receive(*this, block, signature)) return false;
		try {
			blockPromise.set_value(node.mine(block));
			nodePromise.set_value(node);
		} catch (std::future_error) {}
		return true;
	};

	std::vector<std::future<bool>> futures;
	for (auto& node : nodes) {
		futures.push_back(std::async(std::launch::async, validate, node));
	}

	bool valid = true;
	for (auto& future : futures) {
		if (!future.get()) {
			valid = false;
			break;
		}
	}

	if (valid)
	{
		Node node = nodePromise.get_future().get();
		Block block = blockPromise.get_future().get();

		for (auto& node : nodes)
			node.blockchain.addBlock(block);
		block.commit();

		std::cout << " + block added by " << node.getWallet().getPublicKey() << std::endl;
	}
	else
	{
		std::cout << " ! block refused" << std::endl;
	}

	std::cout << std::endl;
	std::cout << blockchain.toString() << std::endl;
	std::cout << std::endl;
}

void Node::attack()
{
	std::promise<Node> nodePromise;
	std::promise<Block> blockPromise;

	auto [block, signature] = broadcast(blockchain.getLastBlock().hash());

	// simulate a fake transaction added by the attacker
	Wallet fake(1000.0);
	block.addTransaction(Transaction(fake, this->wallet, 1000.0));

	auto validate = [&](Node node) {
		if (!node.receive(*this, block, signature)) return false;
		try {
			blockPromise.set_value(node.mine(block));
			nodePromise.set_value(node);
		} catch (std::future_error) {}
		return true;
	};

	std::vector<std::future<bool>> futures;
	for (auto& node : nodes) {
		futures.push_back(std::async(std::launch::async, validate, node));
	}

	bool valid = true;
	for (auto& future : futures) {
		if (!future.get()) {
			valid = false;
			break;
		}
	}

	if (valid)
	{
		Node node = nodePromise.get_future().get();
		Block block = blockPromise.get_future().get();

		for (auto& node : nodes)
			node.blockchain.addBlock(block);
		block.commit();

		std::cout << " + block added by " << node.getWallet().getPublicKey() << std::endl;
	}
	else
	{
		std::cout << " ! block refused" << std::endl; // this should be printed in the terminal
	}
}
