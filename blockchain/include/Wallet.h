#pragma once

#include <string>

class Wallet
{
public:
	Wallet(double balance = 0.0);
	std::string getPublicKey() const;
	std::string getPrivateKey() const;
	double getBalance() const;
	void setBalance(double balance);
	std::string hash() const;
	std::string toString() const;
private:
	std::string publicKey;
	std::string privateKey;
	double balance;
};
