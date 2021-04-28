#pragma once

#include <string>
#include <vector>
#include <random>
#include <chrono>

enum eMode
{
	MODE_ECB,
	MODE_CBC
};

class SLCrypt
{
	uint8_t blockBytesLen = 16;
public:
	void setBlockSize(std::size_t size);
	void generateInitVector(std::vector<uint8_t> &out);
	template<eMode T> class Encryption;
};

template<eMode T>
class SLCrypt::Encryption : public SLCrypt
{
public:
	void encryptString(std::string in, std::string key, std::string &out);
	void decryptString(std::string in, std::string key, std::string &out);
};
