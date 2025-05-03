#pragma once

#include "Transaction.h"
#include <string>
#include <vector>

class Block
{
public:
	Block(std::string previousHash);
	std::string hash() const;
	void addTransaction(const Transaction& transaction);
	bool validate() const;
	void commit();
	std::string toString() const;
	void setNonce(int nonce);
private:
	std::string calculateMerkleTreeRootHash() const;
private:
	std::vector<Transaction> transactions;
	std::string timestamp;
	std::string previousHash;
	int nonce;
};
