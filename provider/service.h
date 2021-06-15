#include "driver.h"

// Tampilkan semua data kandidat dari txt
void show_total_votes()
{
    system("cls");
    Kandidat *kdt, tmp;
    kdt = load_kandidat();
    int length = 57, n = count_rows(FILE_DIR_KDT);
    draw_line(equal, length);
    printf("|                                                       |\n");
    printf("|                    Total Perolehan                    |\n");
    printf("|                                                       |\n");
    draw_line(dash, length);
    printf("| %-3s | %-15s | %-20s | %-6s |\n",
           "No", "NIM", "Nama", "Votes");
    draw_line(dash, length);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (kdt[i].votes < kdt[j].votes)
            {
                tmp = kdt[i];
                kdt[i] = kdt[j];
                kdt[j] = tmp;
            }
    for (int i = 0; i < n; i++)
        printf("| %-3d | %-15s | %-20s | %-6d |\n",
               i + 1,
               kdt[i].nim,
               kdt[i].nama,
               kdt[i].votes);
    draw_line(equal, length);
    system("pause");
}

// Tampilkan data kandidat untuk dipilih dari txt
void show_vote_list()
{
    system("cls");
    Kandidat *kdt;
    kdt = load_kandidat();
    int n = count_rows(FILE_DIR_KDT);
    for (int i = 0; i < n; i++)
    {
        char title[20];
        sprintf(title, "No urut - %d", i + 1);
        draw_custom_title(title, 45);
        printf(" NIM: %s\n", kdt[i].nim);
        printf(" Nama: %s\n", kdt[i].nama);
        printf(" Visi: ");
        limit_text_width(kdt[i].visi);
        draw_line(tilde, 45);
        printf("\n");
    }
}

// Cek jika username sudah ada
bool username_exist(char username[])
{
    Admin *adm;
    Mahasiswa *mhs;
    adm = load_admin();
    mhs = load_mahasiswa();
    int n = count_rows(FILE_DIR_MHS);
    for (int i = 0; i < n; i++)
        if (strcmp(mhs[i].username, username) == 0)
        {
            draw_line(dash, 40);
            printf("# Username terdaftar!\n");
            return true;
        }
    n = count_rows(FILE_DIR_ADM);
    for (int i = 0; i < n; i++)
        if (strcmp(adm[i].username, username) == 0)
        {
            draw_line(dash, 40);
            printf("# Username terdaftar!\n");
            return true;
        }
    return false;
}

// Cek jika NIM mahasiswa sudah ada
bool nim_mahasiswa_exist(char nim[])
{
    Mahasiswa *mhs;
    mhs = load_mahasiswa();
    int n = count_rows(FILE_DIR_MHS);
    for (int i = 0; i < n; i++)
        if (strcmp(mhs[i].nim, nim) == 0)
        {
            draw_line(dash, 40);
            printf("# NIM terdaftar!\n");
            return true;
        }
    return false;
}

// Cek jika NIM kandidat sudah ada
bool nim_kandidat_exist(char nim[])
{
    Kandidat *kdt;
    kdt = load_kandidat();
    int n = count_rows(FILE_DIR_KDT);
    for (int i = 0; i < n; i++)
        if (strcmp(kdt[i].nim, nim) == 0)
        {
            draw_line(dash, 40);
            printf("# NIM terdaftar!\n");
            return true;
        }
    return false;
}

// Cek jika NIM mahasiswa teregistrasi
bool mahasiswa_registered(char nim[])
{
    Mahasiswa *mhs;
    mhs = load_mahasiswa();
    int n = count_rows(FILE_DIR_MHS);
    for (int i = 0; i < n; i++)
        if (strcmp(mhs[i].nim, nim) == 0 && !(strcmp(mhs[i].username, "null") == 0))
        {
            draw_line(dash, 40);
            printf("# Akun terdaftar!\n");
            return true;
        }
    return false;
}

// Cek jika Mahasiswa sudah vote
bool mahasiswa_voted()
{
    if (acc.voted)
    {
        Kandidat *kdt;
        kdt = load_kandidat();
        draw_title("Terima kasih!");
        printf("# Kamu sudah vote %s!\n", kdt[acc.voted - 1].nama);
        system("pause");
        return true;
    }
    return false;
}

// Fungsi vote kandidat
bool vote(int kandidat)
{
    int n = count_rows(FILE_DIR_KDT);
    draw_line(dash, 45);
    if (kandidat - 1 < 0 || kandidat > n)
    {
        printf("# Input tidak valid!\n");
        return false;
    }
    Mahasiswa *mhs;
    Kandidat *kdt;
    FILE *file;
    mhs = load_mahasiswa();
    kdt = load_kandidat();
    file = fopen("replace.tmp", "w");
    acc.voted = kandidat;
    for (int i = 0; i < n; i++)
    {
        if (i == kandidat - 1)
            fprintf(file, "%d;%s;%s;%s;\n",
                    ++kdt[i].votes,
                    kdt[i].nim,
                    kdt[i].nama,
                    kdt[i].visi);
        else
            fprintf(file, "%d;%s;%s;%s;\n",
                    kdt[i].votes,
                    kdt[i].nim,
                    kdt[i].nama,
                    kdt[i].visi);
    }
    fclose(file);
    clean_file(FILE_DIR_KDT);
    n = count_rows(FILE_DIR_MHS);
    file = fopen("replace.tmp", "w");
    for (int i = 0; i < n; i++)
    {
        if (strcmp(mhs[i].nim, acc.nim) == 0)
            fprintf(file, "%d;%s;%s;%s;%s;\n",
                    kandidat,
                    mhs[i].nim,
                    mhs[i].nama,
                    mhs[i].username,
                    mhs[i].password);
        else
            fprintf(file, "%d;%s;%s;%s;%s;\n",
                    mhs[i].voted,
                    mhs[i].nim,
                    mhs[i].nama,
                    mhs[i].username,
                    mhs[i].password);
    }
    fclose(file);
    clean_file(FILE_DIR_MHS);
    printf("# Terimakasih telah vote!\n");
    system("pause");
    return true;
}

// Fungsi ambil nama mahasiswa
char *get_mahasiswa_name(char nim[])
{
    Mahasiswa *mhs;
    mhs = load_mahasiswa();
    int n = count_rows(FILE_DIR_MHS);
    for (int i = 0; i < n; i++)
        if (strcmp(mhs[i].nim, nim) == 0)
            return mhs[i].nama;
}

// Fungsi tambah mahasiswa
void create_mahasiswa(char nim[], char nama[])
{
    FILE *file;
    file = fopen(FILE_DIR_MHS, "a");
    fprintf(file, "0;%s;%s;null;null;\n", nim, nama);
    fclose(file);
    draw_line(dash, 40);
    printf("# Mahasiswa berhasil ditambahkan!\n");
    system("pause");
}

// Fungsi tambah kandidat
void create_kandidat(char nim[], char nama[], char visi[])
{
    FILE *file;
    file = fopen(FILE_DIR_KDT, "a");
    fprintf(file, "0;%s;%s;%s;\n", nim, nama, visi);
    fclose(file);
    draw_line(dash, 40);
    printf("# Kandidat berhasil ditambahkan!\n");
    system("pause");
}

// Fungsi register
void create_account(char nim[], char username[], char password[])
{
    Mahasiswa *mhs;
    FILE *file;
    file = fopen("replace.tmp", "w");
    mhs = load_mahasiswa();
    int n = count_rows(FILE_DIR_MHS);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(mhs[i].nim, nim) == 0)
            fprintf(file, "0;%s;%s;%s;%s;\n",
                    mhs[i].nim,
                    mhs[i].nama,
                    username,
                    password);
        else
            fprintf(file, "%d;%s;%s;%s;%s;\n",
                    mhs[i].voted,
                    mhs[i].nim,
                    mhs[i].nama,
                    mhs[i].username,
                    mhs[i].password);
    }
    fclose(file);
    clean_file(FILE_DIR_MHS);
    printf("# Registrasi berhasil!\n");
    system("pause");
}

// Fungsi log-in
int load_account(char username[], char password[])
{

    if (password_valid(username, "null", password, "null"))
        return acc.role = guest;
    Admin *adm;
    Mahasiswa *mhs;
    adm = load_admin();
    mhs = load_mahasiswa();
    int n = count_rows(FILE_DIR_MHS);
    for (int i = 0; i < n; i++)
        if (password_valid(mhs[i].password, password,
                           mhs[i].username, username))
        {
            strcpy(acc.nim, mhs[i].nim);
            strcpy(acc.nama, mhs[i].nama);
            strcpy(acc.username, mhs[i].username);
            acc.voted = mhs[i].voted;
            return acc.role = mahasiswa;
        }
    n = count_rows(FILE_DIR_ADM);
    for (int i = 0; i < n; i++)
        if (password_valid(adm[i].password, password,
                           adm[i].username, username))
        {
            strcpy(acc.username, adm[i].username);
            return acc.role = admin;
        }
    return acc.role = guest;
}