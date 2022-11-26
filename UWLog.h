#ifndef UWLOG_H
#define UWLOG_H
#include <windows.h>

//#define uchar unsigned char

#ifdef __cplusplus /* 如果采用了C++，如下代码使用C编译器 */
     extern  "C"  {  /* 如果没有采用C++，顺序预编译 */
#endif

    void log_open(const char* savefp,const int level);
    void log_printfs(const char* files,unsigned int line,const char* fmt, ...);
    void log_close();

    /* 采用C编译器编译的C语言代码段 */
#ifdef __cplusplus /* 结束使用C编译器 */
     }
#endif

#define log_debug(fmt, ...) \
        log_printfs(__FILE__,__LINE__,fmt, ##__VA_ARGS__)

#define TASK_POINT \
    unsigned long s_time,e_time,usetimes;        \
    s_time = GetTickCount();

#define TASK_USETIMES   \
   e_time = GetTickCount(); \
   usetimes= e_time-s_time; \
   log_debug("Use Time:%d (ms)",usetimes);

//#define log_debug(fmt, ...) {}

#endif // UWLOG_H
