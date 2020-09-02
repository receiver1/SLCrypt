
#include "SLCrypt.hpp"

void printHexArray(unsigned char a[], unsigned int n)
{
	for (unsigned int i = 0; i < n; i++) {
		printf("%02x ", a[i]);
	}
}

void SLCrypt::generateInitVector(std::vector<uint8_t> &out)
{
	out.clear();
	for (size_t i = 0; i < blockBytesLen; ++i) {
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937_64 mersenne(seed);
		std::uniform_int_distribution<int> distribution('a', 'z');
		out.push_back(static_cast<uint8_t>(distribution(mersenne)));
	}
	return;
}

void SLCrypt::encryptString(std::string in, std::string key, std::string &out)
{
	if (key.length() != blockBytesLen)
		throw "Key length != " + blockBytesLen;

	std::vector<uint8_t> in_byte(in.begin(), in.end()), 
		key_byte(key.begin(), key.end()), init_vector, encryptedBytes;

	this->generateInitVector(init_vector);

	size_t paddingLength = in_byte.size() / blockBytesLen;
	for (size_t a = 0; a <= paddingLength; ++a) {
		for (size_t b = 0; b < blockBytesLen; ++b) {
			if (in_byte.size() > a * blockBytesLen + b) {
				encryptedBytes.push_back(in_byte[a * blockBytesLen + b] + init_vector[b] - key_byte[b]);
			}
		}
	}

	out = std::string(reinterpret_cast<char*>(init_vector.data()), init_vector.size())
		+ std::string(reinterpret_cast<char*>(encryptedBytes.data()), encryptedBytes.size());
	return;
}

void SLCrypt::decryptString(std::string in, std::string key, std::string &out)
{
	if (key.length() != blockBytesLen)
		throw "Key length != " + blockBytesLen;

	std::string iv = in.substr(0, blockBytesLen);
	in = in.substr(blockBytesLen);

	std::vector<uint8_t> in_byte(in.begin(), in.end()),
		key_byte(key.begin(), key.end()), init_vector(iv.begin(), iv.end()), decryptedBytes;

	size_t paddingLength = in_byte.size() / blockBytesLen;
	for (size_t a = 0; a <= paddingLength; ++a) {
		for (size_t b = 0; b < blockBytesLen; ++b) {
			if (in_byte.size() > a * blockBytesLen + b) {
				if (in_byte[a * blockBytesLen + b] != 0x00) {
					decryptedBytes.push_back(in_byte[a * blockBytesLen + b] - init_vector[b] + key_byte[b]);
				}
			}
		}
	}

	out = std::string(reinterpret_cast<char*>(decryptedBytes.data()), decryptedBytes.size());
	return;
}
