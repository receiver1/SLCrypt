import datetime
import random
 
 
class SLCrypt:
    def __init__(self):
        self.blockBytesLen = 16
        self.ep = datetime.datetime(1970, 1, 1, 0, 0, 0)
        self.top = int.from_bytes("a".encode("cp1251"), "little")
        self.bot = int.from_bytes("z".encode("cp1251"), "little")
 
    def generate(self):
        OutStr = b""
        for i in range(self.blockBytesLen):
            random.seed()
            OutStr += random.randint(self.top, self.bot).to_bytes(1, "little")
        return OutStr
 
    def crypt(self, InStr, Key):
        in_byte = InStr.encode("cp1251")
        init_vector = self.generate()
        key_byte = Key.encode("cp1251")
        OutStr = b""
 
        paddingLength = len(in_byte) // self.blockBytesLen
 
        for a in range(paddingLength + 1):
            for b in range(self.blockBytesLen):
                if len(in_byte) > a * self.blockBytesLen + b:
                    OutStr += (in_byte[a * self.blockBytesLen + b] + init_vector[b] - key_byte[b]).to_bytes(1, "little")
 
        return (init_vector + OutStr).decode("cp1251")
 
    def decrypt(self, InStr, Key):
        inn = InStr.encode("cp1251")
        in_byte = inn[self.blockBytesLen:]
        init_vector = inn[0:self.blockBytesLen]
        key_byte = Key.encode("cp1251")
        OutStr = b""
 
        paddingLength = len(in_byte) // self.blockBytesLen
 
        for a in range(paddingLength + 1):
            for b in range(self.blockBytesLen):
                if len(in_byte) > a * self.blockBytesLen + b:
                    if in_byte[a * self.blockBytesLen + b] != 0x00:
                        OutStr += (in_byte[a * self.blockBytesLen + b] - init_vector[b] + key_byte[b]).to_bytes(1, "little")
        return OutStr
