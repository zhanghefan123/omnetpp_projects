/*
 * LipsinOverheadCalculation.h
 *
 *  Created on: Sep 13, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_OVERHEAD_ENCAPSULATE_LIPSINOVERHEADCALCULATION_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_OVERHEAD_ENCAPSULATE_LIPSINOVERHEADCALCULATION_H_
#include <fstream>
#include <vector>
namespace inet {

class LipsinOverheadCalculation {
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
    // find optimal M with given C, K,N
    static double findMinimumOverheadWithOptimalM(int C, int K, int N);
    // set precision, os is the output stream, n is the precision
    static std::ostream& setPrecision(std::ostream& os, int n);
    // zhf add code
    static void sayHello();
    // zhf add code
    static int calculateEncapsulateCount(int C , int k, int N, double B, double t);
    // zhf add code
    static int findMwithMinimumOverhead(int C,int K, int N);
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_OVERHEAD_ENCAPSULATE_LIPSINOVERHEADCALCULATION_H_ */
