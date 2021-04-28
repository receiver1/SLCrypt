#include <iostream>

#include "SLCrypt.hpp"

/*
* Output: "> Invalid encryptions: 0"
*/
int main()
{
    std::string strInput = "Hello world!";
    std::string strKey = "1234567890123456";
    std::string strOutput;

    SLCrypt::Encryption<MODE_ECB> crypt;
    crypt.setBlockSize(128);

    size_t invalidCount = 0;
    for (size_t i = 0; i < 0xFFFF; ++i)
    {
        crypt.encryptString(strInput, strKey, strOutput);
        crypt.decryptString(strOutput, strKey, strOutput);

        if (strOutput != strInput) {
            ++ invalidCount;
        }
    }
    std::cout << "> Invalid encryptions: " << invalidCount << std::endl;

    system("pause");
}
