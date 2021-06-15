#include "admin.h"

void vote_mahasiswa()
{
start:
    if (!mahasiswa_voted())
    {
        int no;
        show_vote_list();
        draw_line(dash, 45);
        printf("> Masukan no urut: ");
        scanf("%d", &no);
        if (!vote(no))
            if (try_again())
                goto start;
    }
}

void menu_mahasiswa()
{
    int menu;
start:
    draw_title("Main Menu");
    greet();
    draw_option(1, "Lihat Visi");
    draw_option(2, "Vote");
    draw_option(3, "Log Out");
    draw_line(dash, 40);
    printf("> Silahkan pilih menu: ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
        show_vote_list();
        system("pause");
        goto start;
        break;
    case 2:
        vote_mahasiswa();
        goto start;
        break;
    case 3:
        return;
        break;
    default:
        draw_line(dash, 40);
        printf("# Input tidak valid\n");
        if (try_again())
            goto start;
        break;
    }
}