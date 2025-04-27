#include "Blockchain.h"
#include <sstream>

std::string Blockchain::toString() const
{
    std::ostringstream oss;
    oss << "=== Blockchain ===" << "\n"
        << "Chain Height: " << chain.size() << "\n";
    if (!chain.empty()) {
        oss << "\nBlockchain Summary:\n";
        oss << "Genesis Block: " << chain[0].hash() << "\n";
        oss << "Last Block: " << chain.back().hash() << "\n";
        oss << "\nBlocks:\n";
        for (const auto& block : chain) {
            oss << block.toString() << "\n";
        }
    }
    oss << "===================";
    return oss.str();
}

void Blockchain::addBlock(const Block& newBlock)
{
	chain.push_back(newBlock);
}
