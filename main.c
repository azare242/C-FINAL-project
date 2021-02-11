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
#include <string.h>
#include <time.h>
#include "maps.h"
#include "gameloop.h"

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
void get_AND_add(User ** head);
void add(User ** head,char username[20]);
void init_user(User ** head);
void print(User * head);
void save(User * head);
User * loadnext (User * head, FILE * file);
User * load(User * head);
User * choseuser(User * head);
void rev(User * current, User * previous, User ** head);
void reve(User ** head);
void sort(User ** head);
void print_for_scoreboard(User * head);
void initshowmap_empty(char map[map_rows][map_columns]);
void initplayermap_empty(int map[map_rows][map_columns]);
void printmap_for_set(int map[map_rows][map_columns]);
void printmap(char map[map_rows][map_columns]);
Ships * addship(int xb,int yb,int xe,int ye,int size,int state);
void newship(Ships ** head,int xb,int yb,int xe,int ye,int size,int state);
bool isnotshiphere(int xb,int xe,int yb,int ye,int state,int map[map_rows][map_columns]);
int scan_state(int map[map_rows][map_columns],int size);

typedef struct coords{
    int xb;
    int xe;
    int yb;
    int ye;
}Coords;
Coords scan_coords_notsize1(int map[map_rows][map_columns],int state,int size);
Coords scan_coords_size1(int map[map_rows][map_columns]);
typedef struct ships_map{
    int playermap[10][10];
    Ships * player_ships;
}PlayerShipsMap;
PlayerShipsMap set_map(PlayerShipsMap player);
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
                list = load(list);
                break;
            case 2:
                play_with_bot(list);
                list = load(list);
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
                scoreboard(list);
                list = load(list);
                system("cls");
                break;
            case 6:
                setting();
                system("cls");
                break;
            case 7 :
                exit(10);
            default:
                printf("Invalid Input Press Enter To Try Again\n");
                getchar();getchar();
                system("cls");
        }
    }
}
void rev(User * current, User * previous, User ** head){
    if (!current->next) {
        *head = current;
        current->next = previous;
        return;
    }
    User * next = current->next;
    current->next = previous;
    rev(next, current, head);
}

void reve(User ** head){
    if (!head)
        return;
    rev(*head, NULL, head);
}

void sort(User ** head) {
    User *prev = *head;
    User *curr = (*head)->next;

    while (curr != NULL) {
        if (curr->score < prev->score) {
            prev->next = curr->next;
            curr->next = *head;
            *head = curr;

            curr = prev;
        } else
            prev = curr;
        curr = curr->next;
    }
}
void print_for_scoreboard(User * head)
{
    printf("#|USERNAME            |SCORE     \n");
    User * temp = head;
    int i = 1;
    for ( temp ; temp != NULL ; temp=temp->next){
        printf("%d|%-20s|%-10d\n",i,temp->username,temp->score);
        i++;
    }
}

void scoreboard(User * head)
{
    User * temp = head;
    sort(&temp);
    reve(&temp);
    print_for_scoreboard(temp);
    printf("PRESS ENTER TO RETURN TO MAIN MENU\n");
    getchar();getchar();
    system("cls");
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
            map[i][j] = '-';
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
Ships * addship(int xb,int yb,int xe,int ye,int size,int state){
    Ships * new = (Ships *)malloc(sizeof(Ships));
    new->cord_x_b = xb;
    new->cord_x_e = xe;
    new->cord_y_b = yb;
    new->cord_y_e = ye;
    new->size = size;
    new->state = state;
    new->next = NULL;
    return new;
}
void newship(Ships ** head, int xb,int yb,int xe,int ye,int size,int state){
    Ships * new = addship(xb,yb,xe,ye,size,state);
    new->next = *head;
    *head = new;
}bool isnotshiphere(int xb,int xe,int yb,int ye,int state ,int map[map_rows][map_columns]) {
    if (state == 1) {
        for (int i = yb ; i < ye + 1 ; i++){
            if (map[xb][i] == 1 || map[xb][i] == 2) return false;
        }
        return true;
    }
    else if (state == 2){
        for (int i = xb ; i < xe+1 ; i++){
            if (map[i][yb] == 1 || map[i][yb] == 2) return false;
        }
        return true;
    }
}
int scan_state(int map[map_rows][map_columns],int size){
    int state;
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
    return state;
}
Coords scan_coords_notsize1(int map[map_rows][map_columns],int state,int size){
    Coords result;
    int xb,xe,yb,ye;
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
                result.xb = xb ; result.xe = xe; result.yb = yb ; result.ye = ye;
                break;
            }
            else{
                printf("Invalid Input,Press Enter To Try Again\n");getchar();getchar();
                system("cls");
            }
            system("cls");
        }
        return result;
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
            if (ye == yb && xe - xb + 1 == size && xe > xb && isnotshiphere(xb,xe,yb,ye,state,map)){
                result.xb = xb ; result.xe = xe; result.yb = yb ; result.ye = ye;
                break;
            }
            else{
                printf("Invalid Input,Press Enter To Try Again\n");getchar();getchar();
                system("cls");
            }
            system("cls");

        }
        return result;
    }
}
Coords scan_coords_size1(int map[map_rows][map_columns]) {
    Coords result;
    int x1, y1, xt, yt;
    while (1) {
        printmap_for_set(map);
        printf("Enter The Coordinates (ROW COLUMN)Of Size 1 Ship\n");
        scanf("%d %d", &x1, &y1);
        xt = x1;
        yt = y1;
        system("cls");
        if (isnotshiphere(x1, xt, y1, yt, 1, map)) {
            result.xb = x1;
            result.xe = xt;
            result.yb = y1;
            result.ye = yt;
            break;
        } else {
            printf("Invalid Input,Press Enter To Try Again\n");
            getchar();
            getchar();
            system("cls");
        }

        system("cls");
    }
    return result;
}
PlayerShipsMap set_map(PlayerShipsMap player)
{
    PlayerShipsMap temp = player;
    int state[7];
    state[0] = scan_state(temp.playermap,5);
    Coords coords ;
    coords = scan_coords_notsize1(temp.playermap,state[0],5);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[0],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,5,state[0]);
    state[1] = scan_state(temp.playermap,3);
    coords = scan_coords_notsize1(temp.playermap,state[1],3);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[1],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,3,state[1]);
    state[2] = scan_state(temp.playermap,3);
    coords = scan_coords_notsize1(temp.playermap,state[2],3);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[2],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,3,state[2]);
    state[3] = scan_state(temp.playermap,2);
    coords = scan_coords_notsize1(temp.playermap,state[3],2);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[3],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,2,state[3]);
    state[4] = scan_state(temp.playermap,2);
    coords = scan_coords_notsize1(temp.playermap,state[4],2);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[4],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,2,state[4]);
    state[5] = scan_state(temp.playermap,2);
    coords = scan_coords_notsize1(temp.playermap,state[5],2);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[5],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,2,state[5]);
    state[6] = 1;
    coords = scan_coords_size1(temp.playermap);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[6],temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,1,state[6]);
    coords = scan_coords_size1(temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,1,state[6]);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[6],temp.playermap);
    coords = scan_coords_size1(temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,1,state[6]);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[6],temp.playermap);
    coords = scan_coords_size1(temp.playermap);
    newship(&temp.player_ships,coords.xb,coords.yb,coords.xe,coords.ye,1,state[6]);
    setshipsonmap(coords.xb,coords.xe,coords.yb,coords.ye,state[6],temp.playermap);
    return temp;

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
    PlayerShipsMap temp1,temp2;
    PlayerShipsMap player1_ships_map ,player2_ships_map;
    initplayermap_empty(temp1.playermap);
    initplayermap_empty(temp2.playermap);
    temp1.player_ships = NULL;
    temp2.player_ships = NULL;
    player1_ships_map = set_map(temp1);
    player2_ships_map = set_map(temp2);
    char map_show1[map_rows][map_columns] , map_show2[map_rows][map_columns];
    initshowmap_empty(map_show1);initshowmap_empty(map_show2);
    gameloop(player1_ships_map.playermap,player2_ships_map.playermap,&player1_ships_map.player_ships,&player2_ships_map.player_ships,map_show1,map_show2,player1,player2);

    for(User * temp = head ; temp != NULL ; temp = temp->next)
    {
        if(strcmp(temp->username,player1->username) == 0){
            temp->score += player1->score;
        }
        if (strcmp(temp->username,player2->username) == 0){
            temp->score += player2->score;
        }
    }
    save(head);

    return;

}
PlayerShipsMap set_map_bot(PlayerShipsMap bot)
{
    PlayerShipsMap temp = bot;
    setshipsonmap(1,1,1,5,1,temp.playermap);
    newship(&temp.player_ships,1,2,1,6,5,1);
    setshipsonmap(0,0,7,9,1,temp.playermap);
    newship(&temp.player_ships,0,7,0,9,3,1);
    setshipsonmap(2,2,7,9,1,temp.playermap);
    newship(&temp.player_ships,2,7,2,9,3,1);
    setshipsonmap(5,6,0,0,2,temp.playermap);
    newship(&temp.player_ships,5,0,6,0,2,2);
    setshipsonmap(5,6,3,3,2,temp.playermap);
    newship(&temp.player_ships,5,3,6,2,2,2);
    setshipsonmap(5,6,5,5,2,temp.playermap);
    newship(&temp.player_ships,5,5,6,5,2,2);
    setshipsonmap(9,9,0,0,1,temp.playermap);
    newship(&temp.player_ships,9,0,9,0,1,1);
    setshipsonmap(9,9,2,2,1,temp.playermap);
    newship(&temp.player_ships,9,2,9,2,1,1);
    setshipsonmap(9,9,4,4,1,temp.playermap);
    newship(&temp.player_ships,9,4,9,4,1,1);
    setshipsonmap(9,9,7,7,1,temp.playermap);
    newship(&temp.player_ships,9,7,9,7,1,1);



    return temp;
}

void play_with_bot(User * head){
    User * player;
    printf("Player\n");
    printf("1.Chose User\n2.New User\n");
    int opp;
    scanf("%d",&opp);
    system("cls");
    if (opp == 1){
        player = choseuser(head);
    }
    else if(opp == 2){
        player = (User *)malloc(sizeof(User));
        get_AND_add(&head);
        save(head);
        User * temp;
        for ( temp = head ; temp->next != NULL ; temp = temp->next);
        strcpy(player->username,temp->username);
        player->score = temp->score;
        player->next = NULL;
    }
    system("cls");
    User * bot = (User *)malloc(sizeof(User));
    strcpy(bot->username,"BOT");
    bot->score = 0;
    bot->next = NULL;
    PlayerShipsMap temp1,temp2;
    PlayerShipsMap player_ships_map ,bot_ships_map;
    initplayermap_empty(temp1.playermap);
    initplayermap_empty(temp2.playermap);
    char map_player_for_show[map_rows][map_columns] , map_bot_for_show[map_rows][map_columns];
    initshowmap_empty(map_bot_for_show);initshowmap_empty(map_player_for_show);
    temp1.player_ships = NULL;
    temp2.player_ships = NULL;
    bot_ships_map = set_map_bot(temp2);
    printf("\nBOT MAP SAT\nPress Enter to Continue");
    getchar();getchar();
    system("cls");
    player_ships_map = set_map(temp1);
    gameloop_with_bot(player_ships_map.playermap,bot_ships_map.playermap,&player_ships_map.player_ships,&bot_ships_map.player_ships,map_player_for_show,map_bot_for_show,player,bot);

    for(User * temp = head ; temp != NULL ; temp = temp->next)
    {
        if(strcmp(temp->username,player->username) == 0){
            temp->score += player->score;
        }
    }
    save(head);

    return;


}
/*
 * With Thank to Saman Husseini ,Muhammad Fatemi, Amirparsa Salmankhah(DADDY) , Faraz Farangi Zadeh , and َ All TAs
 * For Assist me in learning C Programing
 */