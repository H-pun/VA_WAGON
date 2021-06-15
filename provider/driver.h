#include "utility.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define FILE_DIR_ADM "storage/admin.txt"
#define FILE_DIR_KDT "storage/kandidat.txt"
#define FILE_DIR_MHS "storage/mahasiswa.txt"

typedef struct //Admin
{
    char
        username[15],
        password[15];
} Admin;

typedef struct // Kandidat
{
    int votes;
    char
        nim[15],
        nama[25],
        visi[255];
} Kandidat;

typedef struct // Mahasiswa
{
    int voted;
    char
        nim[15],
        nama[25],
        username[15],
        password[15];
} Mahasiswa;

// Load data admin dari txt
Admin *load_admin()
{
    FILE *file;
    file = fopen(FILE_DIR_ADM, "r");
    int i = 0, n = count_rows(FILE_DIR_ADM);
    Admin *adm = malloc(sizeof(Admin) * n);
    while (fscanf(file, "%[^;];%[^;];\n",
                  adm[i].username,
                  adm[i].password) == 2)
        i++;
    fclose(file);
    return adm;
}

// Load data admin dari txt
Kandidat *load_kandidat()
{
    FILE *file;
    file = fopen(FILE_DIR_KDT, "r");
    int i = 0, n = count_rows(FILE_DIR_KDT);
    Kandidat *kdt = malloc(sizeof(Kandidat) * n);
    while (fscanf(file, "%d;%[^;];%[^;];%[^;];\n",
                  &kdt[i].votes,
                  kdt[i].nim,
                  kdt[i].nama,
                  kdt[i].visi) == 4)
        i++;
    fclose(file);
    return kdt;
}

// Load data mahasiswa dari txt
Mahasiswa *load_mahasiswa()
{
    FILE *file;
    file = fopen(FILE_DIR_MHS, "r");
    int i = 0, n = count_rows(FILE_DIR_MHS);
    Mahasiswa *mhs = malloc(sizeof(Mahasiswa) * n);
    while (fscanf(file, "%d;%[^;];%[^;];%[^;];%[^;];\n",
                  &mhs[i].voted,
                  mhs[i].nim,
                  mhs[i].nama,
                  mhs[i].username,
                  mhs[i].password) == 5)
        i++;
    fclose(file);
    return mhs;
}

// Tampilkan semua data admin dari txt
void show_admin()
{
    Admin *adm;
    adm = load_admin();
    int length = 43, n = count_rows(FILE_DIR_ADM);
    draw_line(equal, length);
    printf("| %-3s | %-15s | %-15s |\n",
           "No", "Username", "Password");
    draw_line(equal, length);
    for (int i = 0; i < n; i++)
        printf("| %-3d | %-15s | %-15s |\n",
               i + 1,
               adm[i].username,
               adm[i].password);
    draw_line(equal, length);
}

// Tampilkan semua data kandidat dari txt
void show_kandidat()
{
    Kandidat *kdt;
    kdt = load_kandidat();
    int length = 91, n = count_rows(FILE_DIR_KDT);
    draw_line(equal, length);
    printf("| %-3s | %-15s | %-20s | %-31s | %-6s |\n",
           "No", "NIM", "Nama", "Visi", "Votes");
    draw_line(equal, length);
    for (int i = 0; i < n; i++)
        printf("| %-3d | %-15s | %-20s | %-28.28s... | %-6d |\n",
               i + 1,
               kdt[i].nim,
               kdt[i].nama,
               kdt[i].visi,
               kdt[i].votes);
    draw_line(equal, length);
}

// Tampilkan semua data mahasiswa dari txt
void show_mahasiswa()
{
    Mahasiswa *mhs;
    mhs = load_mahasiswa();
    int length = 99, n = count_rows(FILE_DIR_MHS);
    draw_line(equal, length);
    printf("| %-3s | %-15s | %-25s | %-15s | %-15s | %-7s |\n",
           "No", "NIM", "Nama", "Username", "Password", "Voted");
    draw_line(equal, length);
    for (int i = 0; i < n; i++)
        printf("| %-3d | %-15s | %-25s | %-15s | %-15s | %-7s |\n",
               i + 1,
               mhs[i].nim,
               mhs[i].nama,
               mhs[i].username,
               mhs[i].password,
               mhs[i].voted ? "Yes" : "No");
    draw_line(equal, length);
}

// Tampilkan semua data mahasiswa txt
void show_all_databases()
{
    system("cls");
    show_admin();
    show_kandidat();
    show_mahasiswa();
    system("pause");
}

// Membuat txt dummy
void seed()
{
    char root_folder[] = "storage/";
    struct stat st = {0};
    if (stat(root_folder, &st) == -1)
        mkdir(root_folder);
    Admin adm[] = {
        {username : "admin", password : "admin"},
        {username : "ordal", password : "ssst"}};
    Kandidat kdt[] = {
        {nim : "1103201263", nama : "Aqwam Farid", visi : "Membentuk BEM yang aktif sebagai pionir dalam pergerakan untuk mewujudkan mahasiswa yang berkompeten dan memiliki integritas terhadap problematika yang terjadi di tengah masyarakat."},
        {nim : "1103204177", nama : "Arya Pramuditha", visi : "Menciptakan BEM yang berperan aktif dalam pengembangan minat dan bakat bagi seluruh mahasiswa."},
        {nim : "1103204058", nama : "Atallah Satrio", visi : "Mewujudkan BEM yang independen, unggul, berkualitas, aspiratif, dan progresif, guna menunaikan tugas yang telah dipercayakan mahasiswa dan universitas kepada BEM."}};
    Mahasiswa mhs[] = {
        {nim : "1103204038", nama : "Harvan Nurluthfi"},
        {nim : "1103201250", nama : "Ratika Dwi"},
        {nim : "1103204115", nama : "Rizka Rahmadina"},
        {nim : "1103204060", nama : "Nabilah Salwa"},
        {nim : "1103200032", nama : "Fajra Risulla"},
        {nim : "1103202052", nama : "Agiel Fakhrozi"},
        {nim : "1103200082", nama : "Yuzzaf Ibrahim"}};
    FILE *file;
    file = fopen(FILE_DIR_MHS, "w");
    for (int i = 0; i < sizeof(mhs) / sizeof(mhs[0]); i++)
        fprintf(file, "0;%s;%s;null;null;\n", mhs[i].nim, mhs[i].nama);
    fclose(file);
    file = fopen(FILE_DIR_ADM, "w");
    for (int i = 0; i < sizeof(adm) / sizeof(adm[0]); i++)
        fprintf(file, "%s;%s;\n", adm[i].username, adm[i].password);
    fclose(file);
    file = fopen(FILE_DIR_KDT, "w");
    for (int i = 0; i < sizeof(kdt) / sizeof(kdt[0]); i++)
        fprintf(file, "0;%s;%s;%s;\n", kdt[i].nim, kdt[i].nama, kdt[i].visi);
    fclose(file);
    draw_line(dash, 40);
    printf("# Data dummy berhasil dibuat!\n");
    system("pause");
}