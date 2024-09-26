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
    printf("아무키나 누르면 다음 순서를 진행합니다.");
    getch();

    do
    {
        for (i = 0; i < 2; i++)
        {
            system("cls");
            game_control(user_name, cake_condition, &cake_left, i, &start, &end, cake_name);

            if (cake_left <= 0)  // 과자가 0개 이하일 때 게임 종료
            {
                winner = i;
                loser = 1 - i;
                break;
            }

            set_color(YELLOW, BLACK);
            gotoxy(10, 12);
            printf("아무키나 누르면 다음 순서를 진행합니다.");
            getch();
        }
    } while (cake_left > 1);

    set_color(RED, BLACK); 
    gotoxy(10, 12);
    play_victory_music();
    printf("%s님이 이겼습니다.", user_name[winner]);
    printf("%s님이 졌습니다.", user_name[loser]);

    set_color(WHITE, BLACK); 
    gotoxy(10, 13);
    printf("게임을 종료합니다.\n");

    return 0;
}

void intro_game(void)
{
    system("cls");
    printf("주사위로 과자먹기 게임 \n\n");
    printf("두사람이 서로 양끝의 주사위 숫자만큼\n");
    printf("과자를 먹는 게임입니다. \n");
    printf("마지막 남은 과자를 먹는 사람이 이깁니다. \n\n");
    printf("아무키나 누르면 게임참가자를\n");
    printf("입력합니다.\n");
    getch();
}

void input_participant(char user_name[][8], char cake_name[])
{
    system("cls");
    printf("1번 참가자의 이름을 입력하고 Enter>");
    scanf("%s", user_name[0]);
    printf("2번 참가자의 이름을 입력하고 Enter>");
    scanf("%s", user_name[1]);
    printf("과자의 이름을 입력하고 Enter>");
    scanf("%s", cake_name);
    printf("아무키나 누르면 게임을 시작합니다...");
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
    printf("%s님의 주사위 숫자는 %d입니다.", name[user], dice_number);

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
    char *eat_cake = "★", *remain_cake = "☆";
    
    gotoxy(30, 5);
    if (left < 0)
        left = 0;
    printf("남은 %s의 수 : %2d 개 ", cake_name, left);

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
    printf("먹은 %s 수: %2d", cake_name, s);
    gotoxy(52, 9);
    printf("먹은 %s 수: %2d", cake_name, 29 - e);
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

