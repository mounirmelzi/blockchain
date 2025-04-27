#pragma once

#include <string>
#include <utility>

class Utils
{
public:
	static std::string hash(const std::string& data);
	static std::pair<std::string, std::string> generateRSAKeyPair(unsigned int keySize = 32);
};
