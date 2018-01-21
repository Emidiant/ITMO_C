#ifndef header_h

#define header_h


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define NLines 13
#define SIZE 10
#define num_ship 4
#define SET_TO_ZERO 0


enum Field_Info
{
    EMPTY,
    SHOT,
    STRIKE,
    KILL,
    AMBIENCE,
    BOTAMBIENCE,
    SHIP,
    BOTSHIP
    
};

enum Game_State
{
    INITIALIZATION,
    DRAWING,
    PROCESSING,
    EXIT
};

enum boolean{
    FALSE,
    TRUE
};

enum route{
    up = 1,
    down,
    right,
    left
};

enum num{
    one = 1,
    two,
    three,
    four
};

enum name{
    BOT,
    PLAYER
};

extern int myField[SIZE+1][SIZE+1], botField[SIZE+1][SIZE+1];
extern int game_state;


void bot_ship_generate(void);
void ship_generate(void);

int live_ships(int name);
int bot_dead_deck(int h, int v, int PAR);
int my_dead_deck(int h, int v, int PAR);
void search_bot_live_deck(int h, int v);

int vertical_value (char vert);

void draw_fields(void);
void Ambience_draw(int h, int v, int field);
void draw_my_dead_ship(int h, int v);
void draw_bot_dead_ship(int h, int v);
void My_shot_draw(int h, int v);


void bot_hit(int h, int v, int num);
void new_bot_hit(void);
void my_hit(void);

#endif

