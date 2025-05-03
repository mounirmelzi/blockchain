#include "Wallet.h"
#include "Utils.h"
#include <sstream>

Wallet::Wallet(double balance)
	: balance(balance)
{
	auto [publicKey, privateKey] = Utils::generateRSAKeyPair();
	this->publicKey = publicKey;
	this->privateKey = privateKey;
}

std::string Wallet::toString() const
{
	std::ostringstream oss;
	oss << "=== Wallet (B) ===" << "\n"
		<< "Public Key: " << publicKey << "\n"
		<< "Private Key: [HIDDEN]" << "\n"
		<< "Balance: " << balance << " coins" << "\n"
		<< "Hash: " << hash() << "\n"
		<< "=== Wallet (E) ===";
	return oss.str();
}

std::string Wallet::getPublicKey() const
{	
	return publicKey;
}

std::string Wallet::getPrivateKey() const
{
	return privateKey;
}

double Wallet::getBalance() const
{
	return balance;
}

void Wallet::setBalance(double balance)
{
	this->balance = balance;
}

std::string Wallet::hash() const
{
	return Utils::hash(publicKey + privateKey + std::to_string(balance));
}
