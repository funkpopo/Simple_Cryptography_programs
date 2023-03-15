import rsa


# rsa加密
def encrypt(str):
    # 生成公钥、私钥
    (pubkey, privkey) = rsa.newkeys(512)
    print("公钥:\n%s\n私钥:\n%s" % (pubkey, privkey))
    # 明文编码格式
    content = str.encode("utf-8")
    # 公钥加密
    crypto = rsa.encrypt(content, pubkey)
    return crypto, privkey


# rsa解密
def decrypt(str, pk):
    # 私钥解密
    content = rsa.decrypt(str, pk)
    con = content.decode("utf-8")
    return con


if __name__ == "__main__":
    str, pk = encrypt("Message~~~")
    print("密文:\n%s" % str)
    content = decrypt(str, pk)
    print("Message:\n%s" % rsa.decrypt(str, pk))
