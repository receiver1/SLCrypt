
#include "SLCrypt.hpp"

void SLCrypt::setBlockSize(std::size_t size)
{
	this->blockBytesLen = static_cast<uint8_t>(ceil(size / 8));
}

void SLCrypt::generateInitVector(std::vector<uint8_t> &out)
{
	out.clear();
	for (size_t i = 0; i < blockBytesLen; ++i) {
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937_64 mersenne(seed);
		std::uniform_int_distribution<int> distribution('A', 'z');
		out.push_back(static_cast<uint8_t>(distribution(mersenne)));
	}
	return;
}

void SLCrypt::Encryption<MODE_ECB>::encryptString(std::string in, std::string key, std::string &out)
{
	if (key.length() != blockBytesLen)
		throw "Key length != " + blockBytesLen;

	std::vector<uint8_t> inByte(in.begin(), in.end()), 
		key_byte(key.begin(), key.end()), initVector, encryptedBytes;

	this->generateInitVector(initVector);

	size_t paddingLength = inByte.size() / blockBytesLen;
	for (size_t a = 0; a <= paddingLength; ++a) {
		for (size_t b = 0; b < blockBytesLen; ++b) {
			if (inByte.size() > a * blockBytesLen + b) {
				encryptedBytes.push_back(inByte[a * blockBytesLen + b] + initVector[b] - key_byte[b]);
			}
		}
	}

	out = std::string(initVector.begin(), initVector.end());
	out += std::string(encryptedBytes.begin(), encryptedBytes.end());
	return;
}

void SLCrypt::Encryption<MODE_ECB>::decryptString(std::string in, std::string key, std::string &out)
{
	if (key.length() != blockBytesLen)
		throw "Key length != " + blockBytesLen;

	std::string iv = in.substr(0, blockBytesLen);
	in = in.substr(blockBytesLen);

	std::vector<uint8_t> inByte(in.begin(), in.end()),
		key_byte(key.begin(), key.end()), initVector(iv.begin(), iv.end()), decryptedBytes;

	size_t paddingLength = inByte.size() / blockBytesLen;
	for (size_t a = 0; a <= paddingLength; ++a) {
		for (size_t b = 0; b < blockBytesLen; ++b) {
			if (inByte.size() > a * blockBytesLen + b) {
				if (inByte[a * blockBytesLen + b] != 0x00) {
					decryptedBytes.push_back(inByte[a * blockBytesLen + b] - initVector[b] + key_byte[b]);
				}
			}
		}
	}

	out = std::string(decryptedBytes.begin(), decryptedBytes.end());
	return;
}


void SLCrypt::Encryption<MODE_CBC>::encryptString(std::string in, std::string key, std::string &out)
{
	if (key.length() != blockBytesLen)
		throw "Key length != " + blockBytesLen;

	std::vector<uint8_t> inByte(in.begin(), in.end()),
		key_byte(key.begin(), key.end()), initVector, encryptedBytes;

	this->generateInitVector(initVector);

	size_t paddingLength = inByte.size() / blockBytesLen;
	for (size_t a = 0; a <= paddingLength; ++a) {
		for (size_t b = 0; b < blockBytesLen; ++b) {
			if (inByte.size() > a * blockBytesLen + b) {
				uint8_t out_byte;
				if (encryptedBytes.size() < blockBytesLen) {
					out_byte = inByte[a * blockBytesLen + b] + initVector[b] - key_byte[b];
				}
				else {
					out_byte = inByte[a * blockBytesLen + b] + encryptedBytes[(a - 1) * blockBytesLen + b] - key_byte[b];
				}
				encryptedBytes.push_back(out_byte);
			}
		}
	}

	out = std::string(initVector.begin(), initVector.end());
	out += std::string(encryptedBytes.begin(), encryptedBytes.end());
	return;
}

void SLCrypt::Encryption<MODE_CBC>::decryptString(std::string in, std::string key, std::string &out)
{
	if (key.length() != blockBytesLen)
		throw "Key length != " + blockBytesLen;

	std::string iv = in.substr(0, blockBytesLen);
	in = in.substr(blockBytesLen);

	std::vector<uint8_t> inByte(in.begin(), in.end()),
		key_byte(key.begin(), key.end()), initVector(iv.begin(), iv.end()), decryptedBytes;

	size_t lastBlock = std::max<intptr_t>(inByte.size() - blockBytesLen, 0LL);
	size_t paddingLength = inByte.size() / blockBytesLen;
	for (size_t a = paddingLength; a != ~size_t(); --a) {
		for (size_t b = blockBytesLen; b != ~size_t() ; --b) {
			if (inByte.size() > a * blockBytesLen + b) {
				if (inByte[a * blockBytesLen + b] != 0x00) {
					uint8_t out_byte = 0x00;
					if (decryptedBytes.size() >= lastBlock) {
						if (a * blockBytesLen + b != 16) {
							out_byte = inByte[a * blockBytesLen + b] - initVector[b] + key_byte[b];
						}
					}
					else {
						out_byte = inByte[a * blockBytesLen + b] - inByte[(a - 1) * blockBytesLen + b] + key_byte[b];
					}

					if (out_byte != 0x00) {
						decryptedBytes.insert(decryptedBytes.begin(), 1, out_byte);
					}
				}
			}
		}
	}

	out = std::string(decryptedBytes.begin(), decryptedBytes.end());
	return;
}
