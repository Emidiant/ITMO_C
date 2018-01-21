#include "header.h"

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
