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
typedef struct users{
    char username[10];
    int score;
    struct users * next;
}User;

void play_with_friend();
void play_with_bot();
void load_last_game();
void setting();
void scoreboard();
void deletelist(User ** head);
void add(User ** head,char username[20]);
void init_user(User ** head);
void print(User * head);
void save(User * head);
User * loadnext (User * head, FILE * file);
User * load(User * head);


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
/*
 * With Thank to Saman Husseini ,Muhammad Fatemi, Amirparsa Salmankhah(DADDY) , Faraz Farangi Zadeh , and َ All TAs
 * For Assist me in learning C Programing
 */