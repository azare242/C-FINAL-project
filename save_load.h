void add_pvp_save_to_list(char name[20])
{
    FILE * saves ;
    fopen_s(&saves,"PVP_SAVES.txt","a");
    fprintf(saves,"%s\n",name);
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
    fprintf(saves,"%s\n",name);
    fclose(saves);
}
void save_usernames(char savename[20],char name1[20],char name2[20])
{
    FILE * savegame;
    char temp[20];
    strcpy(temp,savename);
    strncat(temp,"USERNAMES",10);
    fopen_s(&savegame,temp,"w");
    fprintf(savegame,"%s %s",name1,name2);
    fclose(savegame);
}
void load_show_map(char matrix[map_rows][map_columns],FILE * f) {
    for (int i = 0; i < map_rows; i++) {
        fscanf(f,"%c %c %c %c %c %c %c %c %c %c\n",&matrix[i][0],&matrix[i][1],&matrix[i][2],&matrix[i][3],&matrix[i][4],&matrix[i][5],&matrix[i][6],&matrix[i][7],&matrix[i][8],&matrix[i][9]);
    }
}
void load_map(int matrix[map_rows][map_columns],FILE * f) {
    for (int i = 0; i < map_rows; i++) {
        fscanf(f,"%d %d %d %d %d %d %d %d %d %d\n",&matrix[i][0],&matrix[i][1],&matrix[i][2],&matrix[i][3],&matrix[i][4],&matrix[i][5],&matrix[i][6],&matrix[i][7],&matrix[i][8],&matrix[i][9]);
    }
}
Ships * loadnextship(Ships * head, FILE * file)
{
    int value;
    if (head == NULL){
        head = malloc(sizeof(Ships));
        value = fread(head, sizeof(Ships), 1 ,file);
        head->next = NULL;
    } else{
        Ships * temp = head;
        Ships * newuser = malloc(sizeof(Ships));
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        value = fread(newuser, sizeof(Ships),1,file);
        temp->next = newuser;
        newuser->next = NULL;
    }
    return head;
}
void deleteships(Ships ** head)
{
    Ships * cur = *head;
    Ships * next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}
Ships * loadships(Ships * head,char filename[20]) {
    FILE *file;
    fopen_s(&file,filename, "rb");
    if (file != NULL) {
        deleteships(&head);
        head = NULL;
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        int entries = (int) (size / (sizeof(Ships)));
        int i = 0;
        for ( i = 0; i < entries; i++) {
            fseek(file, sizeof(Ships) * i,SEEK_SET);
            head = loadnextship(head, file);
        }
    } else {
        printf("CAN'T LOAD DATA\n");
    }
    fclose(file);
    return head;
}
void read_usernames(char savename[20],char username1[20],char username2[20])
{
    FILE * list;
    char temp[20];
    strcpy(temp,savename);
    strncat(temp,"USERNAMES",10);
    fopen_s(&list,temp,"r");
    fscanf(list,"%s\n",username1);
    fscanf(list,"%s\n",username2);
    fclose(list);
}
void loadgame(char savename[20])
{
    FILE * load1,*load2,*load3,*load4;
    char temp[20];
    int map_player1[map_rows][map_columns] , map_player2[map_rows][map_columns];
    char mapshow_player1[map_rows][map_columns],mapshow_player2[map_rows][map_columns];
    Ships * player1_ships = NULL , * player2_ships = NULL;
    strcpy(temp,savename);
    strncat(temp,"MP1",4);
    fopen_s(&load1, temp , "r");
    load_map(map_player1,load1);
    fclose(load1);
    strcpy(temp,savename);
    strncat(temp,"MP2",4);
    fopen_s(&load2,temp,"r");
    load_map(map_player2,load2);
    fclose(load2);
    strcpy(temp,savename);
    strncat(temp,"MPS1",5);
    fopen_s(&load3,temp,"r");
    load_show_map(mapshow_player1,load3);
    fclose(load3);
    strcpy(temp,savename);
    strncat(temp,"MPS2",5);
    fopen_s(&load4,temp,"r");
    load_show_map(mapshow_player2,load4);
    fclose(load4);
    strcpy(temp,savename);
    User * player1 = (User *)malloc(sizeof(User)),*player2 = (User *)malloc(sizeof(User));
    read_usernames(temp,player1->username,player2->username);
    strcpy(temp,savename);
    strncat(temp,player1->username,strlen(player1->username) + 1);
    player1_ships = loadships(player1_ships,temp);
    strcpy(temp,savename);
    strncat(temp,player2->username,strlen(player2->username) + 1);
    player2_ships = loadships(player2_ships,temp);

}
void load_last_gmae_fucntion_a(){
    FILE * open;
    fopen_s(&open,"LAST_GAME","r");
    char buffer[20],temp1[1],temp2[2];
    fgets(buffer,20,open);
    strcpy(temp1,strtok(buffer,","));
    strcpy(temp2,strtok(NULL,","));
    if (strcmp(temp1,"1") == 0) {

    }
    else if (strcmp(temp1,"2") == 0){

    }

}
void load_last_game_function_b(){

}
