/**
 * @file endscreen.h
 * @brief Header-Datei für den Endscreen
 */

#ifndef MAINGAME_H
#define MAINGAME_H

#include <stdint.h>

/**
 * @brief startet das spiel erneut, falls r oder R eingegeben worden ist
 * 
 * 
 * @param read_char ist der eingegebene Character des Spielers
 */
void end_screen(uint8_t read_char);

#endif /* GAME_H */