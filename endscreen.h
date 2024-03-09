
/**
 * @file endscreen.h
 * @brief Header-Datei für den Endscreen
 */

#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <stdint.h>

/**
 * @brief startet das spiel erneut, falls r oder R eingegeben worden ist
 * 
 * 
 * @param read_char ist der eingegebene Character des Spielers
 */
void end_screen(uint8_t read_char);

/**
 * @brief Methode, um den Loser End Screen darzustellen
 * 
 * @param player_stats ist ein array mit allen Stats Arrays des Spielers
 * @param bot_stats ist ein array mit allen Stats Arrays des Bots
 */
void draw_you_lost(int* player_stats[3], int* bot_stats[3]);

/**
 * @brief Methode, um den Win End Screen darzustellen
 * 
 * @param player_stats ist ein array mit allen Stats Arrays des Spielers
 * @param bot_stats ist ein array mit allen Stats Arrays des Bots
 */
void draw_you_won(int* player_stats[3], int* bot_stats[3]);

#endif /* ENDSCREEN_H */
