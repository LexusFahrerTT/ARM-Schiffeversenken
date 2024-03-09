/**
 * @file startscreen.h
 * @brief Header-Datei für den Startscreen
 */

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <stdint.h>

/**
 * @brief Methode, die das Spiel starte, wenn man S oder s eingibt
 * @param read_char ist das eingelesene vom SPieler
 * 
 */
// Deklaration der Funktion start_screen
void start_screen(uint8_t read_char);
void draw_start_screen();
#endif /* STARTSCREEN_H */