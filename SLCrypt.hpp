#pragma once

#include <string>
#include <vector>
#include <random>
#include <chrono>

class SLCrypt 
{
	public:
		void generateInitVector(std::vector<uint8_t> &out);
		void encryptString(std::string in, std::string key, std::string &out);
		void decryptString(std::string in, std::string key, std::string &out);

	private:
		uint8_t blockBytesLen = 16;
};