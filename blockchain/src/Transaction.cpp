#include "Transaction.h"
#include "Utils.h"
#include <chrono>
#include <ctime>
#include <sstream>

Transaction::Transaction(Wallet& sender, Wallet& receiver, double amount)
	: sender(sender), receiver(receiver), amount(amount)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	timestamp = std::ctime(&now_time_t);
	timestamp.erase(timestamp.length() - 1);
}

std::string Transaction::toString() const
{
    std::ostringstream oss;
    oss << "=== Transaction (B) ===" << "\n"
        << "  - Sender: " << sender.getPublicKey() << "\n"
        << "  - Receiver: " << receiver.getPublicKey() << "\n"
        << "  - Amount: " << amount << " coins" << "\n"
        << "  - Timestamp: " << timestamp << "\n"
        << "  - Hash: " << hash() << "\n"
        << "=== Transaction (E) ===";
    return oss.str();
}

Wallet Transaction::getSender() const
{
    return sender;
}

Wallet Transaction::getReceiver() const
{
    return receiver;
}

double Transaction::getAmount() const
{
    return amount;
}

std::string Transaction::hash() const
{
	return Utils::hash(sender.hash() + receiver.hash() + std::to_string(amount) + timestamp);
}

void Transaction::commit()
{
    sender.setBalance(sender.getBalance() - amount);
    receiver.setBalance(receiver.getBalance() + amount);
}
