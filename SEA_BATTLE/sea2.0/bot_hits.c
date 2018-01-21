#include "header.h"

int coordinate(int h, int v){
    int coord = FALSE;
    if(myField[h][v] != SHOT)
        coord = h * 12 + v;
    return coord;
}

int next_coord_generate(int h, int v)//генерация случайной координаты выбивания второй палубы
{
    srand(time(NULL));
    int hit;
    int coord;
    int flag_do = TRUE;
    while(flag_do){
        hit = up + rand() % left;
        switch (hit) {
            case up:
                if (coordinate(h-1, v) != FALSE){//при помощи coordinate упростилось
                    flag_do = FALSE;
                    coord = coordinate(h-1, v);
                }
                break;
            case down:
                if (coordinate(h+1, v) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(h+1, v);
                }
                break;
            case left:
                if (coordinate(h, v-1) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(h, v-1);
                }
                break;
            case right:
                if (coordinate(h, v+1) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(h, v+1);
                }
                break;
        }
    }
    return coord;
}

int max(int a, int b){
    int max;
    if (a > b){
        max = a;
    }
    else{
        max = b;
    }
    return max;
}

int horizontal_ship(int h, int v, int v1){
    srand(time(NULL));
    int coord = 0, hit;
    int flag_do = TRUE;
    int vert = max(v1, v);
    while(flag_do){
        hit = right + rand() % left;
        switch (hit) {
            case left:
                if (coordinate(h, vert-2) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(h, vert-2);
                }
                break;
            case right:
                if (coordinate(h, vert+1) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(h, vert+1);
                }
                break;
        }
    }
    return coord;
}

int vertical_ship(int h, int v, int h1){
    srand(time(NULL));
    int coord = 0, hit;
    int flag_do = TRUE;
    int hor = max(h1, h);
    while(flag_do){
        hit = up + rand() % down;
        switch (hit) {
            case up:
                if (coordinate(hor-2, v) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(hor-2, v);
                }
                break;
            case down:
                if (coordinate(hor+1, v) != FALSE){
                    flag_do = FALSE;
                    coord = coordinate(hor+1, v);
                }
                break;
        }
    }
    return coord;
}

int third_coord_generate(int h, int v, int hor, int vert){//выбивание третьей палубы
    int coord = 0;
    if (hor == h){
        coord = horizontal_ship(h, v, vert);
    }
    else{
        coord = vertical_ship(h, v, hor);
    }
    return coord;
}


int number_of_ship_decks(int h, int v){//определение количество палуб корабля, в который попал бот
    int num = 0;
    
    if (my_dead_deck(h, v, SHIP) == TRUE)
        num = one;
    else{
        if (myField[h][v+1] == SHIP){
            if(my_dead_deck(h, v+1, SHIP) == TRUE){
                if(myField[h][v-1] != SHIP){
                    num = two;
                }
                else{
                    if(my_dead_deck(h, v-1, SHIP) == TRUE){
                        num = three;
                    }
                    else num = four;
                }
            }
            else{
                myField[h][v+1] = STRIKE;
                if(my_dead_deck(h, v+2, SHIP) == TRUE){
                    if(myField[h][v-1] != SHIP){
                        num = three;
                    }
                    else{
                        num = four;
                    }
                }
                else{
                    num = four;
                }
                myField[h][v+1] = SHIP;
            }
        }
        if (myField[h-1][v] == SHIP){
            if(my_dead_deck(h-1, v, SHIP) == TRUE){
                if(myField[h+1][v] != SHIP){
                    num = two;
                }
                else{
                    if(my_dead_deck(h+1, v, SHIP) == TRUE){
                        num = three;
                    }
                    else num = four;
                }
            }
            else{
                myField[h-1][v] = STRIKE;
                if(my_dead_deck(h-2, v, SHIP) == TRUE){
                    if(myField[h+1][v] != SHIP){
                        num = three;
                    }
                    else{
                        num = four;
                    }
                }
                else{
                    num = four;
                }
                myField[h-1][v] = SHIP;
            }
        }
        if (myField[h+1][v] == SHIP){
            if(my_dead_deck(h+1, v, SHIP) == TRUE){
                if(myField[h-1][v] != SHIP){
                    num = two;
                }
                else{
                    if(my_dead_deck(h-1, v, SHIP) == TRUE){
                        num = three;
                    }
                    else num = four;
                }
            }
            else{
                myField[h+1][v] = STRIKE;
                if(my_dead_deck(h+2, v, SHIP) == TRUE){
                    if(myField[h-1][v] != SHIP){
                        num = three;
                    }
                    else{
                        num = four;
                    }
                }
                else{
                    num = four;
                }
                myField[h+1][v] = SHIP;
            }
        }
        if (myField[h][v-1] == SHIP){
            if(my_dead_deck(h, v-1, SHIP) == TRUE){
                if(myField[h][v+1] != SHIP){
                    num = two;
                }
                else{
                    if(my_dead_deck(h, v+1, SHIP) == TRUE){
                        num = three;
                    }
                    else num = four;
                }
            }
            else{
                myField[h][v-1] = STRIKE;
                if(my_dead_deck(h, v-2, SHIP) == TRUE){
                    if(myField[h][v+1] != SHIP){
                        num = three;
                    }
                    else{
                        num = four;
                    }
                }
                else{
                    num = four;
                }
                myField[h][v-1] = SHIP;
            }
        }
    }
    
    return num;
}


void new_bot_hit()  //бот пытается в нас попасть
{
    int flag = TRUE;
    srand(time(NULL));
    while (flag)
    {
        int v = 1 + rand() % 10;
        int h = 1 + rand() % 10;
        if (myField[h][v] == AMBIENCE || myField[h][v] == EMPTY) {
            myField[h][v]=SHOT;
            printf("Бот промахнулся...\n");
            flag = FALSE;
        }
        if (myField[h][v] == SHIP){
            myField[h][v]=STRIKE;
            printf("Бот попал :(\n");
            bot_hit(h, v, number_of_ship_decks(h, v));
            flag = FALSE;
        }
    }
}

void pass_one_step()
{
    draw_fields();
    printf("Бот промахнулся\n");
    my_hit();
}

void new_step()
{
    draw_fields();
    printf("Бот потопил ваш корабль\n");
    if (live_ships(PLAYER) == FALSE){
        game_state = EXIT;
    }
    else{
        new_bot_hit();
    }
}
int four_hit_coord(int h, int v, int hor, int vert, int hor3, int vert3){//выбивание четвертой палубы
    int coord = 0;
    int hit;
    srand(time(NULL));
    int flag_do = TRUE;
    int vertical[3], horizontal[3];
    int min = SIZE + 1, max = 0;
    if (h == hor){//корабль расположен горизонтально
        vertical[0] = v;
        vertical[1] = vert;
        vertical[2] = vert3;
        for(int i = 0; i <= 2; i++){
            if (vertical[i] > max)
                max = vertical[i];
            if (vertical[i] < min)
                min = vertical[i];
        }
        while (flag_do){
            hit = right + rand() % left;
            switch (hit) {
                case right:
                    if (coordinate(h, max+1) != FALSE){
                        flag_do = FALSE;
                        coord = coordinate(h, max+1);
                    }
                    break;
                case left:
                    if (coordinate(h, min-1) != FALSE){
                        flag_do = FALSE;
                        coord = coordinate(h, min-1);
                    }
                    break;
            }
        }
        
    }
    else{//корабль расположен вертикально
        horizontal[0] = h;
        horizontal[1] = hor;
        horizontal[2] = hor3;
        for(int i = 0; i <= 2; i++){
            if (horizontal[i] > max)
                max = horizontal[i];
            if (horizontal[i] < min)
                min = horizontal[i];
        }
        while (flag_do){
            hit = up + rand() % down;
            switch (hit) {
                case up:
                    if (coordinate(min-1, v) != FALSE){
                        flag_do = FALSE;
                        coord = coordinate(min-1, v);
                    }
                    break;
                case down:
                    if (coordinate(max+1, v) != FALSE){
                        flag_do = FALSE;
                        coord = coordinate(max+1, v);
                    }
                    break;
            }
        }
    }
    return coord;
}
void bot_hit(int h, int v, int num){//в этой функции бот добивает корабль
    int coord_hit = 0;//координата для второй палубы
    int coord3 = 0;//координата для третьей палубы
    int coord4 = 0;//координата для четвертой палубы
    int hor, vert, vert3, hor3, vert4, hor4;//приведение координат к виду (x,y)
    int num_deck = 1;//количество выбитых палуб нашего корабля
    switch (num) {
        case one://однопалубный
            My_shot_draw(h,v);
            myField[h][v]=KILL;
            new_step();
            break;
        case two://двухпалубный
            coord_hit = next_coord_generate(h, v);
            vert = coord_hit % 12;
            hor = (coord_hit - vert)/12;
            if(myField[hor][vert] == SHIP){
                My_shot_draw(h,v);
                My_shot_draw(hor,vert);
                myField[h][v] = KILL;
                myField[hor][vert] = KILL;
                new_step();
            }
            else{
                myField[hor][vert] = SHOT;
                pass_one_step();
                bot_hit(h, v, two);
            }
            break;
        case three:
            while (num_deck == 1){
                coord_hit = next_coord_generate(h, v);
                vert = coord_hit % 12;
                hor = (coord_hit - vert)/12;
                if(myField[hor][vert] == SHIP){
                    myField[hor][vert] = STRIKE;
                    printf("Бот попал\n");
                    num_deck++;
                }
                else{
                    myField[hor][vert] = SHOT;
                    pass_one_step();
                }
            }
            while (num_deck == 2){
                coord3 = third_coord_generate(h, v, hor, vert);
                vert3 = coord3 % 12;
                hor3 = (coord3 - vert3)/12;
                if (myField[hor3][vert3] == SHIP)
                {
                    My_shot_draw(h, v);
                    My_shot_draw(hor, vert);
                    My_shot_draw(hor3, vert3);
                    myField[h][v] = KILL;
                    myField[hor][vert] = KILL;
                    myField[hor3][vert3] = KILL;
                    num_deck++;
                    new_step();
                }
                else{
                    myField[hor3][vert3] = SHOT;
                    pass_one_step();
                }
            }
            break;
        case four:
            while (num_deck == 1){
                coord_hit = next_coord_generate(h, v);
                vert = coord_hit % 12;
                hor = (coord_hit - vert)/12;
                if(myField[hor][vert] == SHIP){
                    myField[hor][vert] = STRIKE;
                    printf("Бот попал\n");
                    num_deck++;
                }
                else{
                    myField[hor][vert] = SHOT;
                    pass_one_step();
                }
            }
            while (num_deck == 2){
                coord3 = third_coord_generate(h, v, hor, vert);
                vert3 = coord3 % 12;
                hor3 = (coord3 - vert3)/12;
                if (myField[hor3][vert3] == SHIP)
                {
                    myField[hor3][vert3] = STRIKE;
                    printf("Бот попал\n");
                    num_deck++;
                }
                else{
                    myField[hor3][vert3] = SHOT;
                    pass_one_step();
                }
            }
            while (num_deck == 3){
                coord4 = four_hit_coord(h, v, hor, vert, hor3, vert3);
                vert4 = coord4 % 12;
                hor4 = (coord4 - vert4)/12;
                if (myField[hor4][vert4] == SHIP)
                {
                    My_shot_draw(h, v);
                    My_shot_draw(hor, vert);
                    My_shot_draw(hor3, vert3);
                    My_shot_draw(hor4, vert4);
                    myField[h][v] = KILL;
                    myField[hor][vert] = KILL;
                    myField[hor3][vert3] = KILL;
                    myField[hor4][vert4] = KILL;
                    num_deck++;
                    new_step();
                }
                else{
                    myField[hor4][vert4] = SHOT;
                    pass_one_step();
                }
            }
            break;
            
    }
}

