// RSA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;


int Message[100];//明文
long long Cipher[100];//密文
int n, e = 0, d;

//二进制转换
int H2B(int num, int bin_num[])
{

    int i = 0, mod = 0;

    //转换为二进制，逆向暂存temp[]数组中
    while (num != 0)
    {
        mod = num % 2;
        bin_num[i] = mod;
        num = num / 2;
        i++;
    }

    //返回二进制数的位数
    return i;
}

//反复平方求幂
long long Modular(long long a, int b, int n)
{
    int c = 0, bin_num[1000];
    long long d = 1;
    int k = H2B(b, bin_num) - 1;

    for (int i = k; i >= 0; i--)
    {
        c = 2 * c;
        d = (d * d) % n;
        if (bin_num[i] == 1)
        {
            c = c + 1;
            d = (d * a) % n;
        }
    }
    return d;
}

//生成1000以内素数
int Produce(int prime[])
{
    int c = 0, vis[1001];
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= 1000; i++)if (!vis[i])
    {
        prime[c++] = i;
        for (int j = i * i; j <= 1000; j += i)
            vis[j] = 1;
    }

    return c;
}

//欧几里得扩展算法
int Expand(int m, int n, int& x)
{
    int x1, y1, x0, y0, y;
    x0 = 1; y0 = 0;
    x1 = 0; y1 = 1;
    x = 0; y = 1;
    int r = m % n;
    int q = (m - r) / n;
    while (r)
    {
        x = x0 - q * x1; y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        m = n; n = r; r = m % n;
        q = (m - r) / n;
    }
    return n;
}

//RSA初始化
void RSA()
{
    //取出1000内素数保存在prime[]数组中
    int prime[5000];
    int count_Prime = Produce(prime);

    //随机取两个素数p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand() % count_Prime;
    int ranNum2 = rand() % count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];

    n = p * q;

    int On = (p - 1) * (q - 1);


    //用欧几里德扩展算法求e,d
    for (int j = 3; j < On; j += 1331)
    {
        int gcd = Expand(j, On, d);
        if (gcd == 1 && d > 0)
        {
            e = j;
            break;
        }
    }
}

//RSA加密
void RSA_Encrypt()
{
    cout << "公钥 (e, n) : e = " << e << " n = " << n << '\n';
    cout << "私钥 (d, n) : d = " << d << " n = " << n << '\n' << '\n';

    int i = 0;
    for (i = 0; i < 100; i++)
        Cipher[i] = Modular(Message[i], e, n);

    cout << "使用公钥（e,n）加密:" << '\n';
    for (i = 0; i < 100; i++)
        cout << Cipher[i] << " ";
    cout << '\n' << '\n';
}

//RSA解密
void RSA_Decrypt()
{
    int i = 0;
    for (i = 0; i < 100; i++)
        Cipher[i] = Modular(Cipher[i], d, n);

    cout << "私钥（d,n）解密:" << '\n';
    for (i = 0; i < 100; i++)
        cout << Cipher[i] << " ";
    cout << '\n' << '\n';
}

//算法初始化
void Initialize()
{
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < 100; i++)
        Message[i] = rand() % 1000;

    cout << "生成100个随机数:" << '\n';
    for (i = 0; i < 100; i++)
        cout << Message[i] << " ";
    cout << '\n' << '\n';
}

int main()
{
    Initialize();
    while (!e)
    {
        RSA();
    }
    RSA_Encrypt();
    RSA_Decrypt();
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
