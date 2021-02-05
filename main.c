/*In The Name Of Allah
 *
 * Project : Battleship Game
 * Auth : ALIREZA ZARE ZEYNABADI (9931022)
 * CE Department @ AmirKabir University of Technology
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
void start() {
    printf("*********************************\n");
    printf("*     WELCOME TO BATTLESHIP     *\n");
    printf("*        BY ALIREZA ZARE        *\n");
    printf("*********************************\n");
    printf("Press Enter To Continue");
    getchar();
    system("cls");
}
void mainmenu() {
    printf("1. Play With Friend\n2. Play With Bot\n3. Load Last Game\n4. Setting\n5. Score Board\n6. Exit\n");
}
void play_with_friend();
void play_with_bot();
void load_last_game();
void setting();
void scoreboard();

int main() {
    system("color 10");
    start();
    int op;
    //mainmenu();

    while (op != '6') {
        mainmenu();
        scanf("%d",&op);
        system("cls");
        switch (op){
            case 1 :
                //play_with_friend();
                system("cls");
                break;
            case 2:
                //play_with_bot();
                system("cls");
                break;
            case 3 :
                //load_last_game();
                system("cls");
                break;
            case 4 :
                setting();
                system("cls");
                break;
            case 5 :
                //scoreboard();
                system("cls");
                break;
            case 6:
                exit(10);
            default:
                printf("Invalid Input Press Enter To Try Again");
                getchar();getchar();
                system("cls");
        }
    }
}
void setting(){
    int op1;
    printf("1. Theme\n0.Back\n");
    scanf("%d",&op1);
    if (op1 == 0)
        return;
    else if (op1 != 0 && op1!= 1){
        printf("Invalid input\nPress Enter To Try again");
        getchar();getchar();
        system("cls");
        setting();
    }
    else {
        system("cls");
        char op2;
        printf("                8 = Gray\n"
               "    1 = Blue        9 = Light Blue\n"
               "    2 = Green       A = Light Green\n"
               "    3 = Aqua        B = Light Aqua\n"
               "    4 = Red         C = Light Red\n"
               "    5 = Purple      D = Light Purple\n"
               "    6 = Yellow      E = Light Yellow\n"
               "    7 = White       F = Bright White\n");
        getchar();
        scanf("%c", &op2);
        switch (op2) {
            case '1' :
                system("color 10");
                break;
            case '2':
                system("color 20");
                break;
            case '3':
                system("color 30");
                break;
            case '4':
                system("color 40");
                break;
            case '5':
                system("color 50");
                break;
            case '6':
                system("color 60");
                break;
            case '7':
                system("color 70");
                break;
            case '8':
                system("color 80");
                break;
            case '9':
                system("color 90");
                break;
            case 'A':
                system("color A0");
                break;
            case 'B':
                system("color B0");
                break;
            case 'C':
                system("color C0");
                break;
            case 'D':
                system("color D0");
                break;
            case 'E':
                system("color E0");
                break;
            case 'F':
                system("color F0");
                break;
            default:
                printf("Invalid input\nPress Enter To Try again");
                getchar();
                getchar();
                system("cls");
                setting();
        }
    }
    return;
}
/*
 * With Thank to Saman Husseini ,Muhammad Fatemi, Amirparsa Salmankhah(DADDY) , Faraz Farangi Zadeh , and َ All TAs
 * For Assist me in learning C Programing
 */