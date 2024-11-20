#ifndef FILTERING_H
#define FILTERING_H

// file.h
#include "Ql_struct.h"
#include "Update_time.h"
#include "Read_Write.h"

// lọc các chuyến bay đã bay theo thời gian
void Filtering_flight()
{
    // cập nhật thời gian
    TG tg = Thoi_Gian_Hien_Tai();
    // khai báo biến
    CB cb;
    //-------------------------------------mở file----------------------------------------------
    FILE *ff = fopen("data/chuyen_bay/flight.txt","r");
    FILE *ff_temp = fopen("data/chuyen_bay/TEMP_flight.txt","a");
    //--------------------------kiểm tra mở file-----------------------
    if (ff == NULL)
    {
        printf("error: flight.txt\n");
        exit(1);
    }
    //---------------------
    if (ff_temp == NULL)
    {
        printf("error: TEMP_flight.txt\n");
        exit(1);
    }
    //-------------------------------lọc--------------------------------
    char linecb[150];
    while (fgets(linecb,150,ff) != NULL)
    {
        cb = read_cb(linecb);
        if (cb.ngayBay.tm_year > tg.tm_year || (cb.ngayBay.tm_year == tg.tm_year && cb.ngayBay.tm_mon > tg.tm_mon) 
        || (cb.ngayBay.tm_year == tg.tm_year && cb.ngayBay.tm_mon == tg.tm_mon && cb.ngayBay.tm_mday > tg.tm_mday)
        || (cb.ngayBay.tm_year == tg.tm_year && cb.ngayBay.tm_mon == tg.tm_mon && cb.ngayBay.tm_mday == tg.tm_mday && cb.ngayBay.tm_hour > tg.tm_hour)
        || (cb.ngayBay.tm_year == tg.tm_year && cb.ngayBay.tm_mon == tg.tm_mon && cb.ngayBay.tm_mday == tg.tm_mday && cb.ngayBay.tm_hour == tg.tm_hour && cb.ngayBay.tm_min > tg.tm_min))
        {
            write_cb(ff_temp,cb);
        }
    }
    //------------------------------------đóng file---------------------------------------------
    fclose(ff);
    fclose(ff_temp);
    remove("data/chuyen_bay/flight.txt");
    rename("data/chuyen_bay/TEMP_flight.txt","data/chuyen_bay/flight.txt");
}

// lọc vé máy bay theo chuyến bay đã xoá or chuyến bay đã bị huỷ
void Filtering_ticket()
{
    Filtering_flight();
    // khởi tạo biến
    CB cb;
    VE ve;
    int sizecb = 0, demcb = 0, check;
    //-----------------------------------------------mở file------------------------------------------
    FILE * fcb = fopen("data/chuyen_bay/flight.txt","r");
    //--------------------------kiểm tra mở file--------------------------
    if (fcb == NULL)
    {
        printf("error: flight.txt\n");
        exit(1);
    }
    //------------------------------lấy số lượng chuyến bay hiện tại------------
    char linecbht[150];
    while (fgets(linecbht, 150, fcb) != NULL)
    {
        sizecb++;
    }
    rewind(fcb);// đặt con trỏ về lại đầu file
    // tạo mảng chứa mã chuyến bay
    char maCb[sizecb][10];
    //--------------------------kiểm tra tồn tại--------------------------
    char linecb[150];
    while (fgets(linecb, 150, fcb) != NULL)
    {
        cb = read_cb(linecb);
        strcpy(maCb[demcb],cb.maCB);
        demcb++;
    }
    //----------------------------------------------đóng file-----------------------------------------
    fclose(fcb);
    //-----------------------------------------------mở file------------------------------------------
    FILE *fve = fopen("data/ve/ve.txt","r");
    FILE *fvet = fopen("data/ve/TEMP_ve.txt","w");
    //-----------------------------kiểm tra--------------------------
    if (fve == NULL)
    {
        printf("error: ve.txt\n");
        exit(1);
    }
    //-------------------
    if (fvet == NULL)
    {
        printf("error: TEMP_ve.txt\n");
        exit(1);
    }
    //---------------------đếm số lượng vé máy bay còn lại-----------
    char linevesl[200];
    while (fgets(linevesl, 200, fve) != NULL)
    {
        check = 0;
        ve = read_ve(linevesl);
        for (int i = 0; i < sizecb; i++)
        {
            if (strcmp(ve.macb, maCb[i]) == 0)
                check = 1;
        }
        if (check == 1)
        {
            Write_ve(fvet, ve);
        }
    }
    //----------------------------------------------đóng file-----------------------------------------
    fclose(fve);
    fclose(fvet);
    remove("data/ve/ve.txt");
    rename("data/ve/TEMP_ve.txt","data/ve/ve.txt");
}

// lọc ghế ngồi theo chuyến bay đã xoá or chuyến bay đã bị huỷ
void Filtering_chair()
{
    Filtering_flight();
    // khởi tạo biến
    CB cb;
    GHE ghe;
    int sizecb = 0, demcb = 0, check;
    //-----------------------------------------------mở file------------------------------------------
    FILE * fcb = fopen("data/chuyen_bay/flight.txt","r");
    //--------------------------kiểm tra mở file--------------------------
    if (fcb == NULL)
    {
        printf("error: flight.txt\n");
        exit(1);
    }
    //------------------------------lấy số lượng chuyến bay hiện tại------------
    char linecbht[150];
    while (fgets(linecbht, 150, fcb) != NULL)
    {
        sizecb++;
    }
    rewind(fcb);// đặt con trỏ về lại đầu file
    // tạo mảng chứa mã chuyến bay
    char maCb[sizecb][10];
    //--------------------------kiểm tra tồn tại--------------------------
    char linecb[150];
    while (fgets(linecb, 150, fcb) != NULL)
    {
        cb = read_cb(linecb);
        strcpy(maCb[demcb],cb.maCB);
        demcb++;
    }
    //----------------------------------------------đóng file-----------------------------------------
    fclose(fcb);
    //-----------------------------------------------mở file------------------------------------------
    FILE *fghe = fopen("data/chuyen_bay/Chair.txt", "r");
    FILE *fghet = fopen("data/chuyen_bay/TEMP_Chair.txt", "w");
    //--------------------kiểm tra mở file----------------------------
    if (fghe == NULL)
    {
        printf("error: Chair.txt\n");
        exit(1);
    }
    //---------------------tìm ma cb ghe--------------------------------
    char lineghe[200];
    while (fgets(lineghe, 200, fghe) != NULL)
    {
        check = 0;
        ghe = read_chair(lineghe);
        for (int i = 0; i < sizecb; i++)
        {
            if (strcmp(ghe.macb, maCb[i]) == 0)
                check = 1;
        }
        
        if (check == 1)
        {
            write_chair(fghet,ghe);
        }
    }
    //----------------------------------------------đóng file-----------------------------------------
    fclose(fghe);
    fclose(fghet);
    remove("data/chuyen_bay/Chair.txt");
    rename("data/chuyen_bay/TEMP_Chair.txt","data/chuyen_bay/Chair.txt");
}

#endif//FILTERING_H