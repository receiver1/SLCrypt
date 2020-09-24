# SLCrypt
#### Example of usage \<C++>:
```C++
SLCrypt slCrypt;
std::string key = "-128-bytes-key-";

// Of string encryption:
std::string out;
slCrypt.encryptString("string", key, out);
std::cout << "Encrypted string -> " << out << "\n";

// Of string decryption:
std::string in;
slCrypt.encryptString(out, key, in);
std::cout << "Decrypted string -> " << in << "\n";
```
