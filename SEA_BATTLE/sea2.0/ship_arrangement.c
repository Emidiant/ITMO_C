#include "header.h"

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

