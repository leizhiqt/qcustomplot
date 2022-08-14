#ifndef FFTTRANS_H
#define FFTTRANS_H

#include <QVector>

/*
*
*
*               计算傅里叶变换频谱
*
*
* */
#define      MAX_MATRIX_SIZE                4194304             // 2048 * 2048
#define      PI                             3.141592653
#define      MAX_VECTOR_LENGTH              10000


typedef struct Complex
{
    double rl;              //实部 用这个当做y轴画图像就可以
    double im;              //虚部
}Complex;

class FFTTrans
{

public:
    //傅里叶转换 频域
    bool fft1(Complex  const inVec[], int  const len, Complex  outVec[]);

    //逆转换
    bool ifft(Complex  const inVec[], int  const len, Complex  outVec[]);

    int get_computation_layers(int  num);

    bool is_power_of_two(int  num);

    void fft2(const QVector<double> vec, const int len, Complex *outVec);

    void test();

};

#endif // FFTTRANS_H


