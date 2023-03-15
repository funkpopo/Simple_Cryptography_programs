from Cryptodome.Cipher import DES
import binascii

# 密钥
key = b"abcdefgh"  # key需为8字节长度.
# 需要去生成一个DES对象.
des = DES.new(key, DES.MODE_ECB)

# 需要加密的数据
text = "this is python message string"  # 被加密的数据需要为8字节的倍数.
text = text + (8 - (len(text) % 8)) * '='  # 用=填充.
print("下为Message，用户自定义，可改写为即时输入加密/解密")
print(text)

print("\n")

# 加密
# 去除注释后为ASCII格式数据
encrypto_text = des.encrypt(text.encode())
# encrypto_text = binascii.b2a_hex(encrypto_text)
print("密文")
print(encrypto_text)

print("\n")

decrrpto_text = des.decrypt(encrypto_text)
# decrrpto_text = binascii.b2a_hex(decrrpto_text)
print("明文")
print(decrrpto_text)
