#ifndef REMOVE_H
#define REMOVE_H

// file.h
#include "Ql_struct.h"
#include "Clear_spaces.h"
#include "Filtering.h"
#include "Output.h"

// xoá chuyến bay
int remove_flight()
{
    // khởi tạo biến
    CB cb;
    int dem = 0;


    system("cls");
    Filtering_flight();
    //-----------------mở file
    FILE * fcb = fopen("data/chuyen_bay/flight.txt","r");
    //-----------------kiểm tra mở file
    if (fcb == NULL)
    {
        printf("error: flight.txt\n");
        exit(1);
    }
    //-----------------xuất
    dem = Output_flight_file(fcb);
    if (dem == 0)
    {
        system("cls");
        printf("\t\nHIEN KHONG CO CHUYEN BAY NAO!!!\n");
        fclose(fcb);
        return 0;
    }
    rewind(fcb);
    //-----------------nhập mã chuyến bay cần xoá
    printf("Nhap ma chuyen bay can HUY: ");
    getchar();
    char ma[10];
    fgets(ma, 10, stdin);
    ma[strlen(ma) - 1] ='\0';
    system("cls");
    //----------------mở file
    FILE * fcbt = fopen("data/chuyen_bay/TEMP_flight.txt","w");
    //----------------kiểm tra mở file
    if (fcbt == NULL)
    {
        printf("error: TEMP_flight.txt\n");
        exit(1);
    }
    //----------------tìm và sao lưu
    char linecb[150];
    while (fgets(linecb, 150, fcb) != NULL)
    {       
        cb = read_cb(linecb);
        if (strcmp(ma, cb.maCB) != 0)
        {
            write_cb(fcbt, cb);
        }
    }
    //----------------đóng và xoá
    fclose(fcb);
    fclose(fcbt);
    remove("data/chuyen_bay/flight.txt");
    rename("data/chuyen_bay/TEMP_flight.txt","data/chuyen_bay/flight.txt");
    Filtering_ticket();
    Filtering_chair();
    printf("HUY thanh cong!!!\nBam phim bat ki de thoat...\n");
    getch();
    system("cls");
    return 0;
}

// xoá vé
int remove_ticket()
{
    // khởi tạo biến
    VE ve, ve1;
    HK hk;
    int demv = 0;


    char id[15], ma[10];

    Filtering_ticket();
    //----------------mở file
    FILE *fve = fopen("data/ve/ve.txt","r");
    FILE *fvet = fopen("data/ve/TEMP_ve.txt","w");
    //----------------kiểm tra mở file
    if (fve == NULL)
    {
        printf("error: ve.txt\n");
        exit(1);
    }
    //----------------
    if (fvet == NULL)
    {
        printf("error: TEMP_ve.txt\n");
        exit(1);
    }
    //-----------------------------------USER
    if (check_tk == 2)
    {
        // lấy thông tin tài khoản
        hk = Seatch_profile_user_account();
        char lineus[200];
        while(fgets(lineus, 200, fve) != NULL)
        {
            ve1 = read_ve(lineus);
            if (strcmp(hk.id,ve1.mahk) == 0)
            {
                display_ve(ve1);
            }
            demv++;
           
        }
        if (demv == 0)
        {
            printf("\n\tKHONG CO VE NAO!!!\n");
            printf("Bam phim bat ki de thoat...\n");
            getch();
            fclose(fve);
            fclose(fvet);
            remove("data/ve/TEMP_ve.txt");
            system("cls");
            return 0;
        }
        strcpy(id, hk.id);
    }
    
    //----------------------------------ADMIN
    if (check_tk == 1)
    {
        getchar();
        //----------------xuất
        demv = Output_ticket(fve);
        if (demv == 0)
        {
            printf("\n\tKHONG CO VE NAO!!!\n");
            printf("Bam phim bat ki de thoat...\n");
            getch();
            fclose(fve);
            fclose(fvet);
            remove("data/ve/TEMP_ve.txt");
            system("cls");
            return 0;
        }
        //----------------nhập id để xoá
        printf("Nhap ID nguoi can huy ve: ");
        fgets(id, 15, stdin);
        id[strlen(id) - 1 ] = '\0';
    }
    printf("Nhap ma chuyen bay can huy: ");
    fgets(ma, 10, stdin);
    ma[strlen(ma) - 1] = '\0';
    // đưa về đâu file
    rewind(fve);
    //----------------xoá
    char lineve[200];
    while (fgets(lineve, 200, fve) != NULL)
    {
        ve = read_ve(lineve);
        if (strcmp(id, ve.mahk) != 0 || (strcmp(id, ve.mahk) == 0 && strcmp(ma, ve.macb) != 0))
        {
            Write_ve(fvet,ve);
        }
    }
    
    //---------------đóng và xoá file
    fclose(fve);
    fclose(fvet);
    remove("data/ve/ve.txt");
    rename("data/ve/TEMP_ve.txt","data/ve/ve.txt");
    printf("HUY thanh cong!!!\nBam phim bat ki de thoat...\n");
    getch();
    system("cls");
    return 0;
}

// menu xoá
void menu_remove()
{
    system("cls");
    printf("==================Huy===================\n");
    printf("\t1.Huy chuyen bay\n\t2.Huy ve\n\t3.Thoat\n");
    printf("Chon: ");
    int chon;
    scanf("%d", &chon);
    system("cls");
    switch (chon)
    {
        case 1:
        {
            remove_flight();
            break;
        }
        case 2:
        { 
            remove_ticket();
            break;
        }
        case 3:
            break;
    }
}

#endif//REMOVE_H