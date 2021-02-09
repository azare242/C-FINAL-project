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
#include <string.h>
#include "maps.h"
#include "gameloop.h"
#include "bot.h"

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
    printf("1. Play With Friend\n2. Play With Bot\n3. Load Game\n4. Load Last Game\n5. Scoreboard\n6. Settings\n7. Exit\n");
}



void play_with_friend(User * head);
void play_with_bot(User * head);
void loadgame();
void load_last_game();
void setting();
void scoreboard(User * head);
void deletelist(User ** head);
void add(User ** head,char username[20]);
void init_user(User ** head);
void print(User * head);
void save(User * head);
User * loadnext (User * head, FILE * file);
User * load(User * head);
User * choseuser(User * head);
void initshowmap_empty(char map[map_rows][map_columns]);
void initplayermap_empty(int map[map_rows][map_columns]);
void printmap_for_set(int map[map_rows][map_columns]);
void getships(int map[map_rows][map_columns],Ships * head,int size);
void getshipsize1(int map[map_rows][map_columns],Ships * head);
void setmap(int map[map_rows][map_columns],Ships * head);

int main() {
    system("color 10");
    start();
    int op;
    User * list = NULL;
    list = load(list);

    while (op != '6') {
        mainmenu();
        scanf("%d",&op);
        system("cls");
        switch (op){
            case 1 :
                play_with_friend(list);
                system("cls");
                break;
            case 2:
                play_with_bot(list);
                system("cls");
                break;
            case 3 :
                //loadgame();
                system("cls");
                break;
            case 4 :
                //load_last_game();
                system("cls");
                break;
            case 5 :
                setting();
                system("cls");
                break;
            case 6:
                //scoreboard();
                system("cls");
            case 7 :
                exit(10);
            default:
                printf("Invalid Input Press Enter To Try Again\n");
                getchar();getchar();
                system("cls");
        }
    }
}
void setting() {
    int op1;
    printf("1. Theme\n0.Back\n");
    scanf("%d", &op1);
    if (op1 == 0)
        return;
    else if (op1 != 0 && op1 != 1) {
        printf("Invalid input\nPress Enter To Try again\n");
        getchar();
        getchar();
        system("cls");
        setting();
    } else {
        system("cls");
        char op2;
        printf("8 = Gray\n"
               "1 = Blue        9 = Light Blue\n"
               "2 = Green       A = Light Green\n"
               "3 = Aqua        B = Light Aqua\n"
               "4 = Red         C = Light Red\n"
               "5 = Purple      D = Light Purple\n"
               "6 = Yellow      E = Light Yellow\n"
               "7 = White       F = Bright White\n");
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
void deletelist(User ** head)
{
    User * cur = *head;
    User * next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}
void add(User ** head,char username[20])
{
    User *newuser = (User *)malloc(sizeof(User));
    strcpy(newuser->username,username);
    newuser->score = 0;
    newuser->next = NULL;
    if(*head == NULL)
        *head = newuser;
    else
    {
        User *lastuser = *head;
        while(lastuser->next != NULL)
        {
            lastuser = lastuser->next;
        }
        lastuser->next = newuser;
    }
}
void get_AND_add(User ** head) {
    char username[20];
    printf("Enter Username:\n");
    fflush(stdin);
    gets(username);

    if (*head == NULL) {
        add(head, username);
        return;
    }
    else {

        if (strcmp((*head)->username, username) == 0) {
            printf("Username is used!\n");
            printf("Press Enter To back");
            getchar();
            return;

        } else {
            User *cur = *head;
            while (cur) {
                if (strcmp(cur->username, username) == 0) {
                    printf("Username is used!\n");
                    printf("Press Enter To back");
                    getchar();
                    return;
                }
                cur = cur->next;
            }
        }
        add(head,username);
        return;
    }
}
void print(User * head)
{
    User * temp = head;
    int i = 1;
    for ( temp ; temp != NULL ; temp=temp->next){
        printf("%d)%s %d\n",i,temp->username,temp->score);
        i++;
    }
}
void save(User * head)
{
    FILE * save;
    fopen_s(&save,"USERS.bin","wb");
    if(save != NULL){
        User * cur = head;
        User * hold = NULL;
        while(cur != NULL)
        {
            hold = cur->next;

            cur->next = NULL;

            fseek(save,0,SEEK_END);
            fwrite(cur, sizeof(User),1,save);

            cur->next = hold;
            hold = NULL;
            cur = cur->next;
        }
        fclose(save);
        save = NULL;
    }
    else {
        printf("CAN'T SAVE DATA\n");
        return;
    }
}
User * loadnext(User * head, FILE * file)
{
    int value;
    if (head == NULL){
        head = malloc(sizeof(User));
        value = fread(head, sizeof(User), 1 ,file);
        head->next = NULL;
    } else{
        User * temp = head;
        User * newuser = malloc(sizeof(User));
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        value = fread(newuser, sizeof(User),1,file);
        temp->next = newuser;
        newuser->next = NULL;
    }
    return head;
}
User * load(User * head) {
    FILE *file;
    fopen_s(&file, "USERS.bin", "rb");
    if (file != NULL) {
        deletelist(&head);
        head = NULL;
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        int entries = (int) (size / (sizeof(User)));
        int i = 0;
        for ( i = 0; i < entries; i++) {
            fseek(file, sizeof(User) * i,SEEK_SET);
            head = loadnext(head, file);
        }
    } else {
        printf("CAN'T LOAD DATA\n");
    }
    fclose(file);
    return head;
}
User * choseuser(User * head){
    User *player = (User *)malloc(sizeof(User));
    print(head);
    int choose;
    printf("Please Enter Number Of Your Profile\n");
    scanf("%d", &choose);
    User *temp = head;
    int i = 1;
    for (temp; temp != NULL; temp = temp->next) {
        if (i == choose) {
            strcpy(player->username,temp->username);
            player->score = temp->score;
            player->next = NULL;
            break;
        } else i++;
    }
    return player;
}
void initshowmap_empty(char map[map_rows][map_columns]){
    for (int i = 0 ; i < map_rows ; i++)
    {
        for (int j = 0 ; j < map_columns ; j++)
        {
            map[i][j] = (char)220;
        }
    }
}
void initplayermap_empty(int map[map_rows][map_columns]) {
    for (int i = 0; i < map_rows; i++) {
        for (int j = 0; j < map_columns; j++) {
            map[i][j] = 0;
        }
    }
}
void printmap_for_set(int map[map_rows][map_columns]){
    printf("    0  1  2  3  4  5  6  7  8  9\n");
    int column_meter = 0;
    for (int i = 0 ; i < map_rows ; i++)
    {

        if (column_meter < 10)
            printf("%d   ",column_meter);
        else if (column_meter == 10) printf("%d  ",column_meter);

        for (int j = 0 ; j < map_columns ; j++)
        {
            printf("%d  ",map[i][j]);
        }
        column_meter++;
        printf("\n");
    }
}
void getships(int map[map_rows][map_columns],Ships * head,int size){
    int xb,xe,yb,ye,state;
    while(1) {
        printmap_for_set(map);
        printf("Enter State of Ship size %d\n(1 For HORIZONTAL , 2 For VERTICAL)\n",size);
        scanf("%d", &state);
        system("cls");
        if (state == 1) break;
        else if (state == 2) break;
        else {
            printf("Invalid Input,Press Enter To Try Again\n");
            getchar();
            getchar();
            system("cls");
        }
    }
    if (state == 1){
        while (1){
            printmap_for_set(map);
            printf("Enter Beginning(ROW COLUMN) of SIZE %d Ship\n",size);
            scanf("%d %d",&xb,&yb);
            system("cls");
            printmap_for_set(map);
            printf("Enter End (ROW COLUMN) of SIZE %d Ship\n",size);
            scanf("%d %d",&xe,&ye);
            system("cls");
            if (xe == xb && ye - yb + 1 == size && ye > yb && isnotshiphere(xb,xe,yb,ye,state,map)) {
                break;
            }
            else{
                printf("Invalid Input,Press Enter To Try Again\n");getchar();getchar();
                system("cls");
            }
            system("cls");
        }
    }
    else if (state == 2){
        while (1){
            printmap_for_set(map);
            printf("Enter Beginning(ROW COLUMN) of SIZE %d Ship\n",size);
            scanf("%d %d",&xb,&yb);
            system("cls");
            printmap_for_set(map);
            printf("Enter End (ROW COLUMN) of SIZE %d Ship\n",size);
            scanf("%d %d",&xe,&ye);
            system("cls");
            if (ye == yb && xe - xb + 1 == size && xe > xb && isnotshiphere(xb,xe,yb,ye,state,map)) {
                break;
            }
            else{
                printf("Invalid Input,Press Enter To Try Again\n");getchar();getchar();
                system("cls");
            }
            system("cls");

        }
    }
    setshipsonmap(xb,xe,yb,ye,state,map);
    newship(&head,xb,yb,xe,ye,size,state);
}
void getshipsize1(int map[map_rows][map_columns],Ships * head)
{
    int x1,y1,xt,yt;
    while (1) {
        printmap_for_set(map);
        printf("Enter The Coordinates (ROW COLUMN)Of Size 1 Ship\n");
        scanf("%d %d", &x1, &y1);
        xt = x1;
        yt = y1;
        system("cls");
        if (isnotshiphere(x1, xt, y1, yt, 1, map)) break;
        else {
            printf("Invalid Input,Press Enter To Try Again\n");
            getchar();
            getchar();
            system("cls");
        }

        system("cls");
    }
    setshipsonmap(x1,xt,y1,yt,1,map);
    newship(&head,x1,y1,xt,yt,1,1);
}
void setmap(int map[map_rows][map_columns],Ships * head)
{
    getships(map,head,5);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getships(map,head,3);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getships(map,head,3);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getships(map,head,2);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getships(map,head,2);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getships(map,head,2);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getshipsize1(map,head);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getshipsize1(map,head);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getshipsize1(map,head);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
    getshipsize1(map,head);
    printmap_for_set(map);
    printf("\nPress Enter To Continue\n");
    getchar();getchar();
    system("cls");
}
void play_with_friend(User * head)
{
    User * player1;
    printf("FirstPlayer\n");
    printf("1.Chose User\n2.New User\n");
    int opp;
    scanf("%d",&opp);
    system("cls");
    if (opp == 1){
        player1 = choseuser(head);
    }
    else if(opp == 2){
        player1 = (User *)malloc(sizeof(User));
        get_AND_add(&head);
        save(head);
        User * temp;
        for ( temp = head ; temp->next != NULL ; temp = temp->next);
        strcpy(player1->username,temp->username);
        player1->score = temp->score;
        player1->next = NULL;
    }
    system("cls");
    User *player2;
    printf("Second Player\n");
    printf("1.Chose User\n2.New User\n");
    scanf("%d",&opp);
    system("cls");
    if (opp == 1) {
        player2 = choseuser(head);
    }
    else if (opp == 2) {
        player2 = (User *)malloc(sizeof(User));
        get_AND_add(&head);
        save(head);
        User * temp;
        for ( temp = head ; temp->next != NULL ; temp = temp->next);
        strcpy(player2->username,temp->username);
        player2->score = temp->score;
        player2->next = NULL;
    }
    system("cls");
    int map_player1[map_rows][map_columns] , map_player2[map_rows][map_columns];
    initplayermap_empty(map_player1);
    initplayermap_empty(map_player2);
    char map_player1_for_show[map_rows][map_columns],map_player2_for_show[map_rows][map_columns];
    initshowmap_empty(map_player1_for_show);
    initshowmap_empty(map_player2_for_show);
    Ships *player1_ships = NULL , *player2_ships = NULL;
    setmap(map_player1,player1_ships);
    setmap(map_player2,player2_ships);
    gameloop(map_player1,map_player2,player1_ships,player2_ships,map_player1_for_show,map_player2_for_show,player1,player2);


}
void play_with_bot(User * head) {
    User *player1;
    printf("FirstPlayer\n");
    printf("1.Chose User\n2.New User\n");
    int opp;
    scanf("%d", &opp);
    system("cls");
    if (opp == 1) {
        player1 = choseuser(head);
    } else if (opp == 2) {
        player1 = (User *) malloc(sizeof(User));
        get_AND_add(&head);
        save(head);
        User *temp;
        for (temp = head; temp->next != NULL; temp = temp->next);
        strcpy(player1->username, temp->username);
        player1->score = temp->score;
        player1->next = NULL;
    }
    int map_player[map_rows][map_columns],map_bot[map_rows][map_columns];
    char map_player_show[map_rows][map_columns], map_bot_show[map_rows][map_columns];
    initplayermap_empty(map_player);
    initshowmap_empty(map_player_show);
    initplayermap_empty(map_bot);
    initshowmap_empty(map_bot_show);
    Ships * player_ships = NULL, * bot_ships = NULL;
    bot_set_map(map_bot,bot_ships);
    setmap(map_player,player_ships);


}
/*
 * With Thank to Saman Husseini ,Muhammad Fatemi, Amirparsa Salmankhah(DADDY) , Faraz Farangi Zadeh , and َ All TAs
 * For Assist me in learning C Programing
 */