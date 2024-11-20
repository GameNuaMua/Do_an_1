#ifndef SORT_FLIGHT_H
#define SORT_FLIGHT_H

// file.h
#include "Ql_struct.h"
#include "Read_Write.h"

// sắp xếp chuyến bay theo thời gian
int Sort_flight()
{
    // khởi tạo biến
    CB cb;
    CB cb1;
    int size = 0;
    int dem = 0;
    //------------------------------------mở file---------------------------------------------
    FILE *fcb = fopen("data/chuyen_bay/TEMP_flight.txt","r");
    //----------------------------kiểm tra mở file--------------------------
    if (fcb == NULL)
    {
        printf("error: TEMP_flight.txt");
        exit(1);
    }
    //------------------------------đếm số lượng----------------------------
    char linesl[150];
    while (fgets(linesl, 150, fcb) != NULL)
    {
        size++;
    }
    // khởi tạo mảng
    CB cb_temp[size];
    // đặt con trở về lại đầu file
    rewind(fcb);
    //------------------------------lấy phần tử-----------------------------
    char linecb[150];
    while (fgets(linecb, 150, fcb) != NULL)
    {
        cb = read_cb(linecb);
        cb_temp[dem] = cb;
        dem++;
    }
    //-----------------------------------đóng file--------------------------------------------
    fclose(fcb);
    //-------------------------------sắp xếp--------------------------------
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (cb_temp[i].ngayBay.tm_year < cb_temp[j].ngayBay.tm_year
            ||(cb_temp[i].ngayBay.tm_year == cb_temp[j].ngayBay.tm_year && cb_temp[i].ngayBay.tm_mon > cb_temp[j].ngayBay.tm_mon)
            ||(cb_temp[i].ngayBay.tm_year == cb_temp[j].ngayBay.tm_year && cb_temp[i].ngayBay.tm_mon == cb_temp[j].ngayBay.tm_mon && cb_temp[i].ngayBay.tm_mday < cb_temp[j].ngayBay.tm_mday)
            ||(cb_temp[i].ngayBay.tm_year == cb_temp[j].ngayBay.tm_year && cb_temp[i].ngayBay.tm_mon == cb_temp[j].ngayBay.tm_mon && cb_temp[i].ngayBay.tm_mday == cb_temp[j].ngayBay.tm_mday && cb_temp[i].ngayBay.tm_hour < cb_temp[j].ngayBay.tm_hour)
            ||(cb_temp[i].ngayBay.tm_year == cb_temp[j].ngayBay.tm_year && cb_temp[i].ngayBay.tm_mon == cb_temp[j].ngayBay.tm_mon && cb_temp[i].ngayBay.tm_mday == cb_temp[j].ngayBay.tm_mday && cb_temp[i].ngayBay.tm_hour == cb_temp[j].ngayBay.tm_hour && cb_temp[i].ngayBay.tm_min < cb_temp[j].ngayBay.tm_min))
            {
                cb1 = cb_temp[i];
                cb_temp[i] = cb_temp[j];
                cb_temp[j] = cb1;
            }
        }
    }

    //------------------------------------mở file---------------------------------------------
    fcb = fopen("data/chuyen_bay/TEMP_flight.txt","w");
    //-----------------------------kiểm tra---------------------------------
    if (fcb == NULL)
    {
        printf("error: TEMP_flight.txt");
        exit(1);
    }
    //-------------------------------sao lưu--------------------------------
    for (int i = 0; i < size; i++)
    {
        write_cb(fcb,cb_temp[i]);
    }
    //-----------------------------------đóng file--------------------------------------------
    fclose(fcb);
    return 0;
}

#endif//SORT_FLIGHT_H