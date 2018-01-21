
#include "start.h"

char *field[] =
{
    "   ABCDEFGHIJ        ABCDEFGHIJ",
    "   ----------        ----------"
};

char draw_simbol[BOTSHIP+1] =      //обозначения на поле, для просмотра работы программы пустым лучше оставить только empty
{
    ' ', //empty
    '*', // shot
    '!', // strike
    'X', // kill
    ' ', //ambience '.'
    ' ',//bot ambience  '.' //корабли и окружения для бота отдельные, чтобы их можно было заменить на невидимые
    '$',  // ship
    'S' //bot ship 'S'
};

void draw_fields()          //рисуем своё поле и то, куда будем стрелять (поле бота)
{
    printf("%s\n", field[0]);
    printf("%s\n", field[1]);
    for(int i = 1; i <= SIZE; i++)
    {
        if(i != SIZE){
            printf(" %d|", i);
        }
        else {
            printf("%d|", i);
        }
        for(int j = 1; j <= SIZE; j++)
            printf("%c", draw_simbol[myField[i][j]]);   //значения нашего поля
        
        if(i != SIZE){
            printf("|     %d|", i);
        }
        else {
            printf("|    %d|", i);
        }
        for(int j = 1; j <= SIZE; j++)
            printf("%c", draw_simbol[botField[i][j]]);  //значения поля бота, которое мы видим
        printf("|\n");
    }
    printf("%s\n", field[1]);
};

void Ambience_draw(int h, int v, int field)//окружение, чтобы корабли не стояли рядом
{
    if (field == BOT){
        for(int i = -1; i <= 1; i++)
            for(int j = -1; j <= 1; j++)
                botField[h+i][v+j]=BOTAMBIENCE;
    }
    else{
        for(int i = -1; i <= 1; i++)
            for(int j = -1; j <= 1; j++)
                myField[h+i][v+j]=AMBIENCE;
    }
}

void My_shot_draw(int h, int v)
{
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            myField[h+i][v+j] = SHOT;
}

void draw_bot_dead_ship(int h, int v)
{
    botField[h][v]=KILL;
    if (botField[h+1][v] == STRIKE){botField[h+1][v]=KILL; draw_bot_dead_ship(h+1, v);}
    if (botField[h][v+1] == STRIKE){botField[h][v+1]=KILL; draw_bot_dead_ship(h, v+1);}
    if (botField[h-1][v] == STRIKE){botField[h-1][v]=KILL; draw_bot_dead_ship(h-1, v);}
    if (botField[h][v-1] == STRIKE){botField[h][v-1]=KILL; draw_bot_dead_ship(h, v-1);}
}
void h_minus_1_botField(int h, int v)  // вспомогательные функции для прорисовки потопленных кораблей бота
{
    h = h - 1;
    if (h > 1){
        if(bot_dead_deck(h-1,v, BOTSHIP) == TRUE){
            botField[h][v]=KILL;
            draw_bot_dead_ship(h, v);}
    }
    else{
        botField[h][v]=KILL;
        draw_bot_dead_ship(h, v);
    }
}

void h_plus_1_botField(int h, int v)
{
    h = h + 1;
    if (h < 8){
        if(bot_dead_deck(h+1,v, BOTSHIP) == TRUE){
            botField[h][v]=KILL;
            draw_bot_dead_ship(h, v);
        }
    }
    else{
        botField[h][v]=KILL;
        draw_bot_dead_ship(h, v);
    }
}

void v_minus_1_botField(int h, int v)
{
    v = v - 1;
    if (v > 1){
        if (bot_dead_deck(h, v-1, BOTSHIP) == TRUE){
            botField[h][v]=KILL;
            draw_bot_dead_ship(h, v);
        }
    }
    else{botField[h][v]=KILL;
        draw_bot_dead_ship(h, v);
    }
}

void v_plus_1_botField(int h, int v)
{
    v = v + 1;
    if (v < 8){
        if(bot_dead_deck(h, v+1, BOTSHIP) == TRUE){
            botField[h][v]=KILL;
            draw_bot_dead_ship(h, v);}
    }
    else{
        botField[h][v]=KILL;
        draw_bot_dead_ship(h, v);}
}

void search_bot_live_deck(int h, int v)
{
    if (botField[h+1][v] == STRIKE && bot_dead_deck(h+1,v, BOTSHIP) == TRUE){
        h_plus_1_botField(h, v);
        draw_fields();
    }
    if (botField[h-1][v] == STRIKE && bot_dead_deck(h-1,v, BOTSHIP) == TRUE){
        h_minus_1_botField(h, v);
        draw_fields();
    }
    if (botField[h][v+1] == STRIKE && bot_dead_deck(h,v+1, BOTSHIP) == TRUE){
        v_plus_1_botField(h, v);
        draw_fields();
    }
    if (botField[h][v-1] == STRIKE && bot_dead_deck(h,v-1, BOTSHIP) == TRUE){
        v_minus_1_botField(h, v);
        draw_fields();
    }
    
}

int vertical_value (char vert){
    int v;
    if (vert>='A' && vert<='J')
        v= vert - 64;
    if (vert>='a' && vert<='j')
        v= vert - 96;
    return v;
}

int size_ship[num_ship] = {4, 3, 2, 1};

void ship_generate()//запускает функцию отрисовки 2х, 3х и 4х палубных кораблей, затем расставляет однопалубные
{
    void Render_of_ships(int a);
    for(int i = 0; i <num_ship-1; i++)
        Render_of_ships(size_ship[i]);
    printf("Введите четыре координаты для создания однопалубных кораблей\n");//однопалубные задаём отдельно, так как принцип ввода отличен
    printf("Пример: A6, A..J, 1..10,\n");
    int num_coord_1 = 4;
    int Ambience_test(int v, int h);
    int h, v=0; //горизонталь, вертикаль и так по всей программе
    char vert;
    while (num_coord_1 > 0)
    {
        getchar();
        scanf("%c %d", &vert, &h);
        v = vertical_value(vert);
        if (myField[h][v] == EMPTY)
        {
            Ambience_draw(h, v, PLAYER);
            myField[h][v]=SHIP;
            num_coord_1--;
        }
        else
        {
            printf("Здесь корабль располагаться не может, повторите попытку\n");
        }
    }
    for (int i = 0; i <= 11; i++){//за границами видимого поля расставляем shots, чтобы бот туда не стрелял, когда нас добивает
        myField[i][0] = SHOT;
        myField[0][i] = SHOT;
        myField[i][SIZE+1] = SHOT;
        myField[SIZE+1][i] = SHOT;
    }
}
int number_of_ships (int size_sh){//количество кораблей в зависимости от размера
    int num_coord = 0;
    switch (size_sh) {
        case 4:
            num_coord = 1;
            break;
        case 3:
            num_coord = 2;
            break;
        case 2:
            num_coord = 3;
            break;
    }
    return num_coord;
}

void Render_of_ships(int size_sh)
{
    
    int h, v = 0;
    char vert, o;
    int num_coord = number_of_ships(size_sh);
    //задание n палубных кораблей
    if (size_sh == 4){
        printf("Введите координату для создания %dх палубного корабля\n", size_sh);
    }
    else{
        printf("Введите %d координаты для создания %dх палубных кораблей\n", num_coord, size_sh);
    }
    printf("Пример: A6v, a5h, A..J, 1..10, v(h) \n");
    while (num_coord > 0)
    {
        int num_of_free_coord = SET_TO_ZERO;
        //        int flag_do = 0;    //проверка на то, что все координаты, на которые мы хотим поставить корабль, свободны
        if (size_sh == 3 || size_sh == 2){getchar();} //иначе проскакивает
        scanf("%c %d %c", &vert, &h, &o);  //вертикаль, горизонталь, ориентирование корабля
        v = vertical_value(vert);
        if ((v > SIZE-size_sh+1 && o=='h') || (h > SIZE-size_sh+1 && o=='v'))
        {//если мы ставим какой-то корабль (больше, чем однопалубный) так, что он вылезает за границы поля, то всё печально
            printf("Так корабли располагаться не могут, введите ещё раз:\n");
        }
        else
        {
            if (o=='v')//прорисовка вертикального корабля
            {
                for (int p = 0; p < size_sh; p++)
                    if (myField[h+p][v] == EMPTY)
                        num_of_free_coord++;
                if (num_of_free_coord == size_sh){
                    for (int p = 0; p < size_sh; p++)
                    {
                        if (myField[h+p][v] == EMPTY)
                        {
                            Ambience_draw(h+p, v, PLAYER);
                            if (p != size_sh-1){myField[h+p+1][v]=EMPTY;}
                            
                        }
                    }
                    for (int p = 0; p < size_sh; p++)
                        myField[h+p][v]=SHIP;
                    num_coord--;
                }
                else{
                    printf("Так корабли располагаться не могут!\n");
                }
            }
            else//если корабль не вертикальный, то он горизонтальный, рисуем его
            {
                for (int p = 0; p < size_sh; p++)
                    if (myField[h][v+p] == EMPTY)
                        num_of_free_coord++;
                if (num_of_free_coord == size_sh){
                    for (int p = 0; p < size_sh; p++)
                    {
                        if (myField[h][v+p] == EMPTY)
                        {
                            Ambience_draw(h, v+p, PLAYER);
                            if (p != size_sh-1){myField[h][v+p+1]=EMPTY;}
                        }
                    }
                    for (int p = 0; p < size_sh; p++)
                        myField[h][v+p]=SHIP;
                    num_coord--;
                }
                else{
                    printf("Так корабли располагаться не могут\n");
                }
            }
        }
    }
    draw_fields();
}

void bot_ship_generate()
{
    srand(time(NULL));
    char o;
    for(int i = 0; i < num_ship-1; i++)  //задаём 4х, 3х и 2х палубные корабли
    {
        
        int size_sh = size_ship[i];
        int num_coord = number_of_ships(size_sh);
        while (num_coord>0)
        {
            int num_of_free_coord = SET_TO_ZERO; //проверка на то, что все места, на которые хотим разместить корабль, не заняты
            int orient = 1 + rand() % 2;//рандомно выбираем ориентацию корабля
            if (orient == 1){o = 'h';}
            else {o = 'v';}
            int v = 1 + rand() % 10;
            int h = 1 + rand() % 10;
            
            if ((v <= SIZE-size_sh+1 && o == 'h') || (h <= SIZE-size_sh+1 && o == 'v'))//проверяем, чтобы корабль бота не вылез за границы
            {
                if (o == 'v')
                {
                    for (int p = 0; p < size_sh; p++)//р - просто параметр
                        if (botField[h+p][v] == EMPTY)
                            num_of_free_coord++;
                    if (num_of_free_coord == size_sh){
                        for (int p = 0; p < size_sh; p++)
                        {
                            if (botField[h+p][v] == EMPTY)
                            {
                                Ambience_draw(h+p, v, BOT);
                                if (p != size_sh-1){botField[h+p+1][v]=EMPTY;}
                            }
                        }
                        for (int p = 0; p < size_sh; p++)
                            botField[h+p][v]=BOTSHIP;
                        num_coord--;
                    }
                }
                else
                {
                    for (int p = 0; p < size_sh; p++)
                        if (botField[h][v+p] == EMPTY)
                            num_of_free_coord++;
                    if (num_of_free_coord == size_sh){
                        for (int p = 0; p < size_sh; p++)
                        {
                            if (botField[h][v+p] == EMPTY)
                            {
                                Ambience_draw(h, v+p, BOT);
                                if (p != size_sh-1){botField[h][v+p+1]=EMPTY;}
                                
                            }
                        }
                        for (int p = 0; p<size_sh; p++)
                            botField[h][v+p]=BOTSHIP;
                        num_coord--;
                    }
                }
            }
        }
    }
    //генерация однопалубных кораблей
    int num_coord_1 = 4;
    while (num_coord_1 > 0)
    {
        int v = 1 + rand() % 10;
        int h = 1 + rand() % 10;
        if(botField[h][v]==EMPTY){
            Ambience_draw(h, v, BOT);
            botField[h][v]=BOTSHIP;
            num_coord_1--;
        }
    }
}

void my_hit()  // наши выстрелы
{
    getchar();
    char vert;
    int h, v=0;
    if (live_ships(BOT) == TRUE){//проверка на наличие кораблей у бота
        printf("Введите координату, по которой хотите выстрелить:\n");
        scanf("%c %d", &vert, &h);
        v = vertical_value(vert);
        if (botField[h][v] == BOTAMBIENCE || botField[h][v] == EMPTY) {
            botField[h][v]=SHOT;
            printf("Вы промахнулись :(\n");
        }
        if (botField[h][v] == BOTSHIP){
            botField[h][v]=STRIKE;
            draw_fields();
            if (bot_dead_deck(h, v, BOTSHIP) == TRUE){
                if(bot_dead_deck(h, v, STRIKE) == TRUE && bot_dead_deck(h, v, KILL) == TRUE){
                    draw_bot_dead_ship(h,v);     //прорисовка умершего однопалубного корабля
                    draw_fields();
                    printf("Вы потопили корабль\n");
                }
                search_bot_live_deck(h, v);
            }
            else{
                printf("Вы попали!\n");
            }
            my_hit();
        }
    }
}


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
    int coord = 0;
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

int live_ships(int name)  //проверка на наличие плавающих кораблей на поле
{
    int n_ship = 0;
    int status = TRUE;
    switch (name) {
        case PLAYER:
            for(int i = 1; i <= SIZE; i++)
                for (int j = 1; j <= SIZE; j++)
                    if (myField[i][j] == SHIP)
                        n_ship++;
            if (n_ship == 0){
                game_state = EXIT;
                printf("Вы проиграли...\n");
                status = FALSE;
            }
            break;
        case BOT:
            for(int i = 1; i <= SIZE; i++)
                for (int j = 1; j <= SIZE; j++)
                    if (botField[i][j] == BOTSHIP)
                        n_ship++;
            if (n_ship == 0){
                game_state = EXIT;
                status = FALSE;
                printf("Вы выиграли!\n");
            }
            break;
    }
    return status;
}


int bot_dead_deck(int h, int v, int PAR)//проверка на то, есть ли какой-то объект поблизости на поле бота
{
    
    int ship_is_dead = FALSE;
    if (botField[h+1][v] != PAR && botField[h][v+1] != PAR && botField[h-1][v] != PAR && botField[h][v-1] != PAR)
        ship_is_dead = TRUE;
    return ship_is_dead;
}

int my_dead_deck(int h, int v, int PAR)//проверка на то, есть ли какой-то объект поблизости на нашем поле
{
    
    int ship_is_dead = FALSE;
    if (myField[h+1][v] != PAR && myField[h][v+1] != PAR && myField[h-1][v] != PAR && myField[h][v-1] != PAR)
        ship_is_dead = TRUE;
    return ship_is_dead;
}


int main()
{
    int pass = TRUE;
    
    while(pass)
    {
        switch (game_state) {
            case INITIALIZATION:
                ship_generate();
                bot_ship_generate();
                game_state = DRAWING;
                break;
            case DRAWING:
                draw_fields();
                game_state = PROCESSING;
                break;
            case PROCESSING:
                game_state = DRAWING;
                my_hit();
                if (game_state == DRAWING)
                    new_bot_hit();
                break;
            case EXIT:
                pass = FALSE;
                break;
        }
    }
    
    return 0;
}
