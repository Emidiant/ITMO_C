//
//  start.h
//  sea_battle2.0
//
//  Created by Юлия on 20.01.2018.
//  Copyright © 2018 Юлия. All rights reserved.
//

#ifndef start_h
#define start_h

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define NLines 13
#define SIZE 10
#define num_ship 4
#define SET_TO_ZERO 0

int myField[SIZE+1][SIZE+1], botField[SIZE+1][SIZE+1];

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
    
} Field_Info;

enum Game_State
{
    INITIALIZATION,
    DRAWING,
    PROCESSING,
    EXIT
} Game_State;

enum boolean{
    FALSE,
    TRUE
}boolean;

enum route{
    up = 1,
    down,
    right,
    left
}route;

enum num{
    one = 1,
    two,
    three,
    four
}num;

enum name{
    BOT,
    PLAYER
}name;

int game_state = INITIALIZATION;

void bot_ship_generate(void);
void ship_generate(void);
int live_ships(int name);
int bot_dead_deck(int h, int v, int PAR);
int my_dead_deck(int h, int v, int PAR);
void draw_bot_dead_ship(int h, int v);
void search_bot_live_deck(int h, int v);
int vertical_value (char vert);
void draw_fields(void);
void Ambience_draw(int h, int v, int field);
void new_bot_hit(void);
void draw_my_dead_ship(int h, int v);
void My_shot_draw(int h, int v);
void my_hit(void);
int coordinate(int h, int v);
int next_coord_generate(int h, int v);
int third_coord_generate(int h, int v, int hor, int vert);
int number_of_ship_decks(int h, int v);
void bot_hit(int h, int v, int num);


#endif /* start_h */
