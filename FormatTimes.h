#ifndef FORMATTIMES_H
#define FORMATTIMES_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//按照不同的方式格式化当前times
void t_formats(char *s,const char*fmats);
//获取当前时间
void t_ftime(char *tsname);
//获取当前日期
void t_fdate(char *s);
//获取当前时间
void t_stime(char *tsname);

//执行时间
int disTime();

int ntpdate(const char *f_ip);

void sys_ms(char *ms);

#endif // FORMATTIMES_H
