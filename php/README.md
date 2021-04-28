# SLCrypt ![Deprecated](https://img.shields.io/badge/-Deprecated-critical)
#### Example of usage \<PHP>:
```PHP
$slCrypt = new SLCrypt();
$key = "-128-bits-key-";

// Of string encryption:
$out = $slCrypt->encryptString("string", $key);
print $out;

// Of string decryption:
$in = $slCrypt->encryptString($out, $key);
print $in;
```
