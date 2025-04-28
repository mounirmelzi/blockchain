#include "Utils.h"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include "cryptopp/base64.h"

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

    std::string publicKeyBin, privateKeyBin;
    std::string publicKeyBase64, privateKeyBase64;

    StringSink publicSink(publicKeyBin);
    publicKey.Save(publicSink);
    StringSource(publicKeyBin, true, new Base64Encoder(new StringSink(publicKeyBase64), false));
    
    StringSink privateSink(privateKeyBin);
    privateKey.Save(privateSink);
    StringSource(privateKeyBin, true, new Base64Encoder(new StringSink(privateKeyBase64), false));

    return { publicKeyBase64, privateKeyBase64 };
}
