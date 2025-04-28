#include "Blockchain.h"
#include <sstream>

std::string Blockchain::toString() const
{
    std::ostringstream oss;
    oss << "==== Blockchain (B) ====" << "\n"
        << "Chain Length: " << chain.size() << "\n";
    if (!chain.empty()) {
        oss << "\nBlockchain Summary:\n";
        oss << "Genesis Block: " << chain[0].hash() << "\n";
        oss << "Last Block: " << chain.back().hash() << "\n";
        for (const auto& block : chain) {
            oss << "\n" << block.toString() << "\n";
        }
    }
    oss << "==== Blockchain (E) ====";
    return oss.str();
}

void Blockchain::addBlock(const Block& newBlock)
{
	chain.push_back(newBlock);
}
