import base64
import hashlib


# 默认为UTF-8
class rc4:
    def __init__(self, public_key=None):
        self.public_key = public_key or 'none_public_key'

    def encode(self, string):
        bData = [ord(i) for i in string]
        result = self.__docrypt(bData)
        result = base64.b64encode(result.encode())  # 编码成可见的字符
        return str(result, encoding='utf-8')

    def decode(self, string):
        message = base64.b64decode(string).decode()
        bData = [ord(i) for i in message]
        deresult = self.__docrypt(bData)
        return deresult

    def __rc4_init(self, K):
        j = 0
        K = hashlib.md5(K.encode("utf8")).hexdigest()
        k = []  # 临时数组
        SBox = []  # S盒
        for i in range(256):
            SBox.append(i)
            k.append(K[i % len(K)])  # T[i] = K[ i mod keylen ];
        for i in range(256):
            j = (j + SBox[i] + ord(k[i])) % 256
            SBox[i], SBox[j] = SBox[j], SBox[i]  # 交换S[i],S[j]
        return SBox

    def __docrypt(self, string):
        i = j = 0
        result = ''
        SBox = self.__rc4_init(self.public_key)
        for _str in string:
            i = (i + 1) % 256
            j = (j + SBox[i]) % 256
            SBox[i], SBox[j] = SBox[j], SBox[i]
            k = chr(_str ^ SBox[(SBox[i] + SBox[j]) % 256])
            result += k
        return result


print("Input Key:")
key = input()
_rc4 = rc4(key)
print("Input Message:")
message_s = input()
tempcode = _rc4.encode(message_s)
print("加密结果", tempcode)
tempdecode = _rc4.decode(tempcode)
print("解密结果", tempdecode)
