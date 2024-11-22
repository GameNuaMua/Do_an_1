#ifndef PAY_TICKET_H
#define PAY_TICKET_H

// file.h
#include "Ql_struct.h"
#include "Filtering.h"
#include "Search.h"
#include "Sort_flight.h"
#include "Output.h"
#include "Clear_spaces.h"
#include "Chair.h"

// chọn chuyến bay
CB choose_flight(FILE *file)
{
    // khởi tạo biến
    CB cb;
    char ma[10];
    // chọn chuyến bay
    int check;
    while (1)
    {
        // đặt con trỏ về lại đầu file
        rewind(file);
        getchar();
        printf("Chon chuyen bay\n");
        printf("Chon(VD: vn-123): ");
        fgets(ma,10,stdin);
        ma[strlen(ma) - 1] = '\0';
        char linecb[150];
        while (fgets(linecb,150,file) != NULL)
        {
            cb = read_cb(linecb);
            if (strcmp(cb.maCB, ma) == 0)
            {
                //printf("thanh cong\n");
                return cb;
            }
            check = 1;
        }
        if (check == 1)
        {
            continue;
        }
    }
    return cb;
}

// mua vé
void pay_ticket()
{
    // khai báo biến
    VE pay;
    CB cb;
    HK hk;
    int nguoilon = 0, treem = 0;
    int loaive, hangve;
    char taikhoan[20];
    char temp[50];
    //--------bắt đầu-----------
    //-----------------------------từ đâu
    printf("Tu: ");
    fgets(pay.tu, sizeof(pay.tu), stdin);
    pay.tu[strlen(pay.tu) - 1 ] = '\0';
    //-----------------------------đến đâu
    printf("Den: ");
    fgets(pay.den, sizeof(pay.den), stdin);
    pay.den[strlen(pay.den) - 1 ] = '\0';
    //----------------------------ngày đi
    printf("Ngay di(dd mm yyyy): ");
    scanf("%d %d %d", &pay.ngaybay.tm_mday, &pay.ngaybay.tm_mon, &pay.ngaybay.tm_year);
    //----------------------------loại vé
    printf("\t1.Mot Chieu\n");
    printf("\t2.Khu Hoi\n");
    printf("Chon: ");
    scanf("%d", &loaive);
    printf("Bam phim bat ki de xac nhan....\n");
    getch();

    switch (loaive)
    {
        case 1:
        {
            int demcb;
            strcpy(pay.loaive,"mot chieu");
            system("cls");
            Filtering_flight();
            Seatch_flight_position_time(pay.tu, pay.den, pay.ngaybay.tm_mday, pay.ngaybay.tm_mon, pay.ngaybay.tm_year);
            Sort_flight();
            //-------------------mở file
            FILE *filecb = fopen("data/chuyen_bay/TEMP_flight.txt", "r");
            //-------------------kiểm tra mở file
            if (filecb == NULL)
            {
                printf("error: TEMP_flight.txt\n");
                exit(1);
            }
            //-------------------xuất
            demcb = Output_flight_file(filecb);
            if (demcb == 0)
            {
                system("cls");
                printf("\n\tKHONG CO CHUYEN BAY PHU HOP!!!\n");
                fclose(filecb);
                remove("data/chuyen_bay/TEMP_flight.txt");
                printf("Bam phim bat ki de thoat...\n");
                getch();
                system("cls");
                break;
            }
            //---------------------------chọn chuyến bay
            cb = choose_flight(filecb);
            strcpy(pay.macb, cb.maCB);
            strcpy(pay.hang, cb.hang);
            pay.ngaybay.tm_hour = cb.ngayBay.tm_hour;
            pay.ngaybay.tm_min = cb.ngayBay.tm_min;
            pay.ngayden.tm_mday = cb.ngayDen.tm_mday;
            pay.ngayden.tm_mon = cb.ngayDen.tm_mon;
            pay.ngayden.tm_year = cb.ngayDen.tm_year;
            pay.ngayden.tm_hour = cb.ngayDen.tm_hour;
            pay.ngayden.tm_min = cb.ngayDen.tm_min;
            //-------------------close and remove
            fclose(filecb);
            remove("data/chuyen_bay/TEMP_flight.txt");
            printf("Bam phim bat ki de xac nhan....\n");
            getch();
            system("cls");
            
            //-------------------chọn hạng ghế
            printf("\t1.Thuong Gia\n\t2.Pho Thong\n");
            printf("Chon: ");
            scanf("%d", &hangve);
            switch (hangve)
            {
            case 1:
            {
                printf("Hang Ghe: Thuong Gia\n");
                strcpy(pay.hangve,"thuong gia");
                break;
            }
            case 2:
            {
                printf("Hang Ghe: Pho Thong\n");
                strcpy(pay.hangve,"pho thong");
                break;
            }
            }
            //-------------------chọn ghế
            pay.ghe = Choose_seat(hangve, pay.macb);
            if (check_tk == 1)
            {
                strcpy(taikhoan,"khong co");
                //-----------------mở file
                FILE *fus_temp = fopen("data/hanh_khach/TEMP_profile_user.txt", "a");
                //-----------------kiểm tra mở file
                if (fus_temp == NULL)
                {
                    printf("error: TEMP_profile_user.txt");
                    exit(1);
                }
                //-----------------chạy
                hk = input_profile_user(fus_temp, taikhoan);
                //-----------------đóng file
                fclose(fus_temp);
                
            }
            if (check_tk == 2)
            {
                // lấy thông tin từ tk_login
                hk = Seatch_profile_user_account();
            }
            //-----------------------------
            strcpy(pay.mahk, hk.id);
            strcpy(pay.tenhk, hk.ten);
            // tinh gia ve
            pay.giave = giave(hk.tuoi, hangve, cb);
            //------------------mở file
            FILE *fve = fopen("data/ve/ve.txt","a");
            //------------------kiểm tra mở file
            if (fve == NULL)
            {
                printf("error: ve.txt");
                exit(1);
            }
            //------------------sao lưu
            Write_ve(fve, pay);
            //------------------đóng file
            fclose(fve);
            printf("Dat ve thanh cong\nBam phim bat ki de xac nhan...\n");
            getch();
            system("cls");
            break;// exit case 1
        }// case 1
        case 2:
        {
            int demcb1;
            system("cls");
            strcpy(pay.loaive,"khu hoi");
            for (int j = 0; j < 2; j++)
            {
                if (j == 1)
                {
                    strcpy(temp, pay.tu);
                    strcpy(pay.tu, pay.den);
                    strcpy(pay.den, temp);
                    system("cls");
                    printf("Chon chuyen ve:\n");
                    //----------------------------ngày đi
                    printf("Ngay di(dd mm yyyy): ");
                    scanf("%d %d %d", &pay.ngaybay.tm_mday, &pay.ngaybay.tm_mon, &pay.ngaybay.tm_year);
                }
                printf("tu: %s, den: %s, %d/%d/%d\n",pay.tu, pay.den, pay.ngaybay.tm_mday,pay.ngaybay.tm_mon,pay.ngaybay.tm_year);
                //----------------------------chon chuyen bay
                Filtering_flight();
                Seatch_flight_position_time(pay.tu, pay.den, pay.ngaybay.tm_mday, pay.ngaybay.tm_mon, pay.ngaybay.tm_year);
                Sort_flight();
                //-------------------mở file
                FILE *filecb = fopen("data/chuyen_bay/TEMP_flight.txt", "r");
                //-------------------kiểm tra mở file
                if (filecb == NULL)
                {
                    printf("error: TEMP_flight.txt\n");
                    exit(1);
                }
                //-------------------xuất
                demcb1 = Output_flight_file(filecb);
                if (demcb1 == 0)
                {
                    system("cls");
                    printf("\n\tKHONG CO CHUYEN BAY PHU HOP!!!\n");
                    fclose(filecb);
                    remove("data/chuyen_bay/TEMP_flight.txt");
                    printf("Bam phim bat ki de thoat...\n");
                    getch();
                    system("cls");
                    break;// exit case 1
                }
                //---------------------------chọn chuyến bay
                cb = choose_flight(filecb);
                strcpy(pay.macb, cb.maCB);
                strcpy(pay.hang, cb.hang);
                pay.ngaybay.tm_hour = cb.ngayBay.tm_hour;
                pay.ngaybay.tm_min = cb.ngayBay.tm_min;
                pay.ngayden.tm_mday = cb.ngayDen.tm_mday;
                pay.ngayden.tm_mon = cb.ngayDen.tm_mon;
                pay.ngayden.tm_year = cb.ngayDen.tm_year;
                pay.ngayden.tm_hour = cb.ngayDen.tm_hour;
                pay.ngayden.tm_min = cb.ngayDen.tm_min;
                //-------------------close and remove
                fclose(filecb);
                remove("data/chuyen_bay/TEMP_flight.txt");
                printf("Bam phim bat ki de xac nhan....\n");
                getch();
                system("cls");

                //-------------------chọn hạng ghế
                printf("\t1.Thuong Gia\n\t2.Pho Thong\n");
                printf("Chon: ");
                scanf("%d", &hangve);
                switch (hangve)
                {
                case 1:
                {
                    printf("Hang Ghe: Thuong Gia\n");
                    strcpy(pay.hangve,"thuong gia");
                    break;
                }
                case 2:
                {
                    printf("Hang Ghe: Pho Thong\n");
                    strcpy(pay.hangve,"pho thong");
                    break;
                }
                }
                //-------------------chọn ghế
                pay.ghe = Choose_seat(hangve, pay.macb);
                if (j == 0)
                {
                    if (check_tk == 1)
                    {
                        strcpy(taikhoan,"khong co");
                        //-----------------mở file
                        FILE *fus_temp = fopen("data/hanh_khach/TEMP_profile_user.txt", "a");
                        //-----------------kiểm tra mở file
                        if (fus_temp == NULL)
                        {
                            printf("error: TEMP_profile_user.txt");
                            exit(1);
                        }
                        //-----------------chạy
                        hk = input_profile_user(fus_temp, taikhoan);
                        //-----------------đóng file
                        fclose(fus_temp);
                        
                    }
                    if (check_tk == 2)
                    {
                        // lấy thông tin từ tk_login
                        hk = Seatch_profile_user_account();
                    }
                }
                //-----------------------------
                strcpy(pay.mahk, hk.id);
                strcpy(pay.tenhk, hk.ten);
                // tinh gia ve
                pay.giave = giave(hk.tuoi, hangve, cb);
                //------------------mở file
                FILE *fve = fopen("data/ve/ve.txt","a");
                //------------------kiểm tra mở file
                if (fve == NULL)
                {
                    printf("error: ve.txt");
                    exit(1);
                }
                //------------------sao lưu
                Write_ve(fve, pay);
                //------------------đóng file
                fclose(fve);
                if(j == 1)
                {
                    printf("Dat ve thanh cong\nBam phim bat ki de xac nhan...\n");
                    getch();
                    system("cls");
                }
            }
            break;// exit case 2
        }// case 2
    }// switch
}// pay_ticket   

#endif//PAY_TICKET_H