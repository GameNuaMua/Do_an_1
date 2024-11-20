#ifndef INPUT_H
#define INPUT_H

// file.h
#include "Ql_struct.h"
#include "Update_time.h"
#include "Read_Write.h"
#include "Chair.h"

// nhập thông tin khách hàng với mua = tk_login nếu thêm = "khong co"
HK input_profile_user(FILE *file, char taikhoan[])
{
    while(1)
    {
        // khai báo biến
        int check = 0;
        int chon;
        char tk[50];// tài khoản đã đăng ký
        char id[15];// mã hành khách
        char ten[50];// tên hành khách
        char gioiTinh[50];// giới tính
        char quocTich[50];// quốc tịch
        int tuoi;// tuổi
        char sdt[15];// số điện thoại
        struct tm ngaySinh;// ngày sinh
        //--------------------tài khoản
        strcpy(tk, taikhoan);
        //--------------------ID
        printf("ID: ");
        fgets(id,sizeof(id),stdin);
        id[strlen(id) - 1] = '\0';
        //---------------------check id-----------------------
        //---------kiểm tra tồn tại-------------
        HK hk;
        char linehk[200];
        rewind(file);
        while (fgets(linehk,200,file) != NULL)
        {
            hk = read_user(linehk);
            if (strcmp(id, hk.id) == 0)
            {
                check = 1;
                break;
            }
        }
        if (check == 1)
        {
            system("cls");
            printf("!!!-ID da ton tai-!!!\n");
            continue;
        }//-------------------------------------------kiểm tra xong-----------------------
        //--------------------tên
        printf("Ten: ");
        fgets(ten,sizeof(ten),stdin);
        ten[strlen(ten) - 1] = '\0';
        //--------------------giới tính
        printf("\t1.Nam\n\t2.Nu\n");
        printf("Chon: ");
        scanf("%d",&chon);
        switch (chon)
        {
            case 1:
                strcpy(gioiTinh, "nam");
                break;
            case 2:
                strcpy(gioiTinh, "nu");
                break;
        }
        printf("Gioi Tinh: %s\n", gioiTinh);
        //--------------------quốc tịch
        printf("Quoc Tich: ");
        getchar();
        fgets(quocTich,sizeof(quocTich),stdin);
        quocTich[strlen(quocTich) - 1] = '\0';
        //--------------------số điện thoại
        printf("SDT: ");
        fgets(sdt,sizeof(sdt),stdin);
        sdt[strlen(sdt) - 1] = '\0';
        //--------------------ngày tháng năm sinh
        printf("Ngay Sinh(dd mm yyyy): ");
        scanf("%d %d %d", &ngaySinh.tm_mday, &ngaySinh.tm_mon, &ngaySinh.tm_year);
        //--------------------tuổi
        TG tg = Thoi_Gian_Hien_Tai();
        tuoi = tg.tm_year - ngaySinh.tm_year;
        //----------------------------------------------------------------gán các giá trị mới--
        strcpy(hk.tk, tk);
        strcpy(hk.id, id);
        strcpy(hk.ten, ten);
        strcpy(hk.gioiTinh, gioiTinh);
        strcpy(hk.quocTich, quocTich);
        strcpy(hk.sdt, sdt);
        hk.tuoi = tuoi;
        hk.ngaySinh.tm_mday = ngaySinh.tm_mday;
        hk.ngaySinh.tm_mon = ngaySinh.tm_mon;
        hk.ngaySinh.tm_year = ngaySinh.tm_year;
        //-------------------------------------------------------------------gán thành công----
        write_hk(file, hk);
        fclose(file);
        return hk;
        break;
    }
}

// thêm chuyến bay
int add_flight()
{
    while(1)
    {
        // khởi tạo biến
        CB cb;
        CB cb_temp;
        int check = 0;
        //-------------------mã chuyến bay
        printf("Ma: ");
        fgets(cb_temp.maCB,10,stdin);
        cb_temp.maCB[strlen(cb_temp.maCB) - 1] = '\0';
        //---------------------------------------kiểm tra mã chuyến bay có tồn tại không-------------------
        //----------------------------mở file----------------------
        FILE * fcb = fopen("data/chuyen_bay/flight.txt","a+");
        //----------kiểm tra mở file--------
        if (fcb == NULL)
        {
            printf("error: filght.txt\n");
            exit(1);
        }
        //--------------------------kiểm tra tồn tại-----------------
        char linecb[200];
        while (fgets(linecb, 200, fcb) != NULL)
        {
            cb = read_cb(linecb);
            if (strcmp(cb.maCB, cb_temp.maCB) == 0)
            {
                check = 1;
                break;
            }
        }
        if (check == 1)
        {
            system("cls");
            printf("!!!-Ma chuyen bay da ton tai-!!!\n");
            continue;
        }//--------------------------------check xong--------------
        //---------------------------tạo ghế ngồi cho chuyến bay-------------
        Chair_create(cb_temp.maCB);
        //----------------------------hãng
        printf("Hang: ");
        fgets(cb_temp.hang,sizeof(cb_temp.hang),stdin);
        cb_temp.hang[strlen(cb_temp.hang) - 1] = '\0';
        //----------------------------từ đâu
        printf("Tu: ");
        fgets(cb_temp.tu,sizeof(cb_temp.tu),stdin);
        cb_temp.tu[strlen(cb_temp.tu) - 1] = '\0';
        //----------------------------đến đâu
        printf("Den: ");
        fgets(cb_temp.den,sizeof(cb_temp.den),stdin);
        cb_temp.den[strlen(cb_temp.den) - 1] = '\0';
        //----------------------------ngày tháng năm bay
        printf("Ngay bay(dd mm yyyy): ");
        scanf("%d %d %d",&cb_temp.ngayBay.tm_mday, &cb_temp.ngayBay.tm_mon, &cb_temp.ngayBay.tm_year);
        //----------------------------giờ bay
        printf("Gio bay(hh mm): ");
        scanf("%d %d",&cb_temp.ngayBay.tm_hour, &cb_temp.ngayBay.tm_min);
        //----------------------------ngày tháng năm đến
        printf("Ngay den(dd mm yyyy): ");
        scanf("%d %d %d",&cb_temp.ngayDen.tm_mday, &cb_temp.ngayDen.tm_mon, &cb_temp.ngayDen.tm_year);
        //----------------------------giờ đến
        printf("Gio den(hh mm): ");
        scanf("%d %d",&cb_temp.ngayDen.tm_hour, &cb_temp.ngayDen.tm_min);
        //----------------------------giá vé hạng thương gia
        printf("Gia ve hang 'Thuong Gia': ");
        scanf("%d", &cb_temp.giaCBtg);
        //----------------------------giá vé hạng phổ thông
        printf("Gia ve hang 'Pho Thong': ");
        scanf("%d", &cb_temp.giaCBpth);
        //----------------------------tổng tiền của chuyến bay
        cb_temp.sum = 0;
        //--------------------------------gán giá trị---------
        cb = cb_temp;
        //-----------------------------------in thông tin vào file--------------------
        write_cb(fcb,cb);
        //----------------------------đóng file------------------
        fclose(fcb);
        system("cls");
        printf("Da tao chuyen bay thanh cong ^-^ \n");
        printf("\nBam phim bat ki de thoat...\n");
        getch();
        system("cls");
        return 0;
    }
    return 0;
}
#endif// end INPUT_H