#pragma once

#include "Block.h"
#include <vector>

class Blockchain
{
public:
	void addBlock(const Block& newBlock);
public:
	std::string toString() const;
private:
	std::vector<Block> chain;
};
