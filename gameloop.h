bool is_map_emptied(int map[map_rows][map_columns]){
    for (int i = 0 ; i < map_rows ; i++){
        for (int j = 0 ; j < map_columns ; j++){
            if (map[i][j] == 1) return false;
        }
    }
    return true;
}
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
bool is_ship_distroyed(char map[map_rows][map_columns],int xb,int xe,int yb,int ye,int state)
{
    if (state == 1)
    {
        for (int i = yb ; i < ye + 1 ; i++){
            if (map[xb][i] == '-') return false;
        }
        return true;
    }
    else if (state == 2){
        for (int i = xb ; i < xe + 1 ; i++){
            if (map[i][yb] == '-') return false;
        }
        return true;
    }
}
void delete_ship(Ships ** ships,int xb, int xe , int yb, int ye,int state , int size) {

    if ((*ships)->cord_x_b == xb && (*ships)->cord_x_e == xe && (*ships)->cord_y_b == yb && (*ships)->cord_y_e == ye && (*ships)->state == state && (*ships)->size == size) {
        Ships *delete = *ships;
        *ships = (*ships)->next;
        free(delete);
        return;
    }
    for (Ships *temp = *ships; temp->next != NULL; temp = temp->next) {
        if (temp->next->cord_x_b == xb && temp->next->cord_x_e == xe && temp->next->cord_y_b == yb && temp->next->cord_y_e == ye && temp->next->state == state && temp->next->size == size) {
            Ships * delete = temp->next;
            temp->next = temp->next->next;
            free(delete);
            return;
        }
    }
}
int complete_explode_score(int size)
{
    if (size == 1) return 25;
    else if (size == 2) return 12;
    else if (size == 3) return 8;
    else if (size == 5) return 5;
}
void gameloop(int map_player1[map_rows][map_columns],int map_player2[map_rows][map_columns],Ships ** head1,Ships ** head2,char map_player1_for_show[map_rows][map_columns],char map_player2_for_show[map_rows][map_columns],User * player1,User * player2)
{
    int temp_score_player1 = 0 , temp_score_player2 = 0;
    int attack_x , attack_y;
    while (1){
        if (is_map_emptied(map_player1)){
            player2->score += temp_score_player2;
            player1->score += temp_score_player1 / 2;
            printf("\n%s WINS",player2->username);
            printmap(map_player2_for_show);
            printmap(map_player1_for_show);
            getchar();
            getchar();
            system("cls");
            return;
        }
        if (is_map_emptied(map_player2)){
            player2->score += temp_score_player2 / 2;
            player1->score += temp_score_player1;
            printf("\n%s WINS",player1->username);
            printmap(map_player2_for_show);
            printmap(map_player1_for_show);

            getchar();
            getchar();
            system("cls");
            return;
        }

        while (1){
            /*
            while (1){
                int op1 ;
                printf("1.Continue\n2.SaveGameAndReturnToMainMenu\n");
                scanf("%d",&op1);
                if(op1 == 1) break;
                else if (op1 == 2){

                    return;
                }
            }
             */
            printf("%s Turn\n%s Map:\n",player1->username,player2->username);
            printmap(map_player2_for_show);
            printf("\nEnter Coordinates (ROW COLUMN) Of Place You Want To Attack\n");
            scanf("%d %d",&attack_x,&attack_y);
            system("cls");

            if ((map_player2[attack_x][attack_y] == 0 || map_player2[attack_x][attack_y] == 2 ) && map_player2_for_show[attack_x][attack_y] == '-') {
                map_player2_for_show[attack_x][attack_y] = 'W';
                printf("Oops! The shooting went wrong!!!\n");
                printmap(map_player2_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
                break;
            }
            else if (map_player2[attack_x][attack_y] == 1 && map_player2_for_show[attack_x][attack_y] == '-') {
                printf("KABOOM!!! YOU HIT %s Ship\n",player2->username);
                map_player2_for_show[attack_x][attack_y] = 'E';
                map_player2[attack_x][attack_y] = -1;
                for (Ships * temp = *head2 ; temp!= NULL ; temp = temp->next)
                {
                    if(is_ship_distroyed(map_player2_for_show,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state)) {
                        update_showmap(map_player2_for_show,temp->state,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e);
                        delete_ship(head2,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state,temp->size);
                        temp_score_player1 += complete_explode_score(temp->size);
                    }
                }
                printmap(map_player2_for_show);
                temp_score_player1++;
                printf("\nPress Enter To Continue\n");
                getchar();
                getchar();
                system("cls");
                //check_ships(*head2,map_player2_for_show,map_player2,temp_score_player1);
            }
            else if (map_player2_for_show[attack_x][attack_y] != '-'){
                printf("You Can't HIT This Place\nPress Enter To Try Again\n");
                getchar();getchar();
                system("cls");
            }
        }
        while (1){
            /*
            while (1){
                int op2 ;
                printf("1.Continue\n2.SaveGameAndReturnToMainMenu\n");
                scanf("%d",&op2);
                if(op2 == 1) break;
                else if (op2 == 2){

                    return;
                }
            }
             */
            printf("%s Turn\n%s Map:\n",player2->username,player1->username);
            printmap(map_player1_for_show);
            printf("\nEnter Coordinates (ROW COLUMN) Of Place You Want To Attack\n");
            scanf("%d %d",&attack_x,&attack_y);
            system("cls");
            if ((map_player1[attack_x][attack_y] == 0 || map_player1[attack_x][attack_y] == 2 ) && map_player1_for_show[attack_x][attack_y] == '-'){
                map_player1_for_show[attack_x][attack_y] = 'W';
                printf("Oops! The shooting went wrong!!!\n");
                printmap(map_player1_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
                break;
            }
            else if (map_player1[attack_x][attack_y] == 1 && map_player1_for_show[attack_x][attack_y] == '-'){
                printf("KABOOM!!! YOU HIT %s Ship\n",player1->username);
                map_player1_for_show[attack_x][attack_y] = 'E';
                map_player1[attack_x][attack_y] = -1;
                for (Ships * temp = *head1 ; temp!= NULL ; temp = temp->next)
                {
                    if(is_ship_distroyed(map_player1_for_show,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state)) {
                        update_showmap(map_player1_for_show,temp->state,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e);
                        delete_ship(head1,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state,temp->size);
                        temp_score_player2 += complete_explode_score(temp->size);
                    }
                }
                printmap(map_player1_for_show);
                temp_score_player2++;
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
                //check_ships(*head1,map_player1_for_show,map_player1,temp_score_player2);
            }
            else if (map_player1_for_show[attack_x][attack_y] != '-'){
                printf("You Can't HIT This Place\nPress Enter To Try Again\n");
                getchar();getchar();
                system("cls");
            }
        }


    }

}
void gameloop_with_bot(int map_player[map_rows][map_columns],int map_bot[map_rows][map_columns],Ships ** player_ships,Ships ** bot_ships,char map_player_for_show[map_rows][map_columns],char map_bot_for_show[map_rows][map_columns],User * player,User * bot)
{
    int temp_score = 0;
    int attack_x , attack_y ;
    while (1)
    {
        if (is_map_emptied(map_player)){
            player->score += temp_score/ 2;
            printf("\n%s WINS",bot->username);
            printmap(map_player_for_show);
            printmap(map_bot_for_show);
            getchar();
            getchar();
            system("cls");
            return;
        }
        if (is_map_emptied(map_bot)){
            player->score += temp_score;
            printf("\n%s WINS",player->username);
            printmap(map_player_for_show);
            printmap(map_bot_for_show);
            getchar();
            getchar();
            system("cls");
            return;
        }

        while (1){
            printf("You Turn\nBot Map:\n");
            printmap(map_bot_for_show);
            printf("\nEnter Coordinates (ROW COLUMN) Of Place You Want To Attack\n");
            scanf("%d %d",&attack_x,&attack_y);
            system("cls");

            if ((map_bot[attack_x][attack_y] == 0 || map_bot[attack_x][attack_y] == 2 ) && map_bot_for_show[attack_x][attack_y] == '-') {
                map_bot_for_show[attack_x][attack_y] = 'W';
                printf("Oops! The shooting went wrong!!!\n");
                printmap(map_bot_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
                break;
            }
            else if (map_bot[attack_x][attack_y] == 1 && map_bot_for_show[attack_x][attack_y] == '-'){
                printf("KABOOM!!! YOU HIT BOT Ship\n");
                map_bot_for_show[attack_x][attack_y] = 'E';
                map_bot[attack_x][attack_y] = -1;

                for (Ships * temp = *bot_ships ; temp != NULL ; temp=temp->next){
                    if(is_ship_distroyed(map_bot_for_show,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state)) {
                        update_showmap(map_bot_for_show,temp->state,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e);
                        delete_ship(bot_ships,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state,temp->size);
                        temp_score += complete_explode_score(temp->size);
                    }
                }
                printmap(map_bot_for_show);
                temp_score++;
                printf("\nPress Enter To Continue\n");
                getchar();
                getchar();
                system("cls");
                //check_ships(*bot_ships,map_bot_for_show,map_bot,temp_score);
            }
            else if (map_bot_for_show[attack_x][attack_y] != '-'){
                printf("You Can't HIT This Place\nPress Enter To Try Again\n");
                getchar();getchar();
                system("cls");
            }

        }
        while (1){
            srand(time(0));
            attack_x = rand() % 10;
            attack_y = rand() % 10;
            if ((map_player[attack_x][attack_y] == 0 || map_player[attack_x][attack_y] == 2 ) && map_player_for_show[attack_x][attack_y] == '-'){
                map_player_for_show[attack_x][attack_y] = 'W';
                printf("BOT SHOOT WRONG\n");
                printmap(map_player_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");

                break;
            }
            else if (map_player[attack_x][attack_y] == 1 && map_player_for_show[attack_x][attack_y] == '-') {
                printf("BOT HITS YOU Ship\n");
                map_player_for_show[attack_x][attack_y] = 'E';
                map_player[attack_x][attack_y] = -1;
                for (Ships * temp = *player_ships ; temp!=NULL ; temp = temp->next){
                    if(is_ship_distroyed(map_player_for_show,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state)) {
                        update_showmap(map_player_for_show,temp->state,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e);
                        delete_ship(player_ships,temp->cord_x_b,temp->cord_x_e,temp->cord_y_b,temp->cord_y_e,temp->state,temp->size);
                    }
                }
                printmap(map_player_for_show);
                printf("\nPress Enter To Continue\n");
                getchar();getchar();
                system("cls");
//          check_ships_for_bot_shoots(*player_ships,map_player_for_show,map_player);
            }
            else if (map_player_for_show[attack_x][attack_y] != '-'){
                continue;
            }

        }
    }
}
