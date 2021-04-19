## Hash函数

hash（散列、杂凑）函数，是将任意长度的数据映射到有限长度的域上。直观解释起来，就是对一串数据m进行杂糅，输出另一段固定长度的数据h，作为这段数据的特征（指纹），比如最简单的hash函数可以定义如下：
~~~~~ c
uinit_t hash(const void* input, uint32_t len){
    uint32_t h = 0;
    for(int i = 0; i < len; i ++){
        h = 32*h + (uint32_t)input[i];
    }
    return h;
}
~~~~~

## Murmur与其它的比较

* 常见的应用比较广的hash函数有MD5，SHA1，SHA256，一般用于信息安全方面，比如签名认证和加密等。比如我们传输文件时习惯用对原文件内容计算它的MD5值，生成128 bit的整数，通常我们说的32位MD5值，是转换为HEX格式后的32个字符。

* MurmurHash是2008年发明的，相比较MD5，MurMurhash不太安全（当然MD5也被破译了，sha也可以被破译），但是性能是MD5的几十倍；MurmurHash有很多个版本，MurmurHash3修复了MurmurHash2的一些缺陷同时速度还要快一些，因此很多开源项目有用，比如nginx、redis、memcashed、Hadoop等，比如用于计算一致性hash等。

* MurmurHash被比较好的测试过了，测试方法见[smhasher](https://github.com/aappleby/smhasher), MurMurhash的实现也可以参考smhasher，或者参考[MurmurHash2](https://sites.google.com/site/murmurhash)。他们的碰撞率（Conclusions）怎么样呢？可以参考John D.cook的证明：https://www.johndcook.com/blog/2017/01/10/probability-of-secure-hash-collisions/
现在摘抄一段：

```
So the probability of no collisions is exp(-1/2) or about 60%, which means there’s a 40% chance of at least one collision. As a rule of thumb, a hash function with range of size N can hash on the order of √N values before running into collisions.

This means that with a 64-bit hash function, there’s about a 40% chance of collisions when hashing 2^32 or about 4 billion items. If the output of the hash function is discernibly different from random, the probability of collisions may be higher. A 64-bit hash function cannot be secure since an attacker could easily hash 4 billion items.

```

也就是说MurMurhash的碰撞率不是2^N，而是2^(N/2)，N为hash的比特位数，如果是采用不同的随机种子数，那么碰撞的概率还要高，而且MurMur hash不是安全的。

* CityHash：在murmurhash的基础上又进一步优化了，但是比murmurhash略显复杂，对较长的字符串支持较好，实现详见：http://code.google.com/p/cityhash

## BloomFilter_x64实现

仿照Cassandra中的BloomFilter实现，Hash选用[MurmurHash2]，通过双重散列公式生成散列函数，参考：https://hur.st/bloomfilter/
~~~~~ c
  Hash(key, i) = (H1(key) + i * H2(key)) % m
~~~~~



BloomFilter使用例子，或者见main.cpp的实现
---------------------------------
~~~~~ cpp

#include "bloomfilter.h"
#include <stdio.h>


int main(int argc, char** argv){

    printf(" test bloomfilter\n");

    // 1. 定义BaseBloomFilter
    static BaseBloomFilter stBloomFilter = {0};

    // 2. 初始化stBloomFilter
    InitBloomFilter(&stBloomFilter, 0, 100000, 0.00001);

    // 3. 向BloomFilter中新增数值
    char url[128] = {0};
    for(int i = 0; i < 10000; i++){
        sprintf(url, "https://0voice.com/%d.html", i);
        if(0 == BloomFilter_Add(&stBloomFilter, (const void*)url, strlen(url))){
            // printf("add %s success", url);
        }else{
            printf("add %s failed", url);
        }
        memset(url, 0, sizeof(url));
    }

    // 4. check url exist or not
    char* str = "https://0voice.com/0.html";
    if (0 == BloomFilter_Check(&stBloomFilter, (const void*)str, strlen(str)) ){
        printf("https://0voice.com/0.html exist\n");
    }

    char* str2 = "https://0voice.com/10001.html";
    if (0 != BloomFilter_Check(&stBloomFilter, (const void*)str2, strlen(str2)) ){
          printf("https://0voice.com/10001.html not exist\n");
    }

    // 5. free bloomfilter
    FreeBloomFilter(&stBloomFilter);
    
    // (将生成好的BloomFilter写入文件:
    uint32_t ret = SaveBloomFilterToFile(&stBloomFilter, "dump.bin");
    
    // 从文件读取生成好的BloomFilter:
    ret = LoadBloomFilterFromFile(&stBloomFilter, "dump.bin");

    return 0;
}

~~~~~



