import hashlib
from hashlib import md5
from string import ascii_letters, digits
from itertools import permutations
from time import time

crypted = hashlib.md5()
message = input("明文：")

crypted.update(message.encode('utf-8'))
print(crypted.hexdigest())

data = ascii_letters + digits + '.,;'


# 本例中解密暂不可用，后续会在更新时修改
def decrypt(md5_value):
    if len(md5_value) != 32:
        print("长度错误!")
        return
    md5_value = md5_value.lower()
    for k in range(5, 10):
        for item in permutations(data, k):
            item = ''.join(item)
            print('.', end='')
            if md5(item.encode()).hexdigest() == md5_value:
                return item


md5_value = input()
start = time()
result = decrypt(md5_value)
if result:
    print('\n Success: ' + md5_value + '==>' + result)
print('计时：', time() - start)
