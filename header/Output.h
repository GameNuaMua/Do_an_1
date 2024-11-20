#ifndef OUTPUT_H
#define OUTPUT_H

// file.h
#include "Ql_struct.h"
#include "Sum.h"
#include "Search.h"
#include "Read_Write.h"

// xuất danh sách vé theo mã chuyến bay
void Output_ticket(FILE *file)
{
    // khai báo biến
    VE ve;
    //--------------------tiêu đề---------------------------
    printf("================================================================================================DANH SACH VE======================================================================================================\n");
    printf(" %-15s | %-20s | %-10s | %-20s | %-12s | %-12s | %-12s | %-12s | %-6s | %-11s | %-10s | %-11s | %-10s | %-15s\n",
    "ID", "Ten", "Ma CB", "Hang", "Tu", "Den", "Loai Ve", "Hang Ve", "Ghe", "Ngay Di", "Gio Di", "Ngay Den", "Gio Den",
    "Gia Ve");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    //-------------------xuất danh sách---------------------
    char lineve[200];
    //987239321 | nguyen van anh | vn-999 | vietnam airline | da nang | ho chi minh | mot chieu | pho thong | 13 19 11 2024 5 0 19 11 2024 7 15 1700000
    while (fgets(lineve,200,file) != 0)
    {
        ve = read_ve(lineve);
        display_ve(ve);
    }
}

// xuất danh sách hành khách và khách hàng
int Output_user(FILE *fhk)
{
    // khởi tạo biến
    HK hk;


    //-----------------------------tiêu đề------------------------------------------
    printf("=================================================DANH SACH HANH KHACH VS KHACH HANG=====================================================\n");
    printf(" %-20s | %-15s | %-20s | %-13s | %-13s | %-13s | %-10s | %-15s\n",
            "Tai Khoan", "ID", "Ten", "Gioi Tinh", "Quoc Tich", "SDT", "Tuoi", "Ngay Sinh");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    
    
    //---------------------------------kiểm tra mở file------------------------
    if (fhk == NULL)
    {
        printf("error: profile_user.txt\n");
        return 1;
    }


    //-----------------------------------đọc file và xuất-----------------------
    char lineuser[150];
    while (fgets(lineuser, 150, fhk) != NULL)
    {
        hk = read_user(lineuser);
        display_user(hk);
    }


    //------------------------------------------đóng file-----------------------------------------------
    fclose(fhk);
    return 0;
}

// xuất danh sách chuyến bay
int Output_flight_file(FILE *file)
{
    // khởi tạo biến
    CB cb;
    //------------------------tiêu đề-----------------------------
    printf("======================================================================DANH SACH CHUYEN BAY====================================================================\n");
    printf(" %-10s | %-20s | %-12s | %-12s | %-11s | %-10s | %-11s | %-10s | %-10s | %-10s | %-15s\n",
    "Ma", "Hang", "Tu", "Den", "Ngay di", "Gio Di", "Ngay den", "Gio Den", "Thuong Gia", "Pho Thong", "Tong Tien");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    //------------------------đọc file----------------------------
    char linecb[150];
    while (fgets(linecb,150,file) != NULL)
    {
        cb = read_cb(linecb);
        if (check_tk == 1)
        {
            cb.sum = Sum(cb.maCB);
        }
        display_cb(cb);
    }
    return 0;
}

// menu xuất ds chuyến bay và hành khách
int menu_output()
{
    int choice;
    do
    {
        //----------------------------------menu xuat------------------------------
        printf("======================XUAT======================\n");
        printf("\t1.Xuat danh sach cac chuyen bay\n\t2.Xuat danh sanh khach hang\n\t3.Thoat\n");
        printf("================================================\n");
        printf("Chon: ");
        scanf("%d",&choice);
        system("cls");
        //-----------------------------lựa chọn-----------------------------------
        switch (choice)
        {
        case 1:
        {
            //--------------------------mở file-----------------------
            FILE * fcb = fopen("data/chuyen_bay/flight.txt","r");
            //---------------kiểm tra mở file-----------------
            if (fcb == NULL)
            {   
                printf("error: flight.txt");
                exit(1);
            }
            //------------------------------------------------
            Output_flight_file(fcb);
            //--------------------------------thêm lựa chọn--------------------------
            int chon;
            printf("===================XEM THEM=====================\n");
            printf("\t1.Xuat danh sach ve\n\t2.Thoat\n");
            printf("================================================\n");
            printf("Chon: ");
            scanf("%d", &chon);
            getchar();
            //---------------------------
            switch (chon)
            {
                case 1:
                {
                    char macb[10];
                    printf("Nhap ma chuyen bay: ");
                    fgets(macb, 10, stdin);
                    macb[strlen(macb) - 1] = '\0';
                    system("cls");
                    //-----------------------------------chạy chương trình----------------------
                    Search_ticket_macb(macb);
                    //--------------------------mở file-----------------------
                    FILE * fvet = fopen("data/ve/TEMP_ve.txt","r");
                        //---------------kiểm tra mở file-----------------
                    if (fvet == NULL)
                        {   
                            printf("error: TEMP_ve.txt");
                            exit(1);
                        }
                    Output_ticket(fvet);
                    //-------------------------đóng file-----------------------
                    fclose(fvet);
                    remove("data/ve/TEMP_ve.txt");
                    printf("Bam phim bat ki de thoat...\n");
                    getch();
                    system("cls");
                    break;
                }
                case 2:
                    system("cls");
                    break;
                default:
                    printf("Lua chon khong hop le\n");
                    break;
            }
            //-------------------------đóng file----------------------
            fclose(fcb);
            break;
        }
        case 2:
        {
            FILE *f = fopen("data/hanh_khach/profile_user.txt", "r");
            FILE *f1 = fopen("data/hanh_khach/TEMP_profile_user.txt", "r");
            Output_user(f);
            Output_user(f1);
            fclose(f);
            fclose(f1);
            printf("Bam phim bat ki de thoat...");
            getch();
            system("cls");
            break;
        }           
        case 3:
            system("cls");
            break;
        default:
            printf("Lua chon khong hop le\n");
            break;
        }
    }while (choice != 3);
    return 0;
}
#endif//OUTPUT_H