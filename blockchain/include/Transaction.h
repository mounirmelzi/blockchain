#pragma once

#include "Wallet.h"
#include <string>

class Transaction
{
public:
	Transaction(Wallet& sender, Wallet& receiver, double amount);
	std::string hash() const;
	void commit();
	std::string toString() const;
	Wallet getSender() const;
	Wallet getReceiver() const;
	double getAmount() const;
private:
	Wallet& sender;
	Wallet& receiver;
	double amount;
	std::string timestamp;
};
