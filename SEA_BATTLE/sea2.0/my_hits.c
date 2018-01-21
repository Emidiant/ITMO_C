#include "header.h"

void my_hit()  // наши выстрелы
{
    getchar();
    char vert;
    int h, v=0;
    if (live_ships(BOT) == TRUE){//проверка на наличие кораблей у бота
        printf("Введите координату, по которой хотите выстрелить:\n");
        scanf("%c %d", &vert, &h);
        v = vertical_value(vert);
        if(botField[h][v] == STRIKE || botField[h][v] == SHOT || botField[h][v] == KILL){
            printf("Вы уже стреляли по этому полю\n");
            my_hit();
        }
        else{
            if (botField[h][v] == BOTAMBIENCE || botField[h][v] == EMPTY) {
                botField[h][v] = SHOT;
                printf("Вы промахнулись :(\n");
            }
            if (botField[h][v] == BOTSHIP){
                botField[h][v] = STRIKE;
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
}

