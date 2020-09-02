# SLCrypt

## English branch
#### Description:
Class for encrypting and decrypting text using a key and an initialization vector.\
The size of the key and the initialization vector is equal `blockBytesLen`, by default it is 128 bytes.
#### How does it work:
* Encryption:
  * We split the string into blocks, each 128 bytes
  * Generate an initialization vector (random letters, 128 bytes)
  * For each byte of the string, we increment the byte\
    of the initialization vector and decrement the byte of the key
  * Add an initialization vector to the beginning of the string

* Decryption:
  * Split string and initialization vector (first 128 bytes)
  * We split the string into blocks, each 128 bytes
  * For each byte of string, we decrement the byte\
    of the initialization vector and increment the byte of the key
  
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
#### Example of usage \<PHP>:
```PHP
$slCrypt = new SLCrypt();
$key = "-128-bytes-key-";

// Of string encryption:
$out = $slCrypt->encryptString("string", $key);
print $out;

// Of string decryption:
$in = $slCrypt->encryptString($out, $key);
print $in;
```
___
## Russian branch
#### Описание:
Класс для шифрования и дешифрования текста с использованием ключа и вектора иницализации.\
Размер ключа и вектора инициализации равен `blockBytesLen`, по стандарту это 128 байт.
#### Принцип работы:
* Шифрования:
  * Разбиваем строку на блоки, каждый по 128 байт
  * Генерируем вектор инициализации (случайные буквы, 128 байт)
  * Каждому байту строки инкрементируем байт\
    вектора инициализации и декрементируем байт ключа 
  * Добавляем в начало строки вектор инициализации
  
* Дешифрования:
  * Разбиваем строку и вектор иницализации (первые 128 байт)
  * Разбиваем строку на блоки, каждый по 128 байт
  * Каждому байту строки декрементируем байт\
		вектора инициализации и инкрементируем байт ключа
#### Пример использования \<C++>:
```C++
SLCrypt slCrypt;
std::string key = "-128-bytes-key-";

// С шифрованием строки:
std::string out;
slCrypt.encryptString("string", key, out);
std::cout << "Encrypted string -> " << out << "\n";

// С дешифрованием строки:
std::string in;
slCrypt.encryptString(out, key, in);
std::cout << "Decrypted string -> " << in << "\n";
```
#### Пример использования \<PHP>:
```PHP
$slCrypt = new SLCrypt();
$key = "-128-bytes-key-";

// С шифрованием строки:
$out = $slCrypt->encryptString("string", $key);
print $out;

// С дешифрованием строки:
$in = $slCrypt->encryptString($out, $key);
print $in;
```
