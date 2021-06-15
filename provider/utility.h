#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024

typedef enum
{
    equal,
    dash,
    tilde
} line_types;

struct Account
{
    enum roles
    {
        admin,
        mahasiswa,
        guest
    } role;
    char
        nim[15],
        nama[25],
        username[15];
    int voted;
} acc;

void draw_line(line_types type, int n)
{
    char c = type == equal  ? '='
             : type == dash ? '-'
                            : '~';
    putch('+');
    for (int i = 0; i < n - 2; i++)
        putch(c);
    printf("+\n");
}

void draw_title(char title[])
{
    system("cls");
    int n = 38 - strlen(title),
        left = n / 2,
        right = n % 2 == 0 ? n / 2 : n / 2 + 1;
    draw_line(equal, 40);
    printf("|");
    for (int i = 0; i < left; i++)
        printf(" ");
    printf("%s", title);
    for (int i = 0; i < right; i++)
        printf(" ");
    printf("|\n");
    draw_line(equal, 40);
}

void draw_option(int no, char name[])
{
    int n = 31 - strlen(name);
    printf("| [%d] - %s", no, name);
    for (int i = 0; i < n; i++)
        printf(" ");
    printf("|\n");
}

void draw_custom_title(char title[], int width)
{
    int n = width - strlen(title) - 2,
        left = n / 2,
        right = n % 2 == 0 ? n / 2 : n / 2 + 1;
    draw_line(equal, width);
    printf("|");
    for (int i = 0; i < left; i++)
        printf(" ");
    printf("%s", title);
    for (int i = 0; i < right; i++)
        printf(" ");
    printf("|\n");
    draw_line(equal, width);
}

void limit_text_width(char text[])
{
    int n = strlen(text), limit = 0;
    for (int i = 0; i < n; i++)
    {
        char c = text[i];
        if (limit++ > 30 && c == ' ')
        {
            printf("\n");
            limit = 0;
        }
        putchar(c);
    }
    printf("\n");
}

void greet()
{
    char text[35] = "Wellcome back ",
         spacer[] = "                                      ";
    strcat(text, acc.username);
    strcat(text, "!");
    int n = 38 - strlen(text),
        left = n / 2,
        right = n % 2 == 0 ? n / 2 : n / 2 + 1;
    printf("|%s|\n|", spacer);
    for (int i = 0; i < left; i++)
        printf(" ");
    printf("%s", text);
    for (int i = 0; i < right; i++)
        printf(" ");
    printf("|\n|%s|\n", spacer);
    draw_line(dash, 40);
}

void clean_file(char filename[])
{
    remove(filename);
    rename("replace.tmp", filename);
}

void file_exist(FILE *file)
{
    if (file == NULL)
    {
        fprintf(stderr, "Error open file!\n");
        system("pause");
        exit(1);
    }
}

void mask_password(char pass[])
{
    int i = 0;
    do
    {
        pass[i] = getch();
        if (pass[i] != '\r' && pass[i] != '\b')
        {
            printf("*");
            i++;
        }
        else if (pass[i] == 8 && i != 0)
        {
            printf("\b \b");
            i--;
        }
    } while (pass[i] != '\r');
    pass[i] = '\0';
    putch('\n');
}

void set_color()
{
    char cmd[10] = "color ", color[5];
    printf("> Insert color code : ");
    fflush(stdin);
    scanf("%s", color);
    strcat(cmd, color);
    system(cmd);
}

bool try_again()
{
    char c[5];
    printf("# Coba lagi [yes]? ");
    fflush(stdin);
    scanf("%s", c);
    c[0] = tolower(c[0]);
    return c[0] == 'y' ? true : false;
}

bool password_valid(char p_dest[], char p_source[], char u_dest[], char u_source[])
{
    return (strcmp(p_dest, p_source) == 0) &&
           (strcmp(u_dest, u_source) == 0);
}

int count_rows(char filename[])
{
    FILE *file;
    file = fopen(filename, "r");
    file_exist(file);
    int lines = 0;
    char buff[BUFFER_SIZE];
    while (fgets(buff, sizeof(buff), file) != NULL)
        lines++;
    fclose(file);
    return lines;
}