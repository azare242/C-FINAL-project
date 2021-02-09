#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameloop.h"
int random_number1_2()
{
    srand(time(NULL));
    return ((rand() % 2) + 1);
}
int random_number0_9()
{
    srand(time(NULL));
    return rand() % 10;
}
void bot_give_ships(int map[map_rows][map_columns],Ships * botships,int size)
{
    int xb,xe,yb,ye,state;
    state = random_number1_2();

    if (state == 1){
        while (1){
            xb = random_number0_9();
            if (xb + size > 9) xb -= size ;
            xe = xb;
            yb = random_number0_9();
            if (yb + size > 9) yb -= size;
            ye =  yb + size - 1 ;
            if(xe == xb && ye - yb + 1 == size && ye > yb && isnotshiphere(xb,xe,yb,ye,state,map) && ye < 10 && yb < 9 - size){
                break;
            }
            else continue;
        }
    }
    else if (state == 2) {
        while (1) {
            xb = random_number0_9();
            if (xb + size > 9) xb -= size;
            xe = xb + size - 1;
            yb = random_number0_9();
            if (yb + size > 9) yb -= size;
            ye = yb;
            if (ye == yb && xe - xb + 1 == size && xe > xb && isnotshiphere(xb, xe, yb, ye, state, map) && xe < 10 && xb < 9 - size) {
                break;
            }
            else continue;
        }

    }
    setshipsonmap(xb,xe,yb,ye,state,map);
    newship(&botships,xb,yb,xe,ye,size,state);
    botships = botships->next;
}
void bot_give_ships_size1(int map[map_rows][map_columns],Ships * botships)
{
    int x,y;
    while (1) {
        x = random_number0_9();
        y = random_number0_9();
        if (isnotshiphere(x, x, y, y, 1, map)) break;
        else continue;
    }
    setshipsonmap(x,x,y,y,1,map);
    newship(&botships,x,y,x,y,1,1);
    botships = botships->next;
}
void bot_set_map(int map[map_rows][map_columns],Ships * botships)
{
    printf("Please wait , Bot is Setting MAP\n");
    setshipsonmap(0,0,8,9,1,map);
    newship(&botships,0,8,0,9,1,1);
    setshipsonmap(2,3,9,9,2,map);
    newship(&botships,2,9,3,9,2,2);
    bot_give_ships(map,botships,5);
    bot_give_ships(map,botships,3);
    bot_give_ships(map,botships,3);
    bot_give_ships(map,botships,2);
    bot_give_ships_size1(map,botships);
    bot_give_ships_size1(map,botships);
    bot_give_ships_size1(map,botships);
    bot_give_ships_size1(map,botships);
    //printmap_for_set(map);
    printf("The map of BOT sat\n");
    getchar();
    getchar();
    system("cls");

}