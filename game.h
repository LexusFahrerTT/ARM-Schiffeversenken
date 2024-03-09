/**
 * @file game.h
 * @brief Header-Datei für das "komplette"  Spiel bzw. Varaiblen und Methode, die im gesamten SPiel benötigt werden
 */

#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/**
 * @brief game mode, welches aussagt, in welchem State sich das Spiel befindet
 * game mode = 0 | start
 * game mode = 1 | maingame
 * game mode = 2,3 | end
 */
extern int game_mode;

/**
 * @brief Methode, um das Board in einen Anfangszutsandt zu versetzen
 * @param board ist das jeweilige übergebene Board
 * 
 */
void setup_board(int* board[10][10]);

/**
 * @brief Methode, um das Hauptspiel in den Anfangszusatdn zu versetztzen
 * 
 */
void setup_main_game();

/**
 * @brief Methode, um ein Baord mit Schiffen zu versorgen
 * @param board ist das jeweilige übergebene Board
 */
void placeShip(int* board[10][10]);

#endif /* GAME_H */