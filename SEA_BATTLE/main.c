#include "header.h"

int myField[SIZE+1][SIZE+1], botField[SIZE+1][SIZE+1];
int game_state = INITIALIZATION;

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



