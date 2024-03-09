#ifndef MAINGAME_H
#define MAINGAME_H

#include <stdint.h>

extern int game_mode;

void setup_board(int* board[10][10]);
void setup_main_game();
void placeShip(int* board[10][10]);

#endif /* MAINGAME_H */