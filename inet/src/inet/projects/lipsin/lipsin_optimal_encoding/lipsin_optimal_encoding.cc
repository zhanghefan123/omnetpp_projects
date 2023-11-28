//
// Created by 张贺凡 on 2023/11/28.
//
#include "lipsin_optimal_encoding.h"
#include <cmath>    // 这里是用来进行数学计算的时候引入的头文件
#include <iostream> // 这里是iostream用来进行输入输出的头文件
#include <vector>  // 这里准备用vector进行返回值的存储的头文件
#include <fstream> // 这里直接使用fstream进行文件的写入的头文件
using namespace std;
namespace inet{

// calculateFullOverhead 计算总的开销的实现
    double BloomFilter::calculateFullOverhead(int C,double M, int k, int N) {
        return BloomFilter::calculateIncorrectOverhead(C, M, k, N) + BloomFilter::calculateCorrectOverhead(M, N);
    }

// calculateIncorrectOverhead 计算错误转发开销的实现
    double BloomFilter::calculateIncorrectOverhead(int C, double M, int k, int N) {
        double fpr = BloomFilter::calculateFPR(M, k, N);
        if (fpr >= 1.0/3.0) {
            // 返回无穷大
            return 1.0 / 0.0;
        }
        double result = (2*N + 4)*(M+C)*fpr/(1-3*fpr);
        return result;
    }

// calculateCorrectOverhead 计算正确转发开销的实现
    double BloomFilter::calculateCorrectOverhead(double M, int N) {
        return M*N;
    }

// calculateFPR 进行fpr假正率的计算。
    double BloomFilter::calculateFPR(double M, int K, int N) {
        // calculate the false positive rate of the bloom filter
        // 计算公式：fpr = [1-(1-1/M)^(KN)]^K
        double result = pow((1 - pow((1 - 1.0 / M), K * N)),K);
        return result;
    }

// findMinimumOverheadWithOptimalM 使用遍历的方式从一个指定的范围之中找到最优的M
    double BloomFilter::findMinimumOverheadWithOptimalM(int C, int K, int N) {
        int optimizedM = -1;
        // 这是最小的开销：首先给它一个无穷大，让他能够被替换调
        double minimum_overhead = 1.0 / 0.0;
        // 进行布隆过滤器大小M的遍历，从而能够寻找一个最优的M
        for(int i = 1 ; i < 1000; i++)
        {
            // 使用遍历到的M进行开销的计算，如果计算的结果不是无穷大，那么就进行比较，如果比最小的开销还要小，那么就进行替换
            if(!std::isinf(calculateFullOverhead(C, i, K, N)) && calculateFullOverhead(C, i, K, N) < minimum_overhead)
            {
                minimum_overhead = calculateFullOverhead(C, i, K, N);
                optimizedM = i; // 存储最优的M的大小
            }
        }
        return minimum_overhead;
    }

    std::vector<int> BloomFilter::calculateEncodingNodes(int C, int k ,int N, double B, double t){
        std::vector<int> encodingNodes;

        // 创建一个一维数组用来进行状态的存储
        auto *H = new double[N+1]; // 总共有N+1个状态, H(i)代表i跳的最小代价

        // 创建一个辅助一维数组用来进行前驱状态的存储
        auto *H_pre = new int[N+1]; // 总共有N个状态, H_pre(i)代表i跳的最小代价的前驱状态

        // 创建一个一维数组用来进行封装策略的存储
        auto *x_star = new int[N+2]; // 是一个一维数组, x_star[i]代表第i个节点的封装策略

        // 进行数据结构状态的一些初始化的操作x
        H[0] = 0; // 源路由0跳的代价为0
        H_pre[0] = 0; // 源路由0跳的前驱状态为0
        x_star[1] = 1; // 源路由第一个节点是一定要进行封装的
        x_star[N+1] = 1; // 源路由最后一个节点是一定要结束的

        // 开始利用动态规划状态转移方程进行计算, 0跳不用进行计算因为代价为0, 1跳到N跳都需要进行计算
        for (int i = 1; i < N+1; i++) {
            // 初始化为无穷大
            H[i] = 1.0 / 0.0;
            // 遍历i状态的所有的可能的前驱状态
            for (int j = 0; j < i; j++) {
                // 计算当前状态的代价 - 以时间作为单位。
                double cost_in_time = BloomFilter::findMinimumOverheadWithOptimalM(C, k, i - j)/B + t + H[j];
                // 如果当前状态的代价小于之前的代价, 则进行更新的操作
                if (cost_in_time < H[i]) {
                    H[i] = cost_in_time; // 更新当前的开销的最小值
                    H_pre[i] = j; // 更新当前状态的前驱状态是哪一个
                }
            }
        }

        // 当前状态是N
        int current_state = N;
        // 记录重新封装的次数
        int count = 0;
        // H(1)的前驱状态必定是0
        while (current_state != 0) {
            current_state = H_pre[current_state]; // 更新当前抵达了哪一个状态
            x_star[current_state+1] = 1; // H_pre数组存储的是跳数，而x_star的索引存储的是节点的数量。
            count++;
        }

        // 创建结果数组
        std::vector<double> result;
        result.push_back(count); // 将count的值放入到结果数组中
        result.push_back(H[N]); // 将H(N)的值放入到结果数组中

        // 将正常转发开销H(N)

        // 将x_star打印出来 1 0 0 0 1 0 0 0 1
        std::cout << "x_star:";
        for (int i = 1; i < N+2; i++) {
            if((x_star[i] == 1) && (i != 1) && (i!=(N+1)))
            {
                encodingNodes.push_back(i);
            }
            std::cout << x_star[i] << " ";
        }
        std::cout << std::endl;

        // 找到x_star之中的第一个1和下一个1之间的距离
        for (int i = 2; i < N+2;i++){
            if(x_star[i] == 1){
                break;
            }
        }
        delete [] H;
        delete [] H_pre;
        delete [] x_star;
        // return result;
        return encodingNodes;
    }

// calculateEncodingStrategyVector 计算重新封装策略
    std::vector<double> BloomFilter::calculateEncodingStrategyVector(int C, int k, int N, double B, double t) {

        // 创建一个一维数组用来进行状态的存储
        auto *H = new double[N+1]; // 总共有N+1个状态, H(i)代表i跳的最小代价

        // 创建一个辅助一维数组用来进行前驱状态的存储
        auto *H_pre = new int[N+1]; // 总共有N个状态, H_pre(i)代表i跳的最小代价的前驱状态

        // 创建一个一维数组用来进行封装策略的存储
        auto *x_star = new int[N+2]; // 是一个一维数组, x_star[i]代表第i个节点的封装策略

        // 进行数据结构状态的一些初始化的操作x
        H[0] = 0; // 源路由0跳的代价为0
        H_pre[0] = 0; // 源路由0跳的前驱状态为0
        x_star[1] = 1; // 源路由第一个节点是一定要进行封装的
        x_star[N+1] = 1; // 源路由最后一个节点是一定要结束的

        // 开始利用动态规划状态转移方程进行计算, 0跳不用进行计算因为代价为0, 1跳到N跳都需要进行计算
        for (int i = 1; i < N+1; i++) {
            // 初始化为无穷大
            H[i] = 1.0 / 0.0;
            // 遍历i状态的所有的可能的前驱状态
            for (int j = 0; j < i; j++) {
                // 计算当前状态的代价 - 以时间作为单位。
                double cost_in_time = BloomFilter::findMinimumOverheadWithOptimalM(C, k, i - j)/B + t + H[j];
                // 如果当前状态的代价小于之前的代价, 则进行更新的操作
                if (cost_in_time < H[i]) {
                    H[i] = cost_in_time; // 更新当前的开销的最小值
                    H_pre[i] = j; // 更新当前状态的前驱状态是哪一个
                }
            }
        }

        // 当前状态是N
        int current_state = N;
        // 记录重新封装的次数
        int count = 0;
        // H(1)的前驱状态必定是0
        while (current_state != 0) {
            current_state = H_pre[current_state]; // 更新当前抵达了哪一个状态
            x_star[current_state+1] = 1; // H_pre数组存储的是跳数，而x_star的索引存储的是节点的数量。
            count++;
        }

        // 创建结果数组
        std::vector<double> result;
        result.push_back(count); // 将count的值放入到结果数组中
        result.push_back(H[N]); // 将H(N)的值放入到结果数组中

        // 将正常转发开销H(N)

        // 将x_star打印出来
        std::cout << "x_star:";
        for (int i = 1; i < N+2; i++) {
            std::cout << x_star[i] << " ";
        }
        std::cout << std::endl;

        // 找到x_star之中的第一个1和下一个1之间的距离
        for (int i = 2; i < N+2;i++){
            if(x_star[i] == 1){
                break;
            }
        }
        delete [] H;
        delete [] H_pre;
        delete [] x_star;
        return result;
    }

    std::ostream &BloomFilter::setPrecision(std::ostream &os, int n) {
        os << std::fixed << std::setprecision(n);
        return os;
    }
}
