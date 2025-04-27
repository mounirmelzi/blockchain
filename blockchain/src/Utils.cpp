#include "Utils.h"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

std::string Utils::hash(const std::string& data)
{
    SHA256 hash;
    std::string digest;
    StringSource ss(data, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    return digest;
}

std::pair<std::string, std::string> Utils::generateRSAKeyPair(unsigned int keySize)
{
    AutoSeededRandomPool rng;
    RSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, keySize);
    RSA::PublicKey publicKey(privateKey);

    std::string publicKeyStr, privateKeyStr;

    StringSink publicSink(publicKeyStr);
    publicKey.Save(publicSink);

    StringSink privateSink(privateKeyStr);
    privateKey.Save(privateSink);

    return { publicKeyStr, privateKeyStr };
}
