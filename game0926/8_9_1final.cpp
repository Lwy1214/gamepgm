#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define DICE_SIZE 8
#define cake_number 30  

#define BLACK         0
#define DARK_BLUE     1
#define DARK_GREEN    2
#define DARK_CYAN     3
#define DARK_RED      4
#define DARK_MAGENTA  5
#define DARK_YELLOW   6
#define LIGHT_GRAY    7
#define DARK_GRAY     8
#define BLUE          9
#define GREEN         10
#define CYAN          11
#define RED           12
#define MAGENTA       13
#define YELLOW        14
#define WHITE         15

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

void intro_game(void);
void input_participant(char user_name[][8], char cake_name[]);
void game_control(char name[][8], int condition[], int *left, int user, int *start, int *end, char cake_name[]);
void cake_display(char name[][8], int condition[], int left, int start, int end, char cake_name[]);
void gotoxy(int x, int y);
void set_color(int text_color, int bg_color);
void play_victory_music(void);

int main(void)
{
    int i, start, end, cake_left = cake_number, winner, loser;
    int cake_condition[cake_number] = {0};
    char user_name[2][8];
    char cake_name[20];
    
    srand(time(NULL));

    set_color(YELLOW, BLACK);  
    intro_game();
    input_participant(user_name, cake_name);

    start = 0;
    end = cake_number - 1;

    system("cls");
    game_control(user_name, cake_condition, &cake_left, 2, &start, &end, cake_name);

    set_color(YELLOW, BLACK);
    gotoxy(10, 12);
    printf("�ƹ�Ű�� ������ ���� ������ �����մϴ�.");
    getch();

    do
    {
        for (i = 0; i < 2; i++)
        {
            system("cls");
            game_control(user_name, cake_condition, &cake_left, i, &start, &end, cake_name);

            if (cake_left <= 0)  // ���ڰ� 0�� ������ �� ���� ����
            {
                winner = i;
                loser = 1 - i;
                break;
            }

            set_color(YELLOW, BLACK);
            gotoxy(10, 12);
            printf("�ƹ�Ű�� ������ ���� ������ �����մϴ�.");
            getch();
        }
    } while (cake_left > 1);

    set_color(RED, BLACK); 
    gotoxy(10, 12);
    play_victory_music();
    printf("%s���� �̰���ϴ�.", user_name[winner]);
    printf("%s���� �����ϴ�.", user_name[loser]);

    set_color(WHITE, BLACK); 
    gotoxy(10, 13);
    printf("������ �����մϴ�.\n");

    return 0;
}

void intro_game(void)
{
    system("cls");
    printf("�ֻ����� ���ڸԱ� ���� \n\n");
    printf("�λ���� ���� �糡�� �ֻ��� ���ڸ�ŭ\n");
    printf("���ڸ� �Դ� �����Դϴ�. \n");
    printf("������ ���� ���ڸ� �Դ� ����� �̱�ϴ�. \n\n");
    printf("�ƹ�Ű�� ������ ���������ڸ�\n");
    printf("�Է��մϴ�.\n");
    getch();
}

void input_participant(char user_name[][8], char cake_name[])
{
    system("cls");
    printf("1�� �������� �̸��� �Է��ϰ� Enter>");
    scanf("%s", user_name[0]);
    printf("2�� �������� �̸��� �Է��ϰ� Enter>");
    scanf("%s", user_name[1]);
    printf("������ �̸��� �Է��ϰ� Enter>");
    scanf("%s", cake_name);
    printf("�ƹ�Ű�� ������ ������ �����մϴ�...");
    getch();
}

void game_control(char name[][8], int condition[], int *left, int user, int *s, int *e, char cake_name[])
{
    int i, dice_number;
    cake_display(name, condition, *left, *s, *e, cake_name);

    if (user == 2)
        return;

    dice_number = rand() % DICE_SIZE + 1;
    if (dice_number > *left)
        dice_number = *left;
    *left -= dice_number;
    
    gotoxy(10, 11);
    printf("%s���� �ֻ��� ���ڴ� %d�Դϴ�.", name[user], dice_number);

    if (user == 0)
    {
        for (i = *s; i < dice_number + *s && i < cake_number; i++)  
            condition[i] = 1;
        *s += dice_number;
    }
    else
    {
        for (i = *e; i > (*e - dice_number) && i >= 0; i--)  
            condition[i] = 1;
        *e -= dice_number;
    }
    cake_display(name, condition, *left, *s, *e, cake_name);
}

void cake_display(char name[][8], int condition[], int left, int s, int e, char cake_name[])
{
    int i;
    char *eat_cake = "��", *remain_cake = "��";
    
    gotoxy(30, 5);
    if (left < 0)
        left = 0;
    printf("���� %s�� �� : %2d �� ", cake_name, left);

    for (i = 0; i < 2; i++)
    {
        gotoxy(i * 50 + 10, 6);
        printf("%s", name[i]);
    }

    for (i = 0; i < 30; i++)
        if (condition[i] == 1)
        {
            gotoxy(10 + i * 2, 8);
            printf("%s", eat_cake);
        }
        else
        {
            gotoxy(10 + i * 2, 8);
            printf("%s", remain_cake);
        }

    gotoxy(10, 9);
    printf("���� %s ��: %2d", cake_name, s);
    gotoxy(52, 9);
    printf("���� %s ��: %2d", cake_name, 29 - e);
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void set_color(int text_color, int bg_color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

void play_victory_music(void)
{
    Beep(_C, 300); Sleep(200);
    Beep(_D, 300); Sleep(200);
    Beep(_E, 300); Sleep(200);
    Beep(_F, 300); Sleep(200);
    Beep(_G, 700); Sleep(200);
}

