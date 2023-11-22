/*
 * BloomFilter.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_SOURCE_ROUTING_LIPSIN_PACKETS_BLOOMFILTER_H_
#define INET_PROJECTS_SOURCE_ROUTING_LIPSIN_PACKETS_BLOOMFILTER_H_
#include <string>
class CppBloomFilter; // this line cannot be eliminated
namespace inet{
    class BloomFilter{
    private:
        CppBloomFilter* innerCppBloomFilter;
        int M; // the size of bloom filter
        int K; // the number of hash functions
        int seed; // the seed of the bloom filter
    public:
        // constructor
        BloomFilter(int m, int k, int seed);
        BloomFilter* getCopy() const;
        ~BloomFilter();
    public:
        // operations
        void insert(int linkIdentifier);
        bool query(int linkIdentifier);
        void reset();
    public:
        // getter and setter
        int getM() const {
            return M;
        }
        int getK() const {
            return K;
        }
    // the goBloomFilter corresponding function
    /*
    public:
        static void executeCMD(const char* cmd, char* result);
    */
    };
}
#endif /* INET_PROJECTS_SOURCE_ROUTING_LIPSIN_PACKETS_BLOOMFILTER_H_ */
