# SLCrypt \<Pawn\>
#### Example of usage:
```C++
native slCrypt_encryptString(input[], key[], out[]);
native slCrypt_decryptString(input[], key[], out[]);

// Somewhere in function...
new key[16] = "-128-bytes-key-";

// Of string encryption:
new out[128];
slCrypt_encryptString("string", key, out);
printf("Encrypted string -> %s", out);

// Of string decryption:
new in[128];
slCrypt_decryptString(out, key, in);
printf("Decrypted string -> %s", in);
```
___
