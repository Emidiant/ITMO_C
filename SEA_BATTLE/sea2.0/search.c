#include "header.h"

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

