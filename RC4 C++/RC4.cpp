// RC4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string.h>
const int max_length = 256;
const int BOX_LEN = 256;
using namespace std;

/*把字节码转为十六进制码，一个字节两个十六进制，内部为字符串分配空间*/
char* ByteToHex(const unsigned char* Byte, const int Len)
{
	if (!Byte)
		return NULL;
	char* tmp = new char[Len * 2 + 1];
	int tmp2;
	for (int i = 0; i < Len; i++)
	{
		tmp2 = (int)(Byte[i]) / 16;
		tmp[i * 2] = (char)(tmp2 + ((tmp2 > 9) ? 'A' - 10 : '0'));
		tmp2 = (int)(Byte[i]) % 16;
		tmp[i * 2 + 1] = (char)(tmp2 + ((tmp2 > 9) ? 'A' - 10 : '0'));
	}
	tmp[Len * 2] = '\0';
	return tmp;
}

/*把十六进制字符串，转为字节码，每两个十六进制字符作为一个字节*/
unsigned char* HexToByte(const char* szHex)
{
	int length = strlen(szHex);
	unsigned char* pbBuf = new unsigned char[length / 2]; //数据缓冲区
	int tmp1, tmp2;
	for (int i = 0; i < length / 2; i++)
	{
		tmp1 = (int)szHex[i * 2] - (((int)szHex[i * 2] >= 'A') ? 'A' - 10 : '0');
		if (tmp1 >= 16)
			return NULL;
		tmp2 = (int)szHex[i * 2 + 1] - (((int)szHex[i * 2 + 1] >= 'A') ? 'A' - 10 : '0');
		if (tmp2 >= 16)
			return NULL;
		pbBuf[i] = (tmp1 * 16 + tmp2);
	}
	return pbBuf;
}

//交换
static void swap_byte(unsigned char* a, unsigned char* b)
{
	unsigned char swapByte;
	swapByte = *a;
	*a = *b;
	*b = swapByte;
}

int GetKey(const unsigned char* pass, int pass_len, unsigned char* out)
{
	int i;
	for (i = 0; i < BOX_LEN; i++)
	{
		out[i] = i;
	}
	int j = 0;
	for (i = 0; i < BOX_LEN; i++)
	{
		j = (pass[i % pass_len] + out[i] + j) % BOX_LEN;
		swap_byte(&out[i], &out[j]);
	}
	return -1;
}

int RC4(const unsigned char* data, int data_len, const unsigned char* key, int key_len, unsigned char* out, int* out_len)
{
	unsigned char* mBox = new unsigned char[BOX_LEN];
	int i = 0;
	int x = 0;
	int y = 0;
	for (int k = 0; k < data_len; k++)
	{
		x = (x + 1) % BOX_LEN;
		y = (mBox[x] + y) % BOX_LEN;
		swap_byte(&mBox[x], &mBox[y]);
		out[k] = data[k] ^ mBox[(mBox[x] + mBox[y]) % BOX_LEN];
	}
	*out_len = data_len;
	delete[] mBox;
	return -1;
}

/* 加密，返回加密结果*/
char* Encrypt(const char* szSource, const char* szPassWord)
{
	unsigned char* ret = new unsigned char[strlen(szSource)];
	int ret_len = 0;
	if (RC4((unsigned char*)szSource,strlen(szSource),(unsigned char*)szPassWord,strlen(szPassWord),ret,&ret_len) == NULL)
		return NULL;
	char* ret2 = ByteToHex(ret, ret_len);
	delete[] ret;
	return ret2;
}

/* 解密，返回解密结果*/
char* Decrypt(const char* szSource, const char* szPassWord)
{
	unsigned char* src = HexToByte(szSource);
	unsigned char* ret = new unsigned char[strlen(szSource) / 2 + 1];
	int ret_len = 0;
	memset(ret, strlen(szSource) / 2 + 1, 0);
	if (RC4(src, strlen(szSource) / 2, (unsigned char*)szPassWord, strlen(szPassWord), ret, &ret_len) == NULL)
		return NULL;
	ret[ret_len] = '\0';
	return (char*)ret;
}

int main(int argc, char* argv[])
{
	int size = 0;
	char *Message;//用户输入明文
	Message = (char*)malloc(1000);
	printf("请输入需要加密的信息：");
	scanf_s("%s", Message, strlen(Message));
	char Key[max_length];//密钥
	Key[0] = '\0';
	printf("\n请输入密钥：");
	scanf_s("%s", Key, strlen(Key));
	char* result1 = NULL;//加密、解密结果
	char* result2 = NULL;
	result1 = Encrypt(Message, Key);//加密
	printf("\n加密结果：%s\n", result1);
	result2 = Decrypt(result1, Key);//解密
	printf("\n解密结果：%s\n\n", result2);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
