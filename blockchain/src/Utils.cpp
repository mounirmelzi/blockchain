#include "Utils.h"
#include <string>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include "cryptopp/base64.h"
#include "cryptopp/filters.h"
#include "cryptopp/pssr.h"

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

std::string Utils::sign(const std::string& privateKeyBase64, const std::string& data) {
    std::string privateKeyBin;
    StringSource(privateKeyBase64, true, new Base64Decoder(new StringSink(privateKeyBin)));

    RSA::PrivateKey privateKey;
    StringSource privKeySource(privateKeyBin, true);
    privateKey.Load(privKeySource);

    AutoSeededRandomPool rng;
    RSASS<PSS, SHA256>::Signer signer(privateKey);
    std::string signature;
    StringSource(data, true, new SignerFilter(rng, signer, new StringSink(signature)));

    std::string encodedSignature;
    StringSource(signature, true, new Base64Encoder(new StringSink(encodedSignature), false));

    return encodedSignature;
}

bool Utils::verify(const std::string& publicKeyBase64, const std::string& data, const std::string& signatureBase64) {
    std::string publicKeyBin;
    StringSource(publicKeyBase64, true, new Base64Decoder(new StringSink(publicKeyBin)));
   
    RSA::PublicKey publicKey;
    StringSource pubKeySource(publicKeyBin, true);
    publicKey.Load(pubKeySource);

    std::string signature;
    StringSource(signatureBase64, true, new Base64Decoder(new StringSink(signature)));

    RSASS<PSS, SHA256>::Verifier verifier(publicKey);
    bool result = false;
    StringSource(data + signature, true, new SignatureVerificationFilter(verifier, new ArraySink((byte*)&result, sizeof(result)), SignatureVerificationFilter::PUT_RESULT|SignatureVerificationFilter::SIGNATURE_AT_END));

    return result;
}
