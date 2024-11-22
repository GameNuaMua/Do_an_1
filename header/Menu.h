#ifndef MENU_H
#define MENU_H

#include "Input.h"
#include "Output.h"
#include "pay_ticket.h"
#include "Remove.h"
#include "Login_Create.h"
#include "sua.h"
#include "Search.h"

void menu_admin()
{
    system("cls");// xóa màn hình console
    printf("Menu Admin\n");
    int choice;
    do
    {
        printf("========================ADMIN======================\n");
        printf("\t\t1.Them chuyen bay\n");
        printf("\t\t2.Them ve\n");
        printf("\t\t3.Xuat\n");
        printf("\t\t4.Sua thong tin Chuyen/TT Hanh Khach\n");
        printf("\t\t5.Huy Chuyen/Ve\n");
        printf("\t\t6.Dang Xuat\n");
        printf("\t\t7.Thoat\n");
        printf("==================================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        system("cls");// xóa màn hình console
        //------------------------------------------------------------------------------------------
        // switch case
        switch (choice)
        {
        case 1:
            add_flight();
            break;
        case 2:
            pay_ticket();
            break;
        case 3:
            menu_output();
            break;
        case 4:
            menu_sua();
            break;
        case 5:
            menu_remove();
            break;
        case 6:
            printf("---Dang Xuat thanh cong---\n");
            getch();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Lua chon khong hop le\n");
            break;
        }
    }while(choice != 6);
    //----------------------------------------------------------------------------------------------
    getch();
}

void menu_user()
{
    system("cls");// xóa màn hình console
    printf("Menu User\n");

    int choice;
    do
    {//=======================================MENU USER=======================================
        printf("========================USER======================\n");
        printf("\t\t1.Danh sach ve da dat\n");
        printf("\t\t2.Mua ve\n");
        printf("\t\t3.Huy ve\n");
        printf("\t\t4.Sua thong tin\n");
        printf("\t\t5.Dang Xuat\n");
        printf("\t\t6.Thoat\n");
        printf("==================================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        system("cls");// xóa màn hình console
        //------------------------------------------------------------------------------------------
        // switch case
        switch (choice)
        {
        case 1:
            {
                HK hk;
                int dem;
                hk = Seatch_profile_user_account();
                Search_ticket_id(hk.id);
                FILE *fvet = fopen("data/ve/TEMP_ve.txt", "r");
                
                // kiem tra
                if (fvet == NULL)
                {
                    printf("error: TEMP_ve.txt");
                    exit(1);
                }
                dem = Output_ticket(fvet);
                if (dem == 0)
                {
                    printf("\n\tKHONG CO VE NAO!!!\n");
                    printf("Bam phim bat ki de thoat...\n");
                    getch();
                    system("cls");
                  
                }
                fclose(fvet);
                remove("data/ve/TEMP_ve.txt");
                printf("Bam phim bat ki de thoat...!!!\n");
                getch();
                system("cls");
                break;
            }
        case 2:
        {
            getchar();
            pay_ticket();
            break;
        }
        case 3:
        {
            remove_ticket();
            break;
        }
        case 4:
        {
            system("cls");
            // khai báo biến
            HK hk;

            // xuất danh sách user profile

            hk = Seatch_profile_user_account();
            
            FILE *f = fopen("data/hanh_khach/profile_user.txt", "r");
            FILE *f1 = fopen("data/hanh_khach/t_profile_user.txt", "w");
            sua_hk(f, f1, hk.id);
            fclose(f);
            fclose(f1);
            remove("data/hanh_khach/profile_user.txt");
            rename("data/hanh_khach/t_profile_user.txt","data/hanh_khach/profile_user.txt");
            system("cls");
            printf("Thay doi thanh cong ^-^\nBam phim bat ki de thoat...\n");
            getch();
            system("cls");
            break;
        }
        case 5:
            printf("---Dang Xuat thanh cong---\n");
            getch();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Lua chon khong hop le\n");
            break;
        }
        //------------------------------------------------------------------------------------------
    }while(choice != 5);
    getch();
}

void menu()
{
    int choice; // biến lựa chọn
    do 
    {
        // menu đăng nhập
        system("cls");// xóa màn hình console
        printf("=================AIRLINE=================\n");
        printf("\t\t1.Dang Nhap\n");
        printf("\t\t2.Dang Ky\n");
        printf("\t\t0.Thoat\n");
        printf("=========================================\n");
        // nhập lựa chọn
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();
        // xóa màn hình console
        system("cls");
        //------------------------------------------------------------------------------------------
        // switch case
        switch (choice)
        {
            case 1:
                int check;
                check = Login();
                switch (check)
                {
                    case 1:
                    {
                        menu_admin();
                        break;
                    }
                    case 2:
                    {
                        int solan;
                        solan = so_lan_login();
                        New_account(solan);
                        menu_user();
                        break;
                    }
                    case 0:
                    {
                        system("cls");
                        printf("Tai Khoan Khong Ton Tai-!!!!!!!!!!!!\n");
                        getch();
                        break;
                    }
                    default:
                        break;
                }
                getch();
                break;
            case 2:
                Create();
                break;
            case 0:
                exit(0);
            default:
                printf("Lua chon khong hop le\n");
                break;
        }
        //------------------------------------------------------------------------------------------
    }while(choice != 0); 
}

#endif // end MENU_H