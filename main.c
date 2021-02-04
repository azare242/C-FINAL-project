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
                //setting();
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
/*
 * With Thank to Saman Husseini ,Muhammad Fatemi, Amirparsa Salmankhah(DADDY) , Faraz Farangi Zadeh , and َ All TAs
 * For Assist me in learning C Programing
 */