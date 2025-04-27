#pragma once

#include <string>

class Wallet
{
public:
	Wallet(double balance = 0.0);
	std::string getPublicKey() const;
	double getBalance() const;
	std::string hash() const;
public:
	std::string toString() const;
private:
	std::string publicKey;
	std::string privateKey;
	double balance;
};
