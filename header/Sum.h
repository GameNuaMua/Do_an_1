#ifndef SUM_H
#define SUM_H

// file.h
#include "Ql_struct.h"
#include "Read_Write.h"

// tính tổng số tiền của một chuyến bay
int Sum(char macb[])
{
    // khởi tạo biến
    VE ve;
    int sum = 0;
    //--------------------------mở file----------------------------
    FILE * fve = fopen("data/ve/ve.txt","r");
    //-----------kiểm tra mở file---------------
    if (fve == NULL)
    {
        printf("error: ve.txt");
        exit(1);
    }
    //--------------tính sum--------------------
    char lineve[200];
    while (fgets(lineve,200,fve) != NULL)
    {
        ve = read_ve(lineve);
        if (strcmp(macb, ve.macb) == 0)
            sum += ve.giave;
    }
    //--------------------------đóng file--------------------------
    fclose(fve);
    return sum;
}

int giave(int tuoi, int hangve, CB cb)
{
    int giave;
    if (tuoi > 12 && hangve == 1)
    {
        giave = cb.giaCBtg;
    }
    if (tuoi > 12 && hangve == 2)
    {
        giave = cb.giaCBpth;
    }
    if (tuoi < 12 && hangve == 1)
    {
        giave = cb.giaCBtg / 10;
    }
    if (tuoi < 12 && hangve == 2)
    {
        giave = cb.giaCBpth / 10;
    }
    return giave;
}
#endif//SUM_H