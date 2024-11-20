#ifndef UPDATE_TIME_H
#define UPDATE_TIME_H

// thư viện
#include "Ql_struct.h"

// xử lý thời gian
TG Thoi_Gian_Hien_Tai()
{
    TG tg;
    time_t hien_tai = time(NULL);
    struct tm tm = *localtime(&hien_tai);

    tg.tm_year = tm.tm_year + 1900;
    tg.tm_mon = tm.tm_mon + 1;
    tg.tm_mday = tm.tm_mday;
    tg.tm_hour = tm.tm_hour;
    tg.tm_min = tm.tm_min;
    return tg;
}

// TG tg = Thoi_Gian_Hien_Tai();
// printf("%02d/%02d/%d  %02d:%02d\n", tg.tm_mday, tg.tm_mon, tg.tm_year, tg.tm_hour, tg.tm_min);
#endif// end UPDATE_TIME_H