#ifndef SEARCH_H
#define SEARCH_H

// file.h
#include "Ql_struct.h"
#include "Update_time.h"
#include "Read_Write.h"

// tìm vé máy bay theo mã chuyến bay
int Search_ticket_macb(char macb[])
{
    // khai báo biến
    VE ve;
    //--------------------------mở file-----------------------
    FILE * fve = fopen("data/ve/ve.txt","r");
    FILE * fvet = fopen("data/ve/TEMP_ve.txt","w");
    //---------------kiểm tra mở file-----------------
    if (fve == NULL)
    {   
        printf("error: ve.txt");
        exit(1);
    }
    //----------
    if (fvet == NULL)
    {   
        printf("error: TEMP_ve.txt");
        exit(1);
    }
    //-------------------------tìm kiếm---------------------
    char lineve[200];
    while (fgets(lineve,200,fve) != 0)
    {
        ve = read_ve(lineve);
        if (strcmp(ve.macb, macb) == 0)
        {
            Write_ve(fvet, ve);
        }      
    }
    //-------------------------đóng file-----------------------
    fclose(fve);
    fclose(fvet);
    return 0;
}

// tìm vé máy bay theo id
int Search_ticket_id(char id[])
{
    // khai báo biến
    VE ve;
    //--------------------------mở file-----------------------
    FILE * fve = fopen("data/ve/ve.txt","r");
    FILE * fvet = fopen("data/ve/TEMP_ve.txt","r");
    //---------------kiểm tra mở file-----------------
    if (fve == NULL)
    {   
        printf("error: ve.txt");
        exit(1);
    }
    //----------
    if (fvet == NULL)
    {   
        printf("error: TEMP_ve.txt");
        exit(1);
    }
    //-------------------------tìm kiếm---------------------
    char lineve[200];
    while (fgets(lineve,200,fve) != 0)
    {
        ve = read_ve(lineve);
        if (strcmp(ve.mahk, id) == 0)
        {
            Write_ve(fvet, ve);
        }      
    }
    //-------------------------đóng file-----------------------
    fclose(fve);
    fclose(fvet);
    return 0;
}

// tìm chuyến bay theo địa điểm và thời gian
int Seatch_flight_position_time(char tu[], char den[], int ngay, int thang, int nam)
{
    // cập nhật thời gian
    TG tg = Thoi_Gian_Hien_Tai();
    // khai báo biến
    CB cb;
    //---------------------------------------------mở file----------------------------------------
    FILE * fcb_temp = fopen("data/chuyen_bay/TEMP_flight.txt","w");
    FILE * fcb = fopen("data/chuyen_bay/flight.txt","r");
    //-------------------------kiểm tra mở file-------------------------------
    if (fcb_temp == NULL)
    {
        printf("error: TEMP_rlight.txt");
        exit(1);
    }
    //------------------
    if (fcb == NULL)
    {
        printf("error: rlight.txt");
        exit(1);
    }
    //-------------------------tìm và sao lưu---------------------------------
    char linecb[150];
    while (fgets(linecb,150,fcb) != NULL)
    {
        cb = read_cb(linecb);
        if (strcmp(cb.tu, tu) == 0 && strcmp(cb.den, den) == 0)
        {
            
            if (cb.ngayBay.tm_mday == ngay && thang == cb.ngayBay.tm_mon && nam == cb.ngayBay.tm_year)
            {
                if (ngay == tg.tm_mday && thang == tg.tm_mon)// có phải là ngày hiện tại không
                {
                    if (cb.ngayBay.tm_hour > tg.tm_hour || (cb.ngayBay.tm_hour == tg.tm_hour && cb.ngayBay.tm_min > tg.tm_min))
                    {
                        write_cb(fcb_temp,cb);
                    }
                }
                else
                {
                    write_cb(fcb_temp,cb);
                }
            }
        }
    }
    //--------------------------------------------đóng file---------------------------------------
    fclose(fcb);
    fclose(fcb_temp);
    return 0;
}

// tìm thông tin khach hàng theo tên tk
HK Seatch_profile_user_account()
{
    // khởi tạo biến
    HK hk;
    //---------------------mở file-----------------------
    FILE *fhk = fopen("data/hanh_khach/profile_user.txt", "r");
    //-------------------kiểm tra mở file----------------
    if (fhk == NULL)
    {
        printf("error: profile_user.txt");
        exit(1);
    }
    //---------------------lấy thông tin-----------------
    char linehk[150];
    while (fgets(linehk, 150, fhk) != NULL)
    {
        hk = read_user(linehk);
        if (strcmp(tk_login, hk.tk) == 0)
        {
            fclose(fhk);
            return hk;
        }
    }
    //--------------------đóng file----------------------
    fclose(fhk);
    return hk;
}

// tìm vé máy bay theo id
void Seatch_ticket_id_user(char id[])
{
    // khai báo biến
    VE ve;
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
    //---------------------tìm vé theo id----------------------------
    char linevesl[200];
    while (fgets(linevesl, 200, fve) != NULL)
    {
        ve = read_ve(linevesl);
        if (strcmp(ve.mahk, id) == 0)
        {
            Write_ve(fvet, ve);
        }
    }
    //----------------------------------------------đóng file-----------------------------------------
    fclose(fve);
    fclose(fvet); 
}

#endif//SEARCH_H