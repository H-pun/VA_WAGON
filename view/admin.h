#include "../provider/service.h"

void add_kandidat()
{
    char nim[15], nama[25], visi[255];
start:
    draw_title("Tambah Kandidat");
    printf("> Masukan NIM : ");
    scanf("%s", nim);
    fflush(stdin);
    if (!nim_kandidat_exist(nim))
    {
        printf("> Masukan Nama : ");
        gets(nama);
        printf("> Masukan Visi : ");
        gets(visi);
        create_kandidat(nim, nama, visi);
    }
    else if (try_again())
        goto start;
}

void add_mahasiswa()
{
    char nim[15], nama[25];
start:
    draw_title("Tambah Mahasiswa");
    printf("> Masukan NIM : ");
    scanf("%s", nim);
    fflush(stdin);
    if (!nim_mahasiswa_exist(nim))
    {
        printf("> Masukan Nama : ");
        gets(nama);
        create_mahasiswa(nim, nama);
    }
    else if (try_again())
        goto start;
}

void menu_admin()
{
    int menu;
start:
    draw_title("Main Menu");
    greet();
    draw_option(1, "Tambah Mahasiswa");
    draw_option(2, "Tambah Kandidat");
    draw_option(3, "Lihat Perolehan");
    draw_option(4, "Log Out");
    draw_line(equal, 40);
    printf("> Silahkan pilih menu : ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
        add_mahasiswa();
        goto start;
        break;
    case 2:
        add_kandidat();
        goto start;
        break;
    case 3:
        show_total_votes();
        goto start;
        break;
    case 4:
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