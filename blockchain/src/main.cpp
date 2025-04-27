#include "Blockchain.h"
#include <iostream>

int main() 
{
    Wallet system(9999.99), genesis(0.0);
    Blockchain blockchain;

    Block block1("");
    block1.addTransaction(Transaction(system, genesis, 100.0));
    blockchain.addBlock(block1);

    Block block2(block1.hash());
    block2.addTransaction(Transaction(genesis, system, 50.0));
    block2.addTransaction(Transaction(system, genesis, 99.99));
    blockchain.addBlock(block2);

    std::cout << blockchain.toString() << std::endl;
    return EXIT_SUCCESS;
}
