#include "Blockchain.h"
#include "Node.h"
#include <iostream>
#include <vector>
#include <future>
#include <mutex>

Blockchain blockchain;
constexpr int nodesSize = 4;

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
    auto [block, signature] = nodes[0].broadcast(blockchain.getLastBlock().hash());

    std::promise<Node> firstNodePromise;
    auto validate = [&](Node node) {
        bool result = node.receive(nodes[0], block, signature);

        // todo: mine the received block

        try { firstNodePromise.set_value(node); }
        catch (...) { }
        return result;
    };

    auto future1 = std::async(std::launch::async, validate, nodes[1]);
    auto future2 = std::async(std::launch::async, validate, nodes[2]);
    auto future3 = std::async(std::launch::async, validate, nodes[3]);

    bool validation1 = future1.get();
    bool validation2 = future2.get();
    bool validation3 = future3.get();

    if (validation1 && validation2 && validation3)
	{
        blockchain.addBlock(block);
        block.commit();

        std::cout << " + block added by " << firstNodePromise.get_future().get().getWallet().getPublicKey() << std::endl;
	}
    else
    {
        std::cout << "block refuse" << std::endl;
    }


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
