//
// Created by 张贺凡 on 2023/11/28.
//

#ifndef DELAYTOLERANTNETWORK_LIPSIN_OPTIMAL_ENCODING_H
#define DELAYTOLERANTNETWORK_LIPSIN_OPTIMAL_ENCODING_H
#include <vector>
#include <ostream>
#include <deque>
namespace inet{
    class OptimalEncoding{
    public:
        // calculate the f_co overhead
        static double calculateFullOverhead(int C,double M, int k, int N);
        // calculate the f_cfo overhead
        static double calculateIncorrectOverhead(int C,double M, int k, int N);
        // calculate the f_ifo overhead
        static double calculateCorrectOverhead(double M, int N);
        // fpr calculation
        static double calculateFPR(double M, int k, int N) ;
        // dynamic programming to calculate the encoding strategy vector x star
        static std::vector<double> calculateEncodingStrategyVector(int C , int k, int N, double B, double t);
        // calculate encoding nodes
        static std::deque<std::pair<int,int>> calculateEncodingNodes(int C, int k, int N, double B, double t);
        // find optimal M with given C, K,N
        static double findMinimumOverheadWithOptimalM(int C, int K, int N);
        // set precision, os is the output stream, n is the precision
        static std::ostream& setPrecision(std::ostream& os, int n);
    };
}
#endif //DELAYTOLERANTNETWORK_LIPSIN_OPTIMAL_ENCODING_H
