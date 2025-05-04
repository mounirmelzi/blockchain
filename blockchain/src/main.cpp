#include "Blockchain.h"
#include "Node.h"
#include <iostream>
#include <vector>
#include <future>
#include <mutex>

Blockchain blockchain;
constexpr int nodesSize = 4;

static void sync(Node& sender, std::vector<Node>& nodes)
{
    std::promise<Node> nodePromise;
    std::promise<Block> blockPromise;

    auto [block, signature] = sender.broadcast(blockchain.getLastBlock().hash());

    auto validate = [&](Node node) {
        if (!node.receive(sender, block, signature)) return false;
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

    bool validation = true;
    for (auto& future : futures) {
        if (!future.get()) {
            validation = false;
            break;
        }
    }

    if (validation)
    {
        blockchain.addBlock(blockPromise.get_future().get());
        block.commit();

        std::cout << " + block added by " << nodePromise.get_future().get().getWallet().getPublicKey() << std::endl;
    }
    else
    {
        std::cout << "block refused" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    Wallet system(1000.0), genesis(0.0);
    Block genesisBlock("0");
    genesisBlock.addTransaction(Transaction(system, genesis, 100.0));
    if (genesisBlock.validate())
    {
        blockchain.addBlock(genesisBlock);
        genesisBlock.commit();
    }

    std::vector<Node> nodes;
    for (int i = 0; i < nodesSize; i++)
	{
		nodes.emplace_back(blockchain, Wallet(100.0));
        std::cout
            << " - Node " << i
            << ": Initial Balance = " << nodes[i].getWallet().getBalance() << " coins "
            << "(" << nodes[i].getWallet().getPublicKey() << ")"
            << std::endl;
	}

    std::cout << std::endl;

    nodes[0].send(nodes[1], 10.0);
    nodes[0].send(nodes[2], 20.0);
    sync(nodes[0], nodes);

    std::cout << std::endl;

    for (int i = 0; i < nodesSize; i++)
    {
        std::cout
            << " - Node " << i
            << ": Final Balance = " << nodes[i].getWallet().getBalance() << " coins "
            << "(" << nodes[i].getWallet().getPublicKey() << ")"
            << std::endl;
    }

    std::cout << std::endl;

    std::cout << blockchain.toString() << std::endl;

    return EXIT_SUCCESS;
}
