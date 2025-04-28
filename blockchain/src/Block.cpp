#include "Block.h"
#include "Utils.h"
#include <chrono>
#include <ctime>
#include <sstream>

Block::Block(std::string previousHash)
	: previousHash(previousHash)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	timestamp = std::ctime(&now_time_t);
	timestamp.erase(timestamp.length() - 1);
}

std::string Block::toString() const
{
    std::ostringstream oss;
    oss << "==== Block (B) ====" << "\n"
        << "Previous Hash: " << previousHash << "\n"
        << "Timestamp: " << timestamp << "\n"
        << "Merkle Root: " << calculateMerkleTreeRootHash() << "\n"
        << "Block Hash: " << hash() << "\n"
        << "Transaction Count: " << transactions.size() << "\n";
    if (!transactions.empty()) {
        oss << "Transactions:\n";
        for (const auto& tx : transactions) {
            oss << tx.toString() << "\n";
        }
    }
    oss << "==== Block (E) ====";
    return oss.str();
}

std::string Block::hash() const
{
    return Utils::hash(previousHash + timestamp + calculateMerkleTreeRootHash());
}

void Block::addTransaction(const Transaction& transaction)
{
    transactions.push_back(transaction);
}

std::string Block::calculateMerkleTreeRootHash() const
{
    if (transactions.empty()) {
        return Utils::hash("empty");
    }

    std::vector<std::string> hashes;
    for (const auto& transaction : transactions) {
        hashes.push_back(transaction.hash());
    }

    while (hashes.size() > 1 && hashes.size() % 2 != 0) {
        hashes.push_back(hashes.back());
    }

    while (hashes.size() > 1) {
        std::vector<std::string> newLevel;
        for (size_t i = 0; i < hashes.size(); i += 2)
            newLevel.push_back(Utils::hash(hashes[i] + hashes[i + 1]));
        hashes = newLevel;
    }

    return hashes[0];
}
