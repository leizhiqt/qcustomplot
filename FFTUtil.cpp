#include "FFTUtil.h"
#include <fftw3.h>
#include "math.h"
//#include "SampleBean.h"

//带宽int w_fs
/*int FFTUtil::getDrawLineN(int w_fs)
{
//    log_debug("[%s %d] g_fSamplerate=%f w_fs=%d\n",__FILE__,__LINE__,g_fSamplerate,w_fs);

    if(w_fs==50){
        return g_fSamplerate*20000;
    }
    if(w_fs==20){
        return g_fSamplerate*50000;
    }
    if(w_fs==10){
        return g_fSamplerate*100000;
    }
    if(w_fs==5){
        return g_fSamplerate*200000;
    }
    if(w_fs==2){
        return g_fSamplerate*500000;
    }
    if(w_fs==1){
        return g_fSamplerate*1000000;
    }

    return 3200000;
}*/
float FFTUtil::getFs(float w_fs)
{
//    log_debug("[%s %d] g_fSamplerate=%f w_fs=%d\n",__FILE__,__LINE__,g_fSamplerate,w_fs);

    if(w_fs==50){
        return (float)1/20000;
    }
    if(w_fs==20){
        return (float)1/50000;
    }
    if(w_fs==10){
        return (float)1/100000;
    }
    if(w_fs==5){
        return (float)1/200000;
    }
    if(w_fs==2){
        return (float)1/500000;
    }
    if(w_fs==1){
        return (float)1/1000000;
    }

    return (float)1/1000000;
}
int FFTUtil::getDrawLineN(const QString& arg1)
{
    if(arg1=="1Hz")
    {
        return 1;
    }

    if(arg1=="2Hz"){
        return 2;
    }
    if(arg1=="5Hz"){
        return 5;
    }
    if(arg1=="10Hz"){
        return 10;
    }
    if(arg1=="20Hz")
    {
        return 20;
    }
    if(arg1=="50Hz")
    {
        return 50;
    }

    return 1;
}
int FFTUtil::getAMP(int code)
{
//    log_debug("code=%d",code);

    int amp=1;

    if(code==0){
        return amp;
    }
    if(code==2){
        return 30;
    }
    if(code==3){
        return 2100;
    }

    return amp;
}

bool FFTUtil::isTN(int x)
{
    return (x != 0) && ((x & -x) == x);
}

//
/*
int FFTUtil::sample_trans_dbm(QList<double>& sample_data_hz)
{
    if(sample_data_hz.isEmpty())
    {
        return -1;
    }

    //转mv 4.096
//    double dy_dmv = 0.00048828125;
    double dy_dmv = 0.0005;
    for(QList<double>::iterator it=sample_data_hz.begin();it!=sample_data_hz.end();++it)
    {
//        log_debug("amp=%d\n",amp);
        *it=((*it)*dy_dmv)/sampleBean.amp;
    }
    return 0;
}
*/
/*
int FFTUtil::sample_trans_dbm(QList<int>& sample_data_hz,QList<double>& sample_dbm)
{
    if(sample_data_hz.isEmpty())
        return -1;
    //转mv 4.096
//    double dy_dmv = 0.00048828125;
    double dy_dmv = 0.0005;
    for(QList<int>::iterator it=sample_data_hz.begin();it!=sample_data_hz.end();++it)
    {
//        log_debug("amp=%d",amp);
        //double dbm=((*it)*dy_dmv)/sampleBean.amp;
        //sample_dbm.append(dbm);
        double dbm=(double)(*it)*dy_dmv/sampleBean.amp;
        sample_dbm.append(dbm);
    }//180ms
//TASK_POINT
//    TASK_USETIMES
    return 0;
}*/
/*
int FFTUtil::sample_trans_dbm(QVector<int>& sample_data_hz,QVector<double>& sample_dbm)
{
//    TASK_POINT
    if(sample_data_hz.isEmpty())
        return -1;
    //转mv 4.096
//    double dy_dmv = 0.00048828125;
    double dy_dmv = 0.0005;
//    for(QVector<int>::iterator it=sample_data_hz.begin();it!=sample_data_hz.end();++it)
//    {
//        double dbm=(double)(*it)*dy_dmv/sampleBean.amp;
//        sample_dbm.append(dbm);
//    }//30ms

    for(auto it:sample_data_hz)
    {
        double dbm=(double)(it)*dy_dmv/sampleBean.amp;
        sample_dbm.append(dbm);
        //        log_debug("amp=%d",amp);
    }//30ms

//    TASK_USETIMES
    return 0;
}
*/
void FFTUtil::FFT_cut_sample_data(QVector<double>& sample_data_hz,int min_k,int max_k,int f_bandwidth)
{
    if(sample_data_hz.isEmpty() || f_bandwidth==0)
    {
        return;
    }

    int Khz=1000;
    int K1=min_k*Khz/f_bandwidth;
    int K2=max_k*Khz/f_bandwidth;

    //10k->200k
    int L = sample_data_hz.size();

    int min_x = K1;
    if(min_x>L || min_x<0) min_x=0;
    int max_x = K2;
    if(max_x>L || max_x<0) max_x=L;

    if(min_x==max_x || max_x<min_x) return;

    sample_data_hz.remove(max_x-1,L-max_x);
    sample_data_hz.remove(0,min_x);

//    log_debug("K1=%d K2=%d FFT_L=%d",K1,K2,sample_data_hz.size());
}

//250ms 1hz
int FFTUtil::FFT_Trans(const QVector<double>& in_fft_y,QVector<double>& out_fft_y,int f_bandwidth)
{
//    TASK_POINT

    if(in_fft_y.isEmpty()) return -1;

    const double *array=in_fft_y.data();
    const int L=in_fft_y.size();

//    log_debug("L1=%d",L);
//    if(!FFTUtil::isTN(L)) return -2;

    fftw_complex* out_cpx;
    fftw_plan fft;

    out_cpx = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*L);
    fft=fftw_plan_dft_r2c_1d(L,(double *)array,out_cpx,FFTW_ESTIMATE);
    fftw_execute(fft);

//    log_debug("L2=%d",L/2);
    for(int i=0;i<(L/2+1);i++){
//        log_debug("i=%d",i);
        //算法1
        double a=out_cpx[i][0];
        double bi=out_cpx[i][1];
        double pow2=a*a+bi*bi;

        double val = sqrt(pow2);

//        val /= L;
//        val=5*log10(val);//转dB
        val=20*log10(val);//转dB
        //abs
//        log_debug("i=%d fft=%f+%fi pow2=%f val=%.12f\n",i,a,bi,pow2,val);
        out_fft_y<<val;
    }
    fftw_destroy_plan(fft);
    fftw_free(out_cpx);

    //10k->200k
    FFT_cut_sample_data(out_fft_y,10,200,f_bandwidth);

//TASK_USETIMES
//    log_debug("FFT_Trans finsh");
    return 0;
}
