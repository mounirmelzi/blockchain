#include "Node.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Blockchain blockchain;
    Wallet system(1000.0), genesis(0.0);
    Block genesisBlock("0");
    genesisBlock.addTransaction(Transaction(system, genesis, 100.0));
    if (genesisBlock.validate())
    {
        blockchain.addBlock(genesisBlock);
        genesisBlock.commit();
    }

    for (int i = 0; i < 4; i++)
	{
        Node::nodes.emplace_back(blockchain, Wallet(100.0));
        std::cout
            << " - Node " << i
            << ": Initial Balance = " << Node::nodes[i].getWallet().getBalance() << " coins "
            << "(" << Node::nodes[i].getWallet().getPublicKey() << ")"
            << std::endl;
	}

    std::cout << std::endl;

    Node::nodes[0].send(Node::nodes[1], 10.0);
    Node::nodes[0].send(Node::nodes[2], 20.0);
    Node::nodes[0].sync();

    std::cout << std::endl;

    Node::nodes[0].attack();

    std::cout << std::endl;

    for (int i = 0; i < Node::nodes.size(); i++)
    {
        std::cout
            << " - Node " << i
            << ": Final Balance = " << Node::nodes[i].getWallet().getBalance() << " coins "
            << "(" << Node::nodes[i].getWallet().getPublicKey() << ")"
            << std::endl;
    }

    return EXIT_SUCCESS;
}
