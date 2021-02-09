typedef struct users{
    char username[10];
    int score;
    struct users * next;
}User;
const int map_rows = 10;
const int map_columns = 10;
typedef struct ships{
    int cord_x_b;
    int cord_x_e;
    int cord_y_b;
    int cord_y_e;
    int size;
    int state;
    struct ships * next;
}Ships;
bool isnotshiphere(int xb,int xe,int yb,int ye,int state ,int map[map_rows][map_columns]) {
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
void newship(Ships ** head, int xb,int yb,int xe,int ye,int size,int state) {
    Ships * new = (Ships *)malloc(sizeof(Ships));
    new->cord_x_b = xb;
    new->cord_x_e = xe;
    new->cord_y_b = yb;
    new->cord_y_e = ye;
    new->size = size;
    new->state = state;
    new->next = NULL;
    if (*head == NULL) *head = new;
    else {
        Ships * lastship = *head;
        while (lastship->next != NULL) lastship = lastship->next;
        lastship->next = new;
    }
}
void setshipsonmap(int xb,int xe,int yb,int ye,int state,int map[map_rows][map_columns])
{
    if (state == 1) {
        if (xb != 0 && xb != 9) {
            for (int i = yb; i < ye + 1; i++) {
                map[xb][i] = 1;
                map[xb + 1][i] = 2;
                map[xb - 1][i] = 2;
            }
            if (yb != 0 && ye != 9) {
                map[xb - 1][yb - 1] = 2;
                map[xb][yb - 1] = 2;
                map[xb + 1][yb - 1] = 2;
                map[xe + 1][ye + 1] = 2;
                map[xe][ye + 1] = 2;
                map[xe - 1][ye + 1] = 2;
            } else if (yb == 0 && ye != 9) {
                map[xe][ye + 1] = 2;
                map[xe + 1][ye + 1] = 2;
                map[xe - 1][ye + 1] = 2;
            }
            else if (yb != 0 && ye == 9){
                map[xb][yb - 1] = 2;
                map[xb + 1][yb - 1] = 2;
                map[xb - 1][yb - 1] = 2;
            }
        }

        else if (xb == 0 || xb == 9){
            for (int i = yb ; i < ye+1 ; i++){
                map[xb][i] = 1;
                if (xb == 0 ) {
                    map[xb+1][i] = 2;
                }
                else if (xe == 9){
                    map[xb-1][i] = 2;
                }
                if (ye == 9 && yb != 0){
                    map[xb][yb - 1]= 2;
                    map[xb+1][yb -1] = 2;
                }
                if (xb == 0 && ye != 9 && yb == 0 && xe != 9 ){
                    map[xb][ye + 1] = 2;
                    map[xb+1][ye+1] = 2;
                }

                if (xb == 0 && ye != 9 && yb != 0 && xe != 9) {
                    map[xb][ye + 1] = 2;
                    map[xb + 1][ye + 1] = 2;
                    map[xb][yb - 1] = 2;
                    map[xb+1][yb - 1] = 2;
                }
                if (xe == 9 && ye != 9 && yb != 0 && xb != 0) {
                    map[xe - 1][ye + 1] = 2;
                    map[xe][ye + 1] = 2;
                    map[xb][yb - 1] = 2;
                    map[xb -1][yb - 1 ] = 2;
                }
                if (xe == 9 && ye != 9 && yb == 0 && xb != 0){
                    map[xe - 1][ye + 1] = 2;
                    map[xe][ye + 1] = 2;
                }
                if (xe == 9 && ye == 9 && yb != 0 && xb != 0){
                    map[xb - 1][yb - 1] = 2;
                }
            }
        }
    }
    else if (state == 2){
        if (yb != 0 && yb != 9) {
            for (int i = xb; i < xe + 1; i++) {
                map[i][yb] = 1;
                map[i][yb + 1] = 2;
                map[i][yb - 1] = 2;
            }
            if (xb != 0 && xe != 0) {
                map[xb - 1][yb - 1] = 2;
                map[xb - 1][yb + 1] = 2;
                map[xb - 1][yb] = 2;
                map[xe + 1][ye] = 2;
                map[xe + 1][ye + 1] = 2;
                map[xe + 1][ye - 1] = 2;
            }
            else if (xb == 0 && xe != 0){
                map[xe+1][ye] = 2;
                map[xe+1][ye-1] = 2;
                map[xe+1][ye+1] = 2;

            }
            else if (xb != 0 && xe == 0){
                map[xb - 1][yb] = 2;
                map[xb - 1][yb -1] = 2;
                map[xb - 1][yb + 1] = 2;
            }
        }
        else if (yb == 0 || yb == 9){
            for (int i = xb; i < xe+1 ; ++i) {
                map[i][yb] = 1;

                if (yb == 0){
                    map[i][yb+1] = 2;
                }
                else if (yb == 9){
                    map[i][yb - 1] = 2;
                }
                if (xb == 0 && xe != 9 && yb == 0 ){
                    map[xe+1][yb] = 2;
                    map[xe+1][yb+1] = 2;
                }
                if (xb != 0 && xe == 9 && ye != 9 && yb != 0){
                    map[xb-1][ye] = 2;
                    map[xb - 1 ][ye + 1] = 2;
                }
                if (xb == 0 && xe != 9 && yb == 9){
                    map[xe+1][ye] = 2;
                    map[xe+1][ye - 1] = 2;
                }
                if (xb != 0 && xe == 9 && yb == 9 ){
                    map[xb -1][yb] = 2;
                    map[xb-1][yb - 1] = 2;
                }
                if (xe != 9 && xb != 0 && yb == 0 && ye != 9 ){
                    map[xb -1][yb] = 2;
                    map[xb - 1][yb + 1] = 2;
                    map[xe + 1][yb] = 2;
                    map[xe + 1 ][yb + 1] = 2;
                }
                if(xe != 9 && xb != 0 && yb != 0 && ye == 9){
                    map[xb - 1][ye] = 2;
                    map[xb - 1][ye -1 ] = 2;
                    map[xe + 1][ye] = 2;
                    map[xe + 1][ye - 1] = 2;
                }
                if (xe == 9 && xb != 0 && yb == 0 && ye != 9){
                    map[xb - 1][yb] = 2;
                    map[xb - 1][yb + 1] = 2;
                }
            }
        }
    }
}
void update_showmap(char showmap[map_rows][map_columns],Ships * ship)
{
    int xb = ship->cord_x_b , xe = ship->cord_x_e , yb = ship->cord_y_b , ye = ship->cord_y_e , state = ship->state;

    if (state == 1) {
        if (xb != 0 && xb != 9) {
            for (int i = yb; i < ye + 1; i++) {
                showmap[xb][i] = 'C';
                showmap[xb + 1][i] = 'W';
                showmap[xb - 1][i] = 'W';
            }
            if (yb != 0 && ye != 9) {
                showmap[xb - 1][yb - 1] = 'W';
                showmap[xb][yb - 1] = 'W';
                showmap[xb + 1][yb - 1] = 'W';
                showmap[xe + 1][ye + 1] = 'W';
                showmap[xe][ye + 1] = 'W';
                showmap[xe - 1][ye + 1] = 'W';
            } else if (yb == 0 && ye != 9) {
                showmap[xe][ye + 1] = 'W';
                showmap[xe + 1][ye + 1] = 'W';
                showmap[xe - 1][ye + 1] = 'W';
            }
            else if (yb != 0 && ye == 9){
                showmap[xb][yb - 1] = 'W';
                showmap[xb + 1][yb - 1] = 'W';
                showmap[xb - 1][yb - 1] = 'W';
            }
        }

        else if (xb == 0 || xb == 9){
            for (int i = yb ; i < ye+1 ; i++){
                showmap[xb][i] = 'C';
                if (xb == 0 ) {
                    showmap[xb+1][i] = 'W';
                }
                else if (xe == 9){
                    showmap[xb-1][i] = 'W';
                }
                if (ye == 9 && yb != 0){
                    showmap[xb][yb - 1]= 'W';
                    showmap[xb+1][yb -1] = 'W';
                }
                if (xb == 0 && ye != 9 && yb == 0 && xe != 9 ){
                    showmap[xb][ye + 1] = 'W';
                    showmap[xb+1][ye+1] = 'W';
                }

                if (xb == 0 && ye != 9 && yb != 0 && xe != 9) {
                    showmap[xb][ye + 1] = 'W';
                    showmap[xb + 1][ye + 1] = 'W';
                    showmap[xb][yb - 1] = 'W';
                    showmap[xb+1][yb - 1] = 'W';
                }
                if (xe == 9 && ye != 9 && yb != 0 && xb != 0) {
                    showmap[xe - 1][ye + 1] = 'W';
                    showmap[xe][ye + 1] = 'W';
                    showmap[xb][yb - 1] = 'W';
                    showmap[xb -1][yb - 1 ] = 'W';
                }
                if (xe == 9 && ye != 9 && yb == 0 && xb != 0){
                    showmap[xe - 1][ye + 1] = 'W';
                    showmap[xe][ye + 1] = 'W';
                }
                if (xe == 9 && ye == 9 && yb != 0 && xb != 0){
                    showmap[xb - 1][yb - 1] = 'W';
                }
            }
        }
    }
    else if (state == 2){
        if (yb != 0 && yb != 9) {
            for (int i = xb; i < xe + 1; i++) {
                showmap[i][yb] = 'C';
                showmap[i][yb + 1] = 'W';
                showmap[i][yb - 1] = 'W';
            }
            if (xb != 0 && xe != 0) {
                showmap[xb - 1][yb - 1] = 'W';
                showmap[xb - 1][yb + 1] = 'W';
                showmap[xb - 1][yb] = 'W';
                showmap[xe + 1][ye] = 'W';
                showmap[xe + 1][ye + 1] = 'W';
                showmap[xe + 1][ye - 1] = 'W';
            }
            else if (xb == 0 && xe != 0){
                showmap[xe+1][ye] = 'W';
                showmap[xe+1][ye-1] = 'W';
                showmap[xe+1][ye+1] = 'W';

            }
            else if (xb != 0 && xe == 0){
                showmap[xb - 1][yb] = 'W';
                showmap[xb - 1][yb -1] = 'W';
                showmap[xb - 1][yb + 1] = 'W';
            }
        }
        else if (yb == 0 || yb == 9){
            for (int i = xb; i < xe+1 ; ++i) {
                showmap[i][yb] = 'C';

                if (yb == 0){
                    showmap[i][yb+1] = 'W';
                }
                else if (yb == 9){
                    showmap[i][yb - 1] = 'W';
                }
                if (xb == 0 && xe != 9 && yb == 0 ){
                    showmap[xe+1][yb] = 'W';
                    showmap[xe+1][yb+1] = 'W';
                }
                if (xb != 0 && xe == 9 && ye != 9 && yb != 0){
                    showmap[xb-1][ye] = 'W';
                    showmap[xb - 1 ][ye + 1] = 'W';
                }
                if (xb == 0 && xe != 9 && yb == 9){
                    showmap[xe+1][ye] = 'W';
                    showmap[xe+1][ye - 1] = 'W';
                }
                if (xb != 0 && xe == 9 && yb == 9 ){
                    showmap[xb -1][yb] = 'W';
                    showmap[xb-1][yb - 1] = 'W';
                }
                if (xe != 9 && xb != 0 && yb == 0 && ye != 9 ){
                    showmap[xb -1][yb] = 'W';
                    showmap[xb - 1][yb + 1] = 'W';
                    showmap[xe + 1][yb] = 'W';
                    showmap[xe + 1 ][yb + 1] = 'W';
                }
                if(xe != 9 && xb != 0 && yb != 0 && ye == 9){
                    showmap[xb - 1][ye] = 'W';
                    showmap[xb - 1][ye -1 ] = 'W';
                    showmap[xe + 1][ye] = 'W';
                    showmap[xe + 1][ye - 1] = 'W';
                }
                if (xe == 9 && xb != 0 && yb == 0 && ye != 9){
                    showmap[xb - 1][yb] = 'W';
                    showmap[xb - 1][yb + 1] = 'W';
                }
            }
        }
    }
}
void update_playermap(int map[map_rows][map_columns],Ships * ship)
{
    int xb = ship->cord_x_b , xe = ship->cord_x_e , yb = ship->cord_y_b , ye = ship->cord_y_e , state = ship->state;
    if (state == 1) {
        if (xb != 0 && xb != 9) {
            for (int i = yb; i < ye + 1; i++) {
                map[xb][i] = -1;
                map[xb + 1][i] = 2;
                map[xb - 1][i] = 2;
            }
            if (yb != 0 && ye != 9) {
                map[xb - 1][yb - 1] = 2;
                map[xb][yb - 1] = 2;
                map[xb + 1][yb - 1] = 2;
                map[xe + 1][ye + 1] = 2;
                map[xe][ye + 1] = 2;
                map[xe - 1][ye + 1] = 2;
            } else if (yb == 0 && ye != 9) {
                map[xe][ye + 1] = 2;
                map[xe + 1][ye + 1] = 2;
                map[xe - 1][ye + 1] = 2;
            }
            else if (yb != 0 && ye == 9){
                map[xb][yb - 1] = 2;
                map[xb + 1][yb - 1] = 2;
                map[xb - 1][yb - 1] = 2;
            }
        }

        else if (xb == 0 || xb == 9){
            for (int i = yb ; i < ye+1 ; i++){
                map[xb][i] = -1;
                if (xb == 0 ) {
                    map[xb+1][i] = 2;
                }
                else if (xe == 9){
                    map[xb-1][i] = 2;
                }
                if (ye == 9 && yb != 0){
                    map[xb][yb - 1]= 2;
                    map[xb+1][yb -1] = 2;
                }
                if (xb == 0 && ye != 9 && yb == 0 && xe != 9 ){
                    map[xb][ye + 1] = 2;
                    map[xb+1][ye+1] = 2;
                }

                if (xb == 0 && ye != 9 && yb != 0 && xe != 9) {
                    map[xb][ye + 1] = 2;
                    map[xb + 1][ye + 1] = 2;
                    map[xb][yb - 1] = 2;
                    map[xb+1][yb - 1] = 2;
                }
                if (xe == 9 && ye != 9 && yb != 0 && xb != 0) {
                    map[xe - 1][ye + 1] = 2;
                    map[xe][ye + 1] = 2;
                    map[xb][yb - 1] = 2;
                    map[xb -1][yb - 1 ] = 2;
                }
                if (xe == 9 && ye != 9 && yb == 0 && xb != 0){
                    map[xe - 1][ye + 1] = 2;
                    map[xe][ye + 1] = 2;
                }
                if (xe == 9 && ye == 9 && yb != 0 && xb != 0){
                    map[xb - 1][yb - 1] = 2;
                }
            }
        }
    }
    else if (state == 2){
        if (yb != 0 && yb != 9) {
            for (int i = xb; i < xe + 1; i++) {
                map[i][yb] = -1;
                map[i][yb + 1] = 2;
                map[i][yb - 1] = 2;
            }
            if (xb != 0 && xe != 0) {
                map[xb - 1][yb - 1] = 2;
                map[xb - 1][yb + 1] = 2;
                map[xb - 1][yb] = 2;
                map[xe + 1][ye] = 2;
                map[xe + 1][ye + 1] = 2;
                map[xe + 1][ye - 1] = 2;
            }
            else if (xb == 0 && xe != 0){
                map[xe+1][ye] = 2;
                map[xe+1][ye-1] = 2;
                map[xe+1][ye+1] = 2;

            }
            else if (xb != 0 && xe == 0){
                map[xb - 1][yb] = 2;
                map[xb - 1][yb -1] = 2;
                map[xb - 1][yb + 1] = 2;
            }
        }
        else if (yb == 0 || yb == 9){
            for (int i = xb; i < xe+1 ; ++i) {
                map[i][yb] = -1;

                if (yb == 0){
                    map[i][yb+1] = 2;
                }
                else if (yb == 9){
                    map[i][yb - 1] = 2;
                }
                if (xb == 0 && xe != 9 && yb == 0 ){
                    map[xe+1][yb] = 2;
                    map[xe+1][yb+1] = 2;
                }
                if (xb != 0 && xe == 9 && ye != 9 && yb != 0){
                    map[xb-1][ye] = 2;
                    map[xb - 1 ][ye + 1] = 2;
                }
                if (xb == 0 && xe != 9 && yb == 9){
                    map[xe+1][ye] = 2;
                    map[xe+1][ye - 1] = 2;
                }
                if (xb != 0 && xe == 9 && yb == 9 ){
                    map[xb -1][yb] = 2;
                    map[xb-1][yb - 1] = 2;
                }
                if (xe != 9 && xb != 0 && yb == 0 && ye != 9 ){
                    map[xb -1][yb] = 2;
                    map[xb - 1][yb + 1] = 2;
                    map[xe + 1][yb] = 2;
                    map[xe + 1 ][yb + 1] = 2;
                }
                if(xe != 9 && xb != 0 && yb != 0 && ye == 9){
                    map[xb - 1][ye] = 2;
                    map[xb - 1][ye -1 ] = 2;
                    map[xe + 1][ye] = 2;
                    map[xe + 1][ye - 1] = 2;
                }
                if (xe == 9 && xb != 0 && yb == 0 && ye != 9){
                    map[xb - 1][yb] = 2;
                    map[xb - 1][yb + 1] = 2;
                }
            }
        }
    }
}
