#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void printmap(char map[map_rows][map_columns])
{
    printf("    0  1  2  3  4  5  6  7  8  9\n");
    int column_meter = 0;
    for (int i = 0 ; i < map_rows ; i++)
    {

        if (column_meter < 10)
            printf("%d   ",column_meter);
        else if (column_meter == 10) printf("%d  ",column_meter);

        for (int j = 0 ; j < map_columns ; j++)
        {
            printf("%c  ",map[i][j]);
        }
        column_meter++;
        printf("\n");
    }
}
bool is_map_emptied(int map[map_rows][map_columns]){
    for (int i = 0 ; i < map_rows ; i++){
        for (int j = 0 ; j < map_columns ; j++){
            if (map[i][j] == 1) return false;
        }
    }
    return true;
}
void gameloop(int map_player1[map_rows][map_columns],int map_player2[map_rows][map_columns],Ships * head1,Ships * head2,char map_player1_for_show[map_rows][map_columns],char map_player2_for_show[map_rows][map_columns],User * player1,User * player2)
{
    int temp_score_player1 = 0 , temp_score_player2 = 0;
    int attack_x , attack_y;
    while (1){

        if (is_map_emptied(map_player1)){
            player2->score += temp_score_player2;
            player1->score += temp_score_player1 / 2;
            break;
        }
        if (is_map_emptied(map_player2)){
            player2->score += temp_score_player2 / 2;
            player1->score += temp_score_player1;
            break;
        }

        while (1) {
            printf("%s Turn\n%s Map:\n", player1->username, player2->username);
            printmap(map_player2_for_show);
            printf("\nEnter Coordinates (ROW COLUMN) Of Place You Want To Attack\n");
            scanf("%d %d", &attack_x, &attack_y);
            system("cls");

            if ( (map_player2[attack_x][attack_y] == 0 || map_player2[attack_x][attack_y] == 2) && map_player2_for_show[attack_x][attack_y] == '-') {
                map_player2_for_show[attack_x][attack_y] = 'W';
                printf("Oops! The shooting went wrong!!!\n");
                printmap(map_player2_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();
                getchar();
                system("cls");
                break;
            } else if (map_player2[attack_x][attack_y] == 1 && map_player2_for_show[attack_x][attack_y] == '-') {
                printf("KABOOM!!! YOU HIT %s Ship\n", player2->username);
                map_player2_for_show[attack_x][attack_y] = 'E';
                map_player2[attack_x][attack_y] = -1;
                printmap(map_player2_for_show);
                temp_score_player1++;
                /*
                Ships *temp1 = *head2;
                while (temp1->next != NULL) {

                    if (isshipdistroyed(temp1, map_player2_for_show)) {
                        update_playermap(map_player2, temp1);
                        update_showmap(map_player2_for_show, temp1);
                        if (temp1->size == 5) temp_score_player1 += 5;
                        else if (temp1->size == 3) temp_score_player1 += 8;
                        else if (temp1->size == 2) temp_score_player1 += 12;
                        else if (temp1->size == 1) temp_score_player1 += 25;
                        //delete_ship(head2,temp1);
                        break;

                    } else temp1 = temp1->next;
                }
                 */
                printf("\nPress Enter To Continue\n");
                getchar();
                getchar();
                system("cls");
            }
            else if ( (map_player2_for_show[attack_x][attack_y] == 'E' || map_player2_for_show[attack_x][attack_y] == 'W' || map_player2_for_show[attack_x][attack_y] == 'C' )&& map_player2_for_show[attack_x][attack_y] != '-' ){
                printf("You Can't HIT This Place\nPress Enter To Try Again\n");
                getchar();getchar();
                system("cls");
            }
        }
        while (1){
            printf("%s Turn\n%s Map:\n",player2->username,player1->username);
            printmap(map_player1_for_show);
            printf("\nEnter Coordinates (ROW COLUMN) Of Place You Want To Attack\n");
            scanf("%d %d",&attack_x,&attack_y);
            system("cls");
            if (map_player1[attack_x][attack_y] == 0 || map_player1[attack_x][attack_y] == 2){
                map_player1_for_show[attack_x][attack_y] = 'W';
                printf("Oops! The shooting went wrong!!!\n");
                printmap(map_player1_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
                break;
            }
            else if (map_player1[attack_x][attack_y] == 1 && map_player1_for_show[attack_x][attack_y] == '-'){
                map_player1_for_show[attack_x][attack_y] = 'E';
                map_player1[attack_x][attack_y] = -1;
                printmap(map_player1_for_show);
                temp_score_player2++;
                /*
                Ships * temp2 = *head1;
                while (temp2->next!= NULL)
                {
                    if (isshipdistroyed(temp2,map_player1_for_show)){
                        update_playermap(map_player1,temp2);
                        update_showmap(map_player1_for_show,temp2);
                        if (temp2->size == 5) temp_score_player2 += 5;
                        else if (temp2->size == 3) temp_score_player2 += 8;
                        else if (temp2->size == 2) temp_score_player2 += 12;
                        else if (temp2->size == 1) temp_score_player2 += 25;
                        //delete_ship(head1,temp2);
                        break;
                    }
                    else temp2 = temp2->next;
                }
                 */
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
            }
            else if ((map_player1_for_show[attack_x][attack_y] == 'E' || map_player1_for_show[attack_x][attack_y] == 'W' || map_player1_for_show[attack_x][attack_y] == 'C' ) && map_player1_for_show[attack_x][attack_y] != '-'){
                printf("You Can't HIT This Place\nPress Enter To Try Again\n");
                getchar();getchar();
                system("cls");
            }
        }


    }

}