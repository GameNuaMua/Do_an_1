#ifndef SUA_H
#define SUA_H

#include "Ql_struct.h"
#include "Read_Write.h"
#include "Filtering.h"
#include "Output.h"

// chọn chuyến bay cần sửa
void sua_cb()
{
    system("cls");
    //khai báo biến
    CB cb;
    char macbsua[10];


    // mở file
    FILE *f = fopen("data/chuyen_bay/flight.txt", "r");
    FILE *f1 = fopen("data/chuyen_bay/TEMP_flight.txt", "w");
    // kiểm tra file có tồn tại không
    if (f == NULL || f1 == NULL)
    {
        printf("File khong ton tai\n");
        exit(1);
    }


    Filtering_flight();
    Output_flight_file(f);
    // đưa con trỏ về lại đầu file
    rewind(f);


    // Nhập mã chuyến bay cần sửa
    //getchar();
    printf("Nhap ma chuyen bay can sua: ");
    fgets(macbsua, sizeof(macbsua), stdin);
    macbsua[strlen(macbsua) - 1] = '\0';
    system("cls");



    // đọc file
    char linesuacb[150];
    int found = 0;
    while (fgets(linesuacb, sizeof(linesuacb), f) != NULL)
    {
        cb = read_cb(linesuacb);
        if (strcmp(cb.maCB, macbsua) == 0)
        {
            //------------------------tiêu đề-----------------------------
            printf("======================================================================DANH SACH CHUYEN BAY====================================================================\n");
            printf(" %-10s | %-20s | %-12s | %-12s | %-11s | %-10s | %-11s | %-10s | %-10s | %-10s | %-15s\n",
            "Ma", "Hang", "Tu", "Den", "Ngay di", "Gio Di", "Ngay den", "Gio Den", "Thuong Gia", "Pho Thong", "Tong Tien");
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

            // in ra chuyến bay cần sửa
            display_cb(cb);

            // cập nhật thời gian bay
            printf("Nhap ngay bay moi (dd mm yyyy): ");
            scanf("%d %d %d", &cb.ngayBay.tm_mday, &cb.ngayBay.tm_mon, &cb.ngayBay.tm_year);
            printf("Nhap gio bay moi (hh mm): ");
            scanf("%d %d", &cb.ngayBay.tm_hour, &cb.ngayBay.tm_min);
            printf("Nhap ngay den moi (dd mm yyyy): ");
            scanf("%d %d %d", &cb.ngayDen.tm_mday, &cb.ngayDen.tm_mon, &cb.ngayDen.tm_year);
            printf("Nhap gio den moi (hh mm): ");
            scanf("%d %d", &cb.ngayDen.tm_hour, &cb.ngayDen.tm_min);

            // cập nhật vào file temp
            write_cb(f1, cb);
            found = 1;
        }
        else
        {
            write_cb(f1, cb);
        }
    }
    if (found == 0)
    {
        printf("Chuyen bay khong ton tai\n");
        getch();
    }
    fclose(f);
    fclose(f1);
    remove("data/chuyen_bay/flight.txt");
    rename("data/chuyen_bay/TEMP_flight.txt", "data/chuyen_bay/flight.txt"); // đổi tên file temp 
    system("cls");
    printf("Thay doi thanh cong ^-^\nBam phim bat ki de thoat...\n");
    getch();
    system("cls");
}

// sửa thông tin hành khách f là profile_user(r), f1 là Temp_profile_user(w)
void sua_hk(FILE *f, FILE *f1, char idsua[])
{
    // khởi tạo biến
    HK hk;


    // mở file
    if (f == NULL || f1 == NULL)
    {
        printf("File khong ton tai\n");
        getch();
        exit(1);
    }


    char linesuahk[150];
    int found = 0;
    while (fgets(linesuahk, sizeof(linesuahk), f) != NULL)
    {
        hk = read_user(linesuahk);
        if (strcmp(hk.id, idsua) == 0)
        {
            //-----------------------------tiêu đề------------------------------------------
            printf("=================================================DANH SACH HANH KHACH VS KHACH HANG=====================================================\n");
            printf(" %-20s | %-15s | %-20s | %-13s | %-13s | %-13s | %-10s | %-15s\n",
                    "Tai Khoan", "ID", "Ten", "Gioi Tinh", "Quoc Tich", "SDT", "Tuoi", "Ngay Sinh");
            printf("----------------------------------------------------------------------------------------------------------------------------------------\n");


            // in ra hanh khach cần sửa
            display_user(hk);

            printf("Ban muon sua gi!\n");
            printf("\t1.Ten\n\t2.Gioi Tinh\n\t3.Quoc Tich\n\t4.SDT\n\t5.Ngay Sinh\n");
            int chon;
            printf("Chon: ");
            scanf("%d", &chon);
            getchar();

            switch (chon)
            {
                case 1:
                {
                    // cập nhật thông tin hanh khach
                    printf("Nhap ten hanh khach: ");
                    fgets(hk.ten, sizeof(hk.ten), stdin);
                    hk.ten[strlen(hk.ten) - 1] = '\0';
                    break;
                }
                case 2:
                {
                    printf("Nhap gioi tinh: ");
                    fgets(hk.gioiTinh, sizeof(hk.gioiTinh), stdin);
                    hk.gioiTinh[strlen(hk.gioiTinh) - 1] = '\0';
                    break;
                }
                case 3:
                {
                    printf("Nhap quoc tich: "); 
                    fgets(hk.quocTich, sizeof(hk.quocTich), stdin);
                    hk.quocTich[strlen(hk.quocTich) - 1] = '\0';
                    break;
                }
                case 4:
                {
                    printf("Nhap so dien thoai: ");
                    fgets(hk.sdt, sizeof(hk.sdt), stdin);
                    hk.sdt[strlen(hk.sdt) - 1] = '\0';
                    break;
                }
                case 5:
                {
                    printf("Nhap ngay sinh (dd/mm/yyyy): ");
                    scanf("%d %d %d", &hk.ngaySinh.tm_mday, &hk.ngaySinh.tm_mon, &hk.ngaySinh.tm_year);
                    break;
                }
            }
            // cập nhật vào file temp
            write_hk(f1, hk);
            found = 1;
        }
        else
        {
            write_hk(f1, hk);
        }
    }
    
    if (found == 0)
    {
        printf("Hanh khach khong ton tai\n");
    }
    fclose(f);
    fclose(f1);
}

void menu_sua()
{
    int choice;
    do 
    {
        system("cls");
        printf("==========================MENU SUA==========================\n");
        printf("\t\t1.Sua chuyen bay\n");
        printf("\t\t2.Sua hanh khach\n");
        printf("\t\t3.Thoat\n");
        printf("chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            sua_cb();
            break;
        case 2:
        {   
            system("cls");
            // xuất danh sách user profile
            FILE *file = fopen("data/hanh_khach/TEMP_profile_user.txt", "r");
            Output_user(file);
            fclose(file);


            // Nhập số cccd cần chỉnh sửa
            char idsua[15];
            printf("Nhap CCCD cua hanh khach can sua: ");
            fgets(idsua, sizeof(idsua), stdin);
            idsua[strlen(idsua) - 1] = '\0';
            system("cls");


            FILE *f = fopen("data/hanh_khach/TEMP_profile_user.txt", "r");
            FILE *f1 = fopen("data/hanh_khach/t_profile_user.txt", "w");
            sua_hk(f, f1, idsua);
            fclose(f);
            fclose(f1);
            remove("data/hanh_khach/TEMP_profile_user.txt");
            rename("data/hanh_khach/t_profile_user.txt","data/hanh_khach/TEMP_profile_user.txt");
            system("cls");
            printf("Thay doi thanh cong ^-^\nBam phim bat ki de thoat...\n");
            getch();
            system("cls");
            break;
        }
        case 3:
            system("cls");
            break;
        default:
            printf("Lua chon khong hop le\n");
            exit(1);
        }
    }while (choice != 3);
}

#endif // SUA_H
