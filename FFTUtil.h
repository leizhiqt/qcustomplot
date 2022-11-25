#ifndef FFTUTIL_H
#define FFTUTIL_H
#include <QVector>

class FFTUtil
{
public:
    FFTUtil(){}

    static int getDrawLineN(int type);
    static int getDrawLineN(const QString& arg1);
    static float getFs(float FS);
    static int getAMP(int code);
    static bool isTN(int x);

    static int sample_trans_dbm(QList<double>& sample_data_hz);
    static int sample_trans_dbm(QList<int>& sample_data_hz,QList<double>& sample_dbm);
    static int sample_trans_dbm(QVector<int>& sample_data_hz,QVector<double>& sample_dbm);

    static void FFT_cut_sample_data(QVector<double>& sample_data_hz,int min_k,int max_k,int f_bandwidth);

    static int FFT_Trans(const QVector<double>& in_fft_y,QVector<double>& out_fft_y,int f_bandwidth);
};

#endif // FFTUTIL_H
