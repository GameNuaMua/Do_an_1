#ifndef CHAIR_H
#define CHAIR_H

#include "Ql_struct.h"
#include "Clear_spaces.h"
#include "Filtering.h"

// tạo ghế 
void Chair_create(char macb[])
{
    //--------------------------------------mở file------------------------------------------
    FILE *fghe = fopen("data/chuyen_bay/Chair.txt","a");
    //---------------------kiểm tra mở file------------------
    if (fghe == NULL)
    {
        printf("error: Chair.txt");
        exit(1);
    }
    //-----------------------------tạo ghế-------------------
    fprintf(fghe,"%s | ",macb);
    for (int i = 1; i < 31; i++)
    {
        fprintf(fghe,"%d ",i);
    }
    fprintf(fghe,"30\n");
    //-------------------------------------đóng file------------------------------------------
    fclose(fghe);
}

// chọn ghế
int Choose_seat(int hangve, char macb[])
{
    Filtering_chair();
    // khởi tạo biến
    int chon_ghe, dem = 0, soghecl, size = 0;
    GHE ghe, ghe_temp;
    char Ma[10];
    //----------------------------------------mở file---------------------------------------
    FILE *fghe = fopen("data/chuyen_bay/Chair.txt","r");
    //-------------------------------kiểm tra mở file--------------------
    if (fghe == NULL)
    {
        printf("error: chair.txt\n");
        exit(1);
    }
    //------------------------------đếm số chuyến bay------------------------
    char linesize[200];
    while (fgets(linesize, 200, fghe) != NULL)
    {
        size++;
    }
    GHE G[size-1];
    //------------------------------xuất ghê-------------------------------
    rewind(fghe);
    int Ghe[30];
    char lineghe[200];
    while (fgets(lineghe, 200, fghe) != NULL)
    {
        ghe = read_chair(lineghe);
        if (strcmp(macb, ghe.macb) == 0)
        {
            for (int i = 0; i < 30; i++)
            {
                Ghe[i] = ghe.ghe[i];
            }
            soghecl = ghe.con_lai - 1;
            strcpy(Ma, ghe.macb);
            if (hangve == 1)// thuong gia
            {   
                for (int i = 0; i < 10; i++)
                {
                    printf("| %2d |", ghe.ghe[i]);
                }
                printf("\n");
            }
            if (hangve == 2)// pho thong
            {
                for (int i = 10; i < 30; i++)
                {
                    printf(" | %2d |", ghe.ghe[i]);
                    if (i == 19 || i == 29) printf("\n");
                }
            }
        }
        else
        {
            G[dem] = ghe;
            dem++;
        }
    }
    //------------------------chọn ghế----------------------
    printf("Chon ghe (ngoai tru 0): ");
    scanf("%d", &chon_ghe);
    getchar();
    //---------------------------------------đóng file--------------------------------------
    fclose(fghe);
    //--------------------------------------thay đổi ghế đã chọn thành 0--------------------
    //--------------------------------------mở file-----------------------------------------
    fghe = fopen("data/chuyen_bay/Chair.txt","w");
    //----------------kiểm tra file mở------------------------
    if (fghe == NULL)
    {
        printf("error: chair.txt\n");
        exit(1);
    }
    //---------------------------thay đổi---------------------
    for (int i = 0; i < 30; i++)
    {
        if (Ghe[i] == chon_ghe)
        {
            Ghe[i] = 0;
            break;
        }
    }
    //----------------------------sao luu---------------------
    fprintf(fghe,"%s | ",Ma);//----------chuyến máy bay đã chọn
    for (int i = 0; i < 30; i++)
    {
        fprintf(fghe,"%d ",Ghe[i]);
    }
    fprintf(fghe,"%d\n",soghecl);
    //---------------------------------------chuyến máy bay không chọn
    for (int i = 0; i < size-1; i++)
    {
        fprintf(fghe,"%s | ",G[i].macb);
        for (int j = 0; j < 30; j++)
        {
            fprintf(fghe,"%d ",G[i].ghe[j]);
        }
        fprintf(fghe,"%d\n",G[i].con_lai);
    }
    //-------------------------------------đóng file-----------------------------------------
    fclose(fghe);
    return chon_ghe;
}

#endif//CHAIR_CREATE_H