#ifndef LOGIN_CREATE_H
#define LOGIN_CREATE_H

// file.h
#include "Ql_struct.h"
#include "Clear_spaces.h"
#include "Input.h"

int so_lan_login()
{
    // khởi tạo biến
    int so_lan;
    DN dn;
    //---------------------------mở file---------------------------------
    FILE * fus = fopen("data/user/tk_user.txt","r");
    FILE * fus_temp = fopen("data/user/TEMP_tk_user.txt","w");
    //----------------kiểm tra mở file------------
    if (fus == NULL)
    {
        printf("error: tk_user.txt\n");
        exit(1);
    }
    //---------
    if (fus == NULL)
    {
        printf("error: TEMP_tk_user.txt\n");
        exit(1);
    }
    //----------------thay đổi số lần đăng nhập-----------
    char lineus[100];
    while (fgets(lineus, sizeof(lineus), fus) != NULL)
    {
        sscanf(lineus, "%[^|]| %[^|]| %d", dn.tk, dn.mk, &dn.dem);
        trim(dn.tk);// xoá ký tự trắng ở 2 đầu nếu có
        trim(dn.mk);// xoá ký tự trắng ở 2 đầu nếu có
        //--------------------so sanh----------------
        if (strcmp(tk_login, dn.tk) != 0)
        {
            fprintf(fus_temp,"%s | %s | %d\n", dn.tk, dn.mk, dn.dem);
        }
        if (strcmp(tk_login, dn.tk) == 0)
        {
            dn.dem++;
            so_lan = dn.dem;
            fprintf(fus_temp,"%s | %s | %d\n", dn.tk, dn.mk, so_lan);
        }
    }
    //--------------------------đóng file--------------------------------
    fclose(fus_temp);
    fclose(fus);
    //---------------------------kết thúc--------------------------------
    remove("data/user/tk_user.txt");
    rename("data/user/TEMP_tk_user.txt","data/user/tk_user.txt");
    return so_lan;
}

int New_account(int solan)
{
    if (solan == 1)
    {
        system("cls");// xoá màn hình cosole
        printf("Chao mung ban den voi AIRLINE cua chung toi\n");
        printf("Hay nhan phim bat ky de bat dau nao:\n");
        getch();
        system("cls");// xoá màn hình cosole
        //--------------nhap thong tin hk----------------------
        FILE * file = fopen("data/hanh_khach/profile_user.txt","a+");
        if (file == NULL)
        {
            exit(1);
        }
        input_profile_user(file, tk_login);
        fclose(file);
    }// end if
    //----------------------kết thúc-----------------------
    return 0;
}

int Login()
{
    // khởi tạo biến
    DN dn;
    char tk[50];
    char mk[50];
    //------------------DANG NHAP-------------------------------
    printf("====================DANG NHAP====================\n");
    printf("\tTK: ");
    fgets(tk,50,stdin);
    tk[strlen(tk) - 1 ] = '\0';
    printf("\tMK: ");
    fgets(mk,50,stdin);
    mk[strlen(mk) - 1 ] = '\0';
    trim(tk);// xoá ký tự trắng ở 2 đầu nếu có
    trim(mk);// xoá ký tự trắng ở 2 đầu nếu có
    printf("=================================================\n");
    //---------------mở---------------------------
    FILE * fadm = fopen("data/admin/tk_admin.txt","r");
    FILE * fus = fopen("data/user/tk_user.txt","r");
    //---------------kiểm tra mở file--------------------------
    if (fadm == NULL)
    {
        printf("error: tk_admin.txt\n");
        exit(1);
    }
    //--------
    if (fus == NULL)
    {
        printf("error: tk_user.txt\n");
        exit(1);
    }
    //------------------kiểm tra---------------------
    //-------------------------------admin-----------
    char lineadm[100];
    while (fgets(lineadm, 100, fadm) != NULL)
    {
        sscanf(lineadm, "%[^|]| %[^|]| %d", dn.tk, dn.mk, &dn.dem);
        trim(dn.tk);// xoá ký tự trắng ở 2 đầu nếu có
        trim(dn.mk);// xoá ký tự trắng ở 2 đầu nếu có
        //--------------------so sánh-----
        if (strcmp(dn.tk, tk) == 0 && strcmp(dn.mk, mk) == 0)
        {
            check_tk = 1;
            system("cls");
            fclose(fadm);
            fclose(fus);
            return check_tk;
        }
    }
    //-------------------------------user------------
    char lineus[100];
    while (fgets(lineus, 100, fus) != NULL)
    {
        sscanf(lineus, "%[^|]| %[^|]| %d", dn.tk, dn.mk, &dn.dem);
        trim(dn.tk);// xoá ký tự trắng ở 2 đầu nếu có
        trim(dn.mk);// xoá ký tự trắng ở 2 đầu nếu có
        //--------------------so sánh-----
        if (strcmp(dn.tk, tk) == 0 && strcmp(dn.mk, mk) == 0)
        {
            check_tk = 2;
            strcpy(tk_login, tk);
            system("cls");
            fclose(fadm);
            fclose(fus);
            return check_tk;
        }
    }
    //----------------đóng------------------------
    fclose(fadm);
    fclose(fus);
    //---------------kết thúc---------------------
    check_tk = 0;
    return check_tk;
}

int Create()
{
    DN dn;
    while (1)
    {
        // khởi tạo biến
        char tk[50];
        char mk[50];
        int check = 0;// kiểm tra tài khoản tồn tại không
        //-----------------DANG KY----------------
        printf("====================DANG KY====================\n");
        printf("\tTK: ");
        fgets(tk,50,stdin);
        tk[strlen(tk) - 1] = '\0';
        //-----------------------------kiểm tra tài khoản có tồn tại không------------------------------------
        //------------------mở file-------------------
        FILE * fadm = fopen("data/admin/tk_admin.txt","r");
        FILE * fus = fopen("data/user/tk_user.txt","a+");
        //--------kiểm tra mở file---------
        if (fadm == NULL)
        {
            printf("error: tk_admin.txt\n");
            exit(1);
        }
        //---------
        if (fus == NULL)
        {
            printf("error: tk_user.txt\n");
            exit(1);
        }
        //--------------------kiểm tra tồn tại---------------
        //---------------------------------------------------------admin
        char lineadm[100];
        while (fgets(lineadm,sizeof(lineadm),fadm) != NULL)
        {
            sscanf(lineadm, "%[^|]| %[^|]| %d", dn.tk, dn.mk, &dn.dem);
            trim(dn.tk);// xoá ký tự trắng ở 2 đầu nếu có
            trim(dn.mk);// xoá ký tự trắng ở 2 đầu nếu có
            //--------------------so sánh-----
            if (strcmp(dn.tk, tk) == 0)
            {
                system("cls");
                printf("Tai Khoan da ton tai-!!!\n");
                check = 1;
                break;
            }
        }
        //----------------------------------------------------------user
        char lineus[100];
        while (fgets(lineus,sizeof(lineus),fus) != NULL)
        {
            sscanf(lineus, "%[^|]| %[^|]| %d", dn.tk, dn.mk, &dn.dem);
            trim(dn.tk);// xoá ký tự trắng ở 2 đầu nếu có
            trim(dn.mk);// xoá ký tự trắng ở 2 đầu nếu có
            //--------------------so sánh-----
            if (strcmp(dn.tk, tk) == 0)
            {
                system("cls");
                printf("Tai Khoan da ton tai-!!!\n");
                check = 1;
                break;
            }
        }
        //---------------------nhập mật khẩu---------------------
        if (check == 1)
        {
            continue;
        }
        printf("\tMK: ");
        fgets(mk,50,stdin);
        mk[strlen(mk) - 1] = '\0';
        //-------------------------------sao luu tk mk----------------------------
        fprintf(fus,"%s | %s | 0\n", tk, mk);
        //-----------------đóng file------------------
        if (fclose(fadm) != 0)
            printf("Dong file tk_admin khong thanh cong\n");
        if (fclose(fus) != 0)
            printf("Dong file tk_user khong thanh cong\n");
        printf("===============================================\n");
        break;
    }
    return 0;
}
#endif// LOGIN_CREATE_H