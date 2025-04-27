#pragma once

#include "Wallet.h"
#include <string>

class Transaction
{
public:
	Transaction(Wallet sender, Wallet receiver, double amount);
	std::string hash() const;
public:
	std::string toString() const;
private:
	Wallet sender;
	Wallet receiver;
	double amount;
	std::string timestamp;
};
