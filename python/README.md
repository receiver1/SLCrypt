# SLCrypt ![Deprecated](https://img.shields.io/badge/-Deprecated-critical)
#### Example of usage \<Python>:
```Python
slcrypt = SLCrypt()
 
KEY = "--SOME--KEY--"
 
# enryption
encrypted = slcrypt.crypt("string", KEY)
print(f"Encrypted string -> {encrypted}")
 
# decrypt
decrypted = slcrypt.decrypt(encrypted, KEY)
print(f"Decrypted string -> {decrypted}")

```
Thanks to KiN4StAt for this code!\
I'll leave his github here: www.github.com/kin4stat
