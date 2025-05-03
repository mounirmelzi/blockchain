#pragma once

#include <string>
#include <utility>

class Utils
{
public:
	static std::string hash(const std::string& data);
	static std::pair<std::string, std::string> generateRSAKeyPair(unsigned int keySize = 1024);
	static std::string sign(const std::string& privateKeyBase64, const std::string& data);
	static bool verify(const std::string& publicKeyBase64, const std::string& data, const std::string& signatureBase64);
};
