#include "UWLog.h"
#include "stdarg.h"
#include "stdio.h"
#include <fstream>
#include <Windows.h>
#include "FormatTimes.h"

using namespace std;

int _level=0;

char logfile[1024]="logfile.log";

ofstream out_log_fp;

void log_open(const char* savefp,const int level)
{
    _level=level;
    snprintf(logfile, sizeof(logfile),"%s",savefp);
    out_log_fp.open(logfile,ios::trunc);
    printf("logfile save:%s\n",logfile);
}

void log_printfs(const char* files,unsigned int line,const char* fmt, ...)
{

    char bufstr[2048]   = "\0";
    char logstr[4096] = "\0";
    char times[20]="\0";

    va_list va_alist;

    va_start(va_alist, fmt);

    vsnprintf(bufstr, sizeof(bufstr), fmt, va_alist);

    va_end (va_alist);

//    log_debug("logfile save:%s\n",logfile);

    t_stime(times);

    snprintf(logstr,sizeof(logstr),"[%ld %s\t%s\t%d]%s\n",GetCurrentThreadId(),times,files,line,bufstr);

//    snprintf(logstr,sizeof(logstr),"[%s]%s\n",times,bufstr);
    if(!_level) printf("%s",logstr);

    out_log_fp.write(logstr,strlen(logstr));
    out_log_fp.flush();
}

void log_close()
{
    out_log_fp.close();
}
