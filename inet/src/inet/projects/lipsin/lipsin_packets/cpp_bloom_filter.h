#ifndef __MICRO_BLOOMFILTER_H__ // NOLINT
#define __MICRO_BLOOMFILTER_H__ // NOLINT

/**
 *
 *  仿照Cassandra中的BloomFilter实现，Hash选用MurmurHash2，通过双重散列公式生成散列函数，参考：http://hur.st/bloomfilter
 *    Hash(key, i) = (H1(key) + i * H2(key)) % m
 *
**/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <sstream>
namespace inet {
#define __BLOOMFILTER_VERSION__ "1.1" // NOLINT
#define __MGAIC_CODE__          (0x01464C42) // NOLINT

/**
 *  BloomFilter使用例子：
 *  static CppBloomFilter stBloomFilter = {0};
 *
 *  初始化BloomFilter(最大100000元素，不超过0.00001的错误率)：
 *      InitBloomFilter(&stBloomFilter, 0, 100000, 0.00001);
 *  重置BloomFilter：
 *      ResetBloomFilter(&stBloomFilter);
 *  释放BloomFilter:
 *      FreeBloomFilter(&stBloomFilter);
 *
 *  向BloomFilter中新增一个数值（0-正常，1-加入数值过多）：
 *      uint32_t dwValue;
 *      iRet = BloomFilter_Add(&stBloomFilter, &dwValue, sizeof(uint32_t));
 *  检查数值是否在BloomFilter内（0-存在，1-不存在）：
 *      iRet = BloomFilter_Check(&stBloomFilter, &dwValue, sizeof(uint32_t));
 *
 *  (1.1新增) 将生成好的BloomFilter写入文件:
 *      iRet = SaveBloomFilterToFile(&stBloomFilter, "dump.bin")
 *  (1.1新增) 从文件读取生成好的BloomFilter:
 *      iRet = LoadBloomFilterFromFile(&stBloomFilter, "dump.bin")
**/

// 注意，要让Add/Check函数内联，必须使用 -O2 或以上的优化等级
#define FORCE_INLINE __attribute__((always_inline))

#define BYTE_BITS           (8)
#define MIX_UINT64(v)       ((uint32_t)((v>>32)^(v)))

#define SETBIT(filter, n)   (filter->pstFilter[n/BYTE_BITS] |= (1 << (n%BYTE_BITS)))
#define GETBIT(filter, n)   (filter->pstFilter[n/BYTE_BITS] & (1 << (n%BYTE_BITS)))

// BloomFilter结构定义
    typedef struct {
        uint8_t cInitFlag;                              // 初始化标志，为0时的第一次Add()会对stFilter[]做初始化
        uint8_t cResv[3];

        uint32_t dwFilterBits;                          // m =  ; - BloomFilter的比特数
        uint32_t dwHashFuncs;                           // k = round(log(2.0) * m / n); - 哈希函数个数

        uint32_t dwSeed;                                // MurmurHash的种子偏移量
        uint32_t dwCount;                               // Add()的计数，超过MAX_BLOOMFILTER_N则返回失败

        uint32_t dwFilterSize;                          // dwFilterBits / BYTE_BITS
        unsigned char *pstFilter;                       // BloomFilter存储指针，使用malloc分配
        uint32_t *pdwHashPos;                           // 存储上次hash得到的K个bit位置数组(由bloom_hash填充)
    } CppBloomFilter;


#pragma pack()

    inline int InitBloomFilterWithMandK(CppBloomFilter *pstBloomfilter, uint32_t dwSeed, uint32_t filterBits,
                                        uint32_t numHashFuncs) {
        if (pstBloomfilter == nullptr)
            return -1;
        // 初始化结构体
        memset(pstBloomfilter, 0, sizeof(CppBloomFilter));
        // 初始化内存结构，并计算BloomFilter需要的空间
        pstBloomfilter->dwSeed = dwSeed;      // hash种子
        pstBloomfilter->dwFilterBits = filterBits; // m
        pstBloomfilter->dwHashFuncs = numHashFuncs; // k
        // 设置大小
        if(pstBloomfilter->dwFilterBits % BYTE_BITS == 0){
            pstBloomfilter->dwFilterSize = pstBloomfilter->dwFilterBits / BYTE_BITS;
        } else{
            pstBloomfilter->dwFilterSize = pstBloomfilter->dwFilterBits / BYTE_BITS + 1;
        }
        // 进行存储空间的分配
        pstBloomfilter->pstFilter = (unsigned char *) malloc(pstBloomfilter->dwFilterSize);
        // 如果存储空间分配失败则返回错误
        if (nullptr == pstBloomfilter->pstFilter)
            return -100;
        // 哈希结果数组，每个哈希函数对应数组上的一个元素。
        pstBloomfilter->pdwHashPos = (uint32_t *) malloc(pstBloomfilter->dwHashFuncs * sizeof(uint32_t));
        // 如果分配失败则返回空
        if (nullptr == pstBloomfilter->pdwHashPos)
            return -200;
        // 初始化BloomFilter的内存
        memset(pstBloomfilter->pstFilter, 0, pstBloomfilter->dwFilterSize);
        // 代表已经初始化完成了
        pstBloomfilter->cInitFlag = 1;
        return 0;
    }

    inline CppBloomFilter *NewBloomFilter(CppBloomFilter *pstBloomFilter) {
        if (pstBloomFilter == nullptr)
            return nullptr;
        // get the filter bits and hash functions
        auto *newBloomFilter = new CppBloomFilter;
        InitBloomFilterWithMandK(newBloomFilter, 0, pstBloomFilter->dwFilterBits, pstBloomFilter->dwHashFuncs);
        memcpy(newBloomFilter->pstFilter, pstBloomFilter->pstFilter, pstBloomFilter->dwFilterSize);
        memcpy(newBloomFilter->pdwHashPos, pstBloomFilter->pdwHashPos, pstBloomFilter->dwHashFuncs * sizeof(uint32_t));
        newBloomFilter->dwCount = pstBloomFilter->dwCount;
        newBloomFilter->dwSeed = pstBloomFilter->dwSeed;
        return newBloomFilter;
    }

/**
 * @brief 释放布隆过滤器
 * @param pstBloomfilter 要释放的布隆过滤器
 * @return 返回值
 */
    inline int FreeBloomFilter(CppBloomFilter *pstBloomfilter) {
        // 如果要释放的布隆过滤器为空返回-1错误代码
        if (pstBloomfilter == nullptr)
            return -1;
        // 将布隆过滤器的初始化标志置为0
        pstBloomfilter->cInitFlag = 0;
        // 将布隆过滤器的计数置为0
        pstBloomfilter->dwCount = 0;
        // 进行布隆过滤器内存释放
        free(pstBloomfilter->pstFilter);
        // 将布隆过滤器的指针置为空
        pstBloomfilter->pstFilter = nullptr;
        // 进行哈希结果数组的释放
        free(pstBloomfilter->pdwHashPos);
        // 将哈希结果数组的指针置为空
        pstBloomfilter->pdwHashPos = nullptr;
        return 0;
    }

/**
 * @brief 重置布隆过滤器 注意: Reset()函数不会立即初始化stFilter，而是当一次Add()时去memset
 * @param pstBloomfilter
 * @return
 */
    inline int ResetBloomFilter(CppBloomFilter *pstBloomfilter) {
        // 如果要重制的布隆过滤器为空返回-1错误代码
        if (pstBloomfilter == nullptr)
            return -1;

        pstBloomfilter->cInitFlag = 0;
        pstBloomfilter->dwCount = 0;
        return 0;
    }

// 和ResetBloomFilter不同，调用后立即memset内存
    inline int RealResetBloomFilter(CppBloomFilter *pstBloomfilter) {
        // 如果要重制的布隆过滤器为空返回-1错误代码
        if (pstBloomfilter == nullptr)
            return -1;

        memset(pstBloomfilter->pstFilter, 0, pstBloomfilter->dwFilterSize);
        pstBloomfilter->cInitFlag = 1;
        pstBloomfilter->dwCount = 0;
        return 0;
    }

/**
 * @brief 哈希函数
 * @param key   要进行哈希的数据
 * @param len   要进行哈希的数据的长度
 * @param seed  哈希种子
 * @return
 */
    FORCE_INLINE uint64_t MurmurHash2_x64(const void *key, int len, uint32_t seed) {
        const uint64_t m = 0xc6a4a7935bd1e995;
        const int r = 47;

        uint64_t h = seed ^ (len * m);

        const auto *data = (const uint64_t *) key;
        const uint64_t *end = data + (len / 8);

        while (data != end) {
            uint64_t k = *data++;

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        const auto *data2 = (const uint8_t *) data;

        switch (len & 7) {
            case 7:
                h ^= ((uint64_t) data2[6]) << 48;
            case 6:
                h ^= ((uint64_t) data2[5]) << 40;
            case 5:
                h ^= ((uint64_t) data2[4]) << 32;
            case 4:
                h ^= ((uint64_t) data2[3]) << 24;
            case 3:
                h ^= ((uint64_t) data2[2]) << 16;
            case 2:
                h ^= ((uint64_t) data2[1]) << 8;
            case 1:
                h ^= ((uint64_t) data2[0]);
                h *= m;
        };

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
    }

/**
 * @brief 计算哈希值
 * @param pstBloomfilter  布隆过滤器
 * @param key  要进行哈希的数据
 * @param len  要进行哈希的数据的长度
 */
    FORCE_INLINE void bloom_hash(CppBloomFilter *pstBloomfilter, const void *key, int len) {
        int i;
        uint32_t dwFilterBits = pstBloomfilter->dwFilterBits;
        uint64_t hash1 = MurmurHash2_x64(key, len, pstBloomfilter->dwSeed);
        uint64_t hash2 = MurmurHash2_x64(key, len, MIX_UINT64(hash1));

        for (i = 0; i < (int) pstBloomfilter->dwHashFuncs; i++) {
            pstBloomfilter->pdwHashPos[i] = (hash1 + i * hash2) % dwFilterBits;
        }
    }

/**
 * @brief 向布隆过滤器中添加一个元素
 * @param pstBloomfilter  布隆过滤器
 * @param key  要进行哈希的数据
 * @param len  要进行哈希的数据的长度
 * @return  成功返回0，当添加数据超过限制值时返回1提示用户
 */
    FORCE_INLINE int BloomFilter_Add(CppBloomFilter *pstBloomfilter, const void *key, int len) {
        if ((pstBloomfilter == nullptr) || (key == nullptr) || (len <= 0))
            return -1;

        int i;

        if (pstBloomfilter->cInitFlag != 1) {
            // Reset后没有初始化，使用前需要memset
            memset(pstBloomfilter->pstFilter, 0, pstBloomfilter->dwFilterSize);
            pstBloomfilter->cInitFlag = 1;
        }

        // hash key到bloomfilter中, 为了计算不同hash命中的位置，保存pdwHashPos数组
        bloom_hash(pstBloomfilter, key, len);
        for (i = 0; i < (int) pstBloomfilter->dwHashFuncs; i++) {
            SETBIT(pstBloomfilter, pstBloomfilter->pdwHashPos[i]);
        }

        // 增加count数
        pstBloomfilter->dwCount++;
        return 0;
    }

// 检查一个元素是否在bloomfilter中
// 返回：0-存在，1-不存在，负数表示失败
    FORCE_INLINE int BloomFilter_Check(CppBloomFilter *pstBloomfilter, const void *key, int len) {
        if ((pstBloomfilter == nullptr) || (key == nullptr) || (len <= 0))
            return -1;

        int i;

        bloom_hash(pstBloomfilter, key, len);
        for (i = 0; i < (int) pstBloomfilter->dwHashFuncs; i++) {
            // 如果有任意bit不为1，说明key不在bloomfilter中
            // 注意: GETBIT()返回不是0|1，高位可能出现128之类的情况
            if (GETBIT(pstBloomfilter, pstBloomfilter->pdwHashPos[i]) == 0)
                return 1;
        }

        return 0;
    }

    FORCE_INLINE void BloomFilter_Print(CppBloomFilter *pstBloomfilter) {
        if (pstBloomfilter == nullptr)
            return;

        std::stringstream ss;
        ss << "\t\tCppBloomFilter: " << std::endl;
        ss << "-------------------------------" << std::endl;
        ss << "Initialized: " << int(pstBloomfilter->cInitFlag) << std::endl;
        ss << "BloomFilterSize(bits): " << pstBloomfilter->dwFilterBits << std::endl;
        ss << "BloomFilterSize(bytes): " << pstBloomfilter->dwFilterSize << std::endl;
        ss << "HashFuncNums " << pstBloomfilter->dwHashFuncs << std::endl;
        ss << "Seed: " << pstBloomfilter->dwSeed << std::endl;
        ss << "InsertCount: " << pstBloomfilter->dwCount << std::endl;
        ss << "-------------------------------" << std::endl;
        std::cout << ss.str() << std::endl;
    }
}
#endif
