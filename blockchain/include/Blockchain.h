#pragma once

#include "Block.h"
#include <vector>

class Blockchain
{
public:
	void addBlock(const Block& newBlock);
	std::string toString() const;
	Block getLastBlock() const;
private:
	std::vector<Block> chain;
};
