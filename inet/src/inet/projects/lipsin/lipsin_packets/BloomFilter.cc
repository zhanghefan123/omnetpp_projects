/*
 * BloomFilter.cpp
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#include "inet/projects/lipsin/lipsin_packets/cpp_bloom_filter.h"
#include "BloomFilter.h"

namespace inet {

    /**
     * the destructor of bloom filter
     */
    BloomFilter::~BloomFilter() {
        // free the memory of the inside bloom filter
        FreeBloomFilter(this->innerCppBloomFilter);
        // set the innerCppBloomFilter to nullptr
        this->innerCppBloomFilter = nullptr;
    }

    /**
     * create bloom filter
     * @param m the bloom filter size m
     * @param k the number of hash functions
     * @param seed the seed of the hash functions
     */
    BloomFilter::BloomFilter(int m, int k, int seed) {
        this->innerCppBloomFilter = new CppBloomFilter;
        InitBloomFilterWithMandK(this->innerCppBloomFilter,
                                 seed, m, k);
        this->M = m;
        this->K = k;
        this->seed = seed;
    }

    /**
     * copy the entire bloom filter including the inside cppBloomfilter
     * @return
     */
    BloomFilter* BloomFilter::getCopy() const{
        // create new inside CppBloomFilter
        CppBloomFilter *newInsideCppBloomFilter = NewBloomFilter(this->innerCppBloomFilter);
        // create new outside bloom filter
        auto* newOutSideBloomFilter = new BloomFilter(this->M, this->K, this->seed);
        // set the innerCppBloomFilter into the outside bloom filter
        newOutSideBloomFilter->innerCppBloomFilter = newInsideCppBloomFilter;
        // return the created Bloom Filter
        return newOutSideBloomFilter;
    }

    /**
     * insert the link identifier into the inside cppBloomFilter
     * @param linkIdentifier the link Identifier
     */
    void BloomFilter::insert(int linkIdentifier){
        // call the inside bloom filter to insert the linkIdentifier
        BloomFilter_Add(this->innerCppBloomFilter, (const void*)(&linkIdentifier), sizeof(int));
    }

    /**
     * query the existence of the linkIdentifier in the bloom filter
     * @param linkIdentifier the linkidentifier about to query
     * @return
     */
    bool BloomFilter::query(int linkIdentifier){
        bool result;
        if(BloomFilter_Check(this->innerCppBloomFilter, (const void*)(&linkIdentifier), sizeof(int)) == 0)
        {
            result = true;
        } else {
            result = false;
        }
        return result;
    }

    void BloomFilter::reset(){
        RealResetBloomFilter(this->innerCppBloomFilter);
    }

    double BloomFilter::getBitSetRate() {
        return getInsideBloomFilterSetRate(this->innerCppBloomFilter);
    }

    // goBloomFilter implementation
    /*
    void BloomFilter::deleteBF(const std::string& uuid) { // NOLINT
        std::stringstream ss;
        ss << "./bloom-master delete -u " << uuid;
        char result[1024] = {0};
        BloomFilter::executeCMD(ss.str().c_str(), result);
    }
    
    void BloomFilter::replace(int newM,int newK){
        std::stringstream ss;
        ss << "./bloom-master replace -u " << UUID << " -M " << newM << " -K " << newK;
        char result[1024] = {0};
        BloomFilter::executeCMD(ss.str().c_str(), result);
    }

    void BloomFilter::insert(int linkIdentifier) {
        std::stringstream ss;
        ss << "./bloom-master add -u " << UUID << " -l " << linkIdentifier;
        char result[1024] = {0};
        BloomFilter::executeCMD(ss.str().c_str(), result);
    }

    bool BloomFilter::query(int linkIdentifier) {
        std::stringstream ss;
        ss << "./bloom-master test -u " << UUID << " -l " << linkIdentifier;
        char result[1024] = {0};
        BloomFilter::executeCMD(ss.str().c_str(), result);
        std::string resultInString = std::string(result);
        // 将resultInString转换为bool
        if (resultInString == "true") {
            return true;
        } else {
            return false;
        }
    }

    void BloomFilter::create() {
        std::stringstream ss;
        ss << "./bloom-master create -M " << this->M << " -K " << this->K;
        char result[1024] = {0};
        BloomFilter::executeCMD(ss.str().c_str(),result);
        std::string resultInString = std::string(result);
        this->setUUID(resultInString);
    }

    void BloomFilter::executeCMD(const char *cmd, char *result) {
        char buf_ps[1024]; // 缓冲区
        char ps[1024] = {0}; // 命令
        FILE *ptr;
        strcpy(ps, cmd);
        if ((ptr = popen(ps, "r")) != nullptr) {
            while (fgets(buf_ps, 1024, ptr) != nullptr) {
                // 将s2放到s1的后面
                strcat(result, buf_ps);
                if (strlen(result) > 1024)
                    break;
            }
            pclose(ptr);
            ptr = nullptr;
        } else {
            printf("open %s error\n", ps);
        }
    }

    BloomFilter* BloomFilter::getCopy() const{
        std::stringstream ss;
        ss << "./bloom-master copy -u " << this->UUID;
        char result[1024] = {0};

        BloomFilter::executeCMD(ss.str().c_str(),result);
        std::string resultInString = std::string(result);
        auto* newBloomFilter = new BloomFilter(this->M,this->K);
        newBloomFilter->setUUID(resultInString);
        return newBloomFilter;
    }*/

} /* namespace inet */
