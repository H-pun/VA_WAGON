#include "mahasiswa.h"

void log_in()
{
    char password[15], username[15];
start:
    draw_title("Login");
    printf("> Masukan Username: ");
    scanf("%s", username);
    printf("> Masukan password: ");
    mask_password(password);

    switch (load_account(username, password))
    {
    case admin:
        menu_admin();
        break;
    case mahasiswa:
        menu_mahasiswa();
        break;
    default:
        draw_line(dash, 40);
        printf("# Username atau password salah!\n");
        if (try_again())
            goto start;
        break;
    }
}

void sign_in()
{
    char nim[15], password[15], username[15];
start:
    draw_title("Registrasi");
    printf("> Masukan NIM : ");
    scanf("%s", nim);
    fflush(stdin);
    if (!mahasiswa_registered(nim))
    {
        if (nim_mahasiswa_exist(nim))
        {
            printf("# Hi %s!\n", get_mahasiswa_name(nim));
            draw_line(dash, 40);
            printf("> Masukan Username : ");
            scanf("%s", username);
            fflush(stdin);
            if (!username_exist(username))
            {
                printf("> Masukan Password : ");
                mask_password(password);
                create_account(nim, username, password);
            }
            else if (try_again())
                goto start;
        }
        else
        {
            draw_line(dash, 40);
            printf("# NIM tidak ditemukan!\n");
            if (try_again())
                goto start;
        }
    }
    else if (try_again())
        goto start;
}

void welcome()
{
    int menu;
start:
    draw_title("Selamat datang di VA WAGON");
    draw_option(1, "Login");
    draw_option(2, "Register");
    draw_option(3, "Keluar");
    draw_line(dash, 40);
    printf("> Silahkan pilih menu: ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
        log_in();
        break;
    case 2:
        sign_in();
        break;
    case 3:
        exit(0);
        break;
    case 777:
        set_color();
        break;
    case 888:
        show_all_databases();
        break;
    case 999:
        seed();
        break;
    default:
        draw_line(dash, 40);
        printf("# Input tidak valid\n");
        if (try_again())
            goto start;
        else
            exit(0);
        break;
    }
}