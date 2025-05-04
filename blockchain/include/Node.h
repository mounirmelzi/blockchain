#pragma once

#include "Wallet.h"
#include "Blockchain.h"
#include "Transaction.h"
#include "Block.h"
#include <vector>

class Node
{
public:
	Node(Blockchain blockchain, Wallet wallet);
	void send(Node& recipient, double amount);
	std::pair<Block, std::string> broadcast(std::string previousHash);
	bool receive(Node sender, const Block& block, const std::string& signature);
	Wallet getWallet() const;
	Block mine(Block block);
	void sync();
	void attack();
public:
	static inline std::vector<Node> nodes;
private:
	Blockchain blockchain;
	Wallet wallet;
	std::vector<Transaction> pendingTransactions;
};
