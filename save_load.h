void add_pvp_save_to_list(char name[20])
{
    FILE * saves ;
    fopen_s(&saves,"PVP_SAVES.txt","a");
    fprintf(saves,"\n%s",name);
    fclose(saves);
}
void write_showmap_to_file(FILE * f,char map[map_rows][map_columns])
{
    for (int i = 0 ; i < map_rows ; i++)
    {
        for (int j = 0 ; j < map_columns ; j++){
            fprintf(f,"%c",map[i][j]);
            if (j < 9) fprintf(f," ");
        }
        fprintf(f,"\n");
    }
}
void write_map_to_file(FILE * f, int map[map_rows][map_columns])
{
    for (int i = 0 ; i < map_rows ; i++)
    {
        for (int j = 0 ; j < map_columns ; j++)
        {
            fprintf(f,"%d",map[i][j]);
            if(j < 9 ) fprintf(f," ");
        }
        fprintf(f,"\n");
    }
}

void save_maps_game(char name[20],char showmap_player1[map_rows][map_columns],int map_player1[map_rows][map_columns], char showmap_player2[map_rows][map_columns],int map_player2[map_rows][map_columns])
{
    char temp[20];
    strcpy(temp,name);
    FILE * save_map_player1;
    strncat(temp,"MP1",4);
    fopen_s(&save_map_player1,temp,"w");
    write_map_to_file(save_map_player1,map_player1);
    fclose(save_map_player1);
    strcpy(temp,name);
    strncat(temp,"MPS1",5);
    FILE * save_showmap_player1;
    fopen_s(&save_showmap_player1,temp,"w");
    write_showmap_to_file(save_showmap_player1,showmap_player1);
    fclose(save_showmap_player1);
    strcpy(temp,name);
    FILE * save_map_player2;
    strncat(temp,"MP2",4);
    fopen_s(&save_map_player2,temp,"w");
    write_map_to_file(save_map_player2,map_player2);
    fclose(save_map_player2);
    strcpy(temp,name);
    strncat(temp,"MPS2",5);
    FILE * save_showmap_player2;
    fopen_s(&save_showmap_player2,temp,"w");
    write_showmap_to_file(save_showmap_player2,showmap_player2);
    fclose(save_showmap_player2);
}
void save_ships(Ships * head,char name[20],char username[20])
{
    FILE * save;
    char temp[20];
    strcpy(temp,name);
    strncat(temp,username,(strlen(username) + 1));
    fopen_s(&save,temp,"wb");
    if(save != NULL){
        Ships * cur = head;
        Ships * hold = NULL;
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
void save_scores_pvp(char name[20],int score1, int score2)
{
    FILE * scores;
    char temp[20];
    strcpy(temp,name);
    strncat(temp,"SCORES",7);
    fopen_s(&scores,temp,"a");
    fprintf(scores,"%d %d\n",score1,score2);
    fclose(scores);
}
void save_scores_pvb(char name[20],int score)
{
    FILE * scores;
    char temp[20];
    strcpy(temp,name);
    strncat(temp,"SCORES_PVB",11);
    fopen_s(&scores,temp,"a");
    fprintf(scores,"%d\n",score);
}
void add_pvb_save_to_list(char name[20])
{
    FILE * saves ;
    fopen_s(&saves,"PVB_SAVES.txt","a");
    fprintf(saves,"\n%s",name);
    fclose(saves);
}
