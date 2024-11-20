#ifndef QL_STRUCT_H
#define QL_STRUCT_H
// biến toàn cục
char tk_login[20];// trả về tài khoản để check
//char tk_login[] = "hau";
int check_tk;// admin or user

// thư viện
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// cập nhật thời gian hiện tại
typedef struct tm TG;


// thông tin đăng nhập
struct DangNhap
{
    char tk[20];// tài khoản
    char mk[20];// mật khẩu
    int dem;// đếm số lần đăng nhập
};

// thông tin chuyến bay
struct chuyenBay
{
    char maCB[10];// mã chuyến bay
    char hang[50];// hãng
    char tu[50];// từ
    char den[50];// đến
    struct tm ngayBay;// ngày bay
    struct tm ngayDen;// ngày đến
    int giaCBtg;// giá chuyến bay thương gia
    int giaCBpth;// giá chuyến bay phổ thông
    int sum;// tổng số tiền của chuyến bay
};

// thông tin hành khách
struct HanhKhach
{
    char tk[50];// tài khoản đã đăng ký
    char id[15];// mã hành khách
    char ten[50];// tên hành khách
    char gioiTinh[50];// giới tính
    char quocTich[50];// quốc tịch
    int tuoi;// tuổi
    char sdt[15];// số điện thoại
    struct tm ngaySinh;// ngày sinh
};

// thông tin vé bay
struct ve
{
    char mahk[15];// mã hành khách
    char tenhk[50];// tên hành khách
    char macb[10];// mã chuyến bay
    char hang[50];// hãng
    char tu[50];// từ
    char den[50];// đến
    char loaive[50];// loại vé
    char hangve[50];// hạng vé
    int ghe;
    struct tm ngaybay;// ngày bay
    struct tm ngayden;// ngày đến
    int giave;// giá vé
};

// quản lý ghế ngồi của chuyến bay
struct ghe
{
    char macb[10];
    int ghe[30];
    int con_lai;
};

typedef chuyenBay CB;
typedef HanhKhach HK;
typedef ve VE;
typedef DangNhap DN;
typedef ghe GHE;

#endif// end QL_STRUCT_H