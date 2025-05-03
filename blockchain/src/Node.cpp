#include "Node.h"
#include "Utils.h"

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
