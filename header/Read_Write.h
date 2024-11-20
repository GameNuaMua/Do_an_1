#ifndef READ_WRITE_H
#define READ_WRITE_H

// file.h
#include "Ql_struct.h"
#include "Clear_spaces.h"

// gán giá trị cho ve
VE read_ve(char line[])
{
    VE ve;
    sscanf(line,"%[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %d %d %d %d %d %d %d %d %d %d %d %d",
    ve.mahk, ve.tenhk, ve.macb, ve.hang, ve.tu, ve.den, ve.loaive, ve.hangve, &ve.ghe,
    &ve.ngaybay.tm_mday, &ve.ngaybay.tm_mon, &ve.ngaybay.tm_year, &ve.ngaybay.tm_hour, &ve.ngaybay.tm_min,
    &ve.ngayden.tm_mday, &ve.ngayden.tm_mon, &ve.ngayden.tm_year, &ve.ngayden.tm_hour, &ve.ngayden.tm_min,
    &ve.giave);
    trim(ve.mahk);
    trim(ve.tenhk);
    trim(ve.macb);
    trim(ve.hang);
    trim(ve.tu);
    trim(ve.den);
    trim(ve.loaive);
    trim(ve.hangve);
    return ve;
}

// ghi vé vào file
void Write_ve(FILE *file,VE ve)
{
    fprintf(file,"%s | %s | %s | %s | %s | %s | %s | %s | %d %d %d %d %d %d %d %d %d %d %d %d\n",
    ve.mahk, ve.tenhk, ve.macb, ve.hang, ve.tu, ve.den, ve.loaive, ve.hangve, ve.ghe,
    ve.ngaybay.tm_mday, ve.ngaybay.tm_mon, ve.ngaybay.tm_year, ve.ngaybay.tm_hour, ve.ngaybay.tm_min,
    ve.ngayden.tm_mday, ve.ngayden.tm_mon, ve.ngayden.tm_year, ve.ngayden.tm_hour, ve.ngayden.tm_min,
    ve.giave);
}

// gán giá trị cho cb
CB read_cb(char line[])
{
    CB cb;
    sscanf(line,"%[^|]| %[^|]| %[^|]| %[^|]| %d %d %d %d %d %d %d %d %d %d %d %d %d",
    cb.maCB, cb.hang, cb.tu, cb.den, 
    &cb.ngayBay.tm_mday, &cb.ngayBay.tm_mon, &cb.ngayBay.tm_year, &cb.ngayBay.tm_hour, &cb.ngayBay.tm_min,
    &cb.ngayDen.tm_mday, &cb.ngayDen.tm_mon, &cb.ngayDen.tm_year, &cb.ngayDen.tm_hour, &cb.ngayDen.tm_min,
    &cb.giaCBtg, &cb.giaCBpth, &cb.sum);
    trim(cb.maCB);
    trim(cb.hang);
    trim(cb.tu);
    trim(cb.den);
    return cb;
}

// ghi cb vào file
void write_cb(FILE *file, CB cb)
{
    fprintf(file, "%s | %s | %s | %s | %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 
    cb.maCB, cb.hang, cb.tu, cb.den, 
    cb.ngayBay.tm_mday, cb.ngayBay.tm_mon, cb.ngayBay.tm_year, cb.ngayBay.tm_hour, cb.ngayBay.tm_min, 
    cb.ngayDen.tm_mday, cb.ngayDen.tm_mon, cb.ngayDen.tm_year, cb.ngayDen.tm_hour, cb.ngayDen.tm_min, 
    cb.giaCBtg, cb.giaCBpth, cb.sum);
}

// gán giá trị cho hk
HK read_user(char line[])
{
    HK hk;
    sscanf(line,"%[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %d %d %d %d",
    hk.tk, hk.id, hk.ten, hk.gioiTinh, hk.quocTich, hk.sdt, &hk.tuoi, 
    &hk.ngaySinh.tm_mday, &hk.ngaySinh.tm_mon, &hk.ngaySinh.tm_year);
    trim(hk.tk);
    trim(hk.id);
    trim(hk.ten);
    trim(hk.gioiTinh);
    trim(hk.quocTich);
    trim(hk.sdt);
    return hk;
}

// ghi hk vào file
void write_hk(FILE *file, HK hk)
{
    fprintf(file,"%s | %s | %s | %s | %s | %s | %d %d %d %d\n",
    hk.tk, hk.id, hk.ten, hk.gioiTinh, hk.quocTich, hk.sdt, hk.tuoi,
    hk.ngaySinh.tm_mday, hk.ngaySinh.tm_mon, hk.ngaySinh.tm_year);
}

// xuất ve ra màn hình
void display_ve(VE ve)
{
    printf(" %-15s | %-20s | %-10s | %-20s | %-12s | %-12s | %-12s | %-12s | %-6d | %2d/%2d/%-5d | %2d:%-7d | %2d/%2d/%-5d | %2d:%-7d | %-15d\n",
    ve.mahk, ve.tenhk, ve.macb, ve.hang, ve.tu, ve.den, ve.loaive, ve.hangve, ve.ghe,
    ve.ngaybay.tm_mday, ve.ngaybay.tm_mon, ve.ngaybay.tm_year, ve.ngaybay.tm_hour, ve.ngaybay.tm_min,
    ve.ngayden.tm_mday, ve.ngayden.tm_mon, ve.ngayden.tm_year, ve.ngayden.tm_hour, ve.ngayden.tm_min,
    ve.giave);
}

// xuất hành khách tra ngoài màn hình 
void display_user(HK hk)
{
    printf(" %-20s | %-15s | %-20s | %-13s | %-13s | %-13s | %-10d | %2d/%2d/%-5d\n",
    hk.tk, hk.id, hk.ten, hk.gioiTinh, hk.quocTich, hk.sdt, hk.tuoi, 
    hk.ngaySinh.tm_mday, hk.ngaySinh.tm_mon, hk.ngaySinh.tm_year);
}

// xuất chuyến bay ra ngời màn hình
void display_cb(CB cb)
{
    printf(" %-10s | %-20s | %-12s | %-12s | %2d/%2d/%-5d | %2d:%-7d | %2d/%2d/%-5d | %2d:%-7d | %-10d | %-10d | %-15d\n",
    cb.maCB, cb.hang, cb.tu, cb.den, 
    cb.ngayBay.tm_mday, cb.ngayBay.tm_mon, cb.ngayBay.tm_year, cb.ngayBay.tm_hour, cb.ngayBay.tm_min,
    cb.ngayDen.tm_mday, cb.ngayDen.tm_mon, cb.ngayDen.tm_year, cb.ngayDen.tm_hour, cb.ngayDen.tm_min,
    cb.giaCBtg, cb.giaCBpth, cb.sum);
}

// gán giá trị vào ghe
GHE read_chair(char line[])
{
    GHE ghe;
    sscanf(line,"%[^|]| %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", ghe.macb,
    &ghe.ghe[0], &ghe.ghe[1], &ghe.ghe[2], &ghe.ghe[3], &ghe.ghe[4], &ghe.ghe[5], &ghe.ghe[6], &ghe.ghe[7], &ghe.ghe[8], &ghe.ghe[9], 
    &ghe.ghe[10], &ghe.ghe[11], &ghe.ghe[12], &ghe.ghe[13], &ghe.ghe[14], &ghe.ghe[15], &ghe.ghe[16], &ghe.ghe[17], &ghe.ghe[18], &ghe.ghe[19], 
    &ghe.ghe[20], &ghe.ghe[21], &ghe.ghe[22], &ghe.ghe[23], &ghe.ghe[24], &ghe.ghe[25], &ghe.ghe[26], &ghe.ghe[27], &ghe.ghe[28], &ghe.ghe[29], 
    &ghe.con_lai);
    trim(ghe.macb);
    return ghe;
}

// ghi ghe vao file
void write_chair(FILE * file, GHE ghe)
{
    fprintf(file,"%s | %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
    ghe.macb,
    ghe.ghe[0], ghe.ghe[1], ghe.ghe[2], ghe.ghe[3], ghe.ghe[4], ghe.ghe[5], ghe.ghe[6], ghe.ghe[7], ghe.ghe[8], ghe.ghe[9],
    ghe.ghe[10], ghe.ghe[11], ghe.ghe[12], ghe.ghe[13], ghe.ghe[14], ghe.ghe[15], ghe.ghe[16], ghe.ghe[17], ghe.ghe[18], ghe.ghe[19],
    ghe.ghe[20], ghe.ghe[21], ghe.ghe[22], ghe.ghe[23], ghe.ghe[24], ghe.ghe[25], ghe.ghe[26], ghe.ghe[27], ghe.ghe[28], ghe.ghe[29],
    ghe.con_lai);
}
#endif//READ_WRITE_H