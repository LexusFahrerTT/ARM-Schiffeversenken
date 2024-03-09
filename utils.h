/**
 * @file utils.h
 * @brief Header-Datei für Utils methoden, werden benötigt in jedem Szenario (Start, Game, End)
 */


#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Methode, die die modulo funktionalität stimuliert
 * @param zaehler ist der Anfangswert
 * @param nenner ist der Wert, durchwelchen der Anfangswert diviert bzw "moduliert" wird ;)
 * 
 */
int modulo(int zaehler, int nenner);

/**
 * @brief Methode, um den Screen zu clearen
 * 
 */
void clear_screen(void);

/**
 * @brief Methode, ANSI auszuführen oder Zeichenkette auf den Screen zu printen
 * @param esc_code ist der code bzw zeichenkette "String"
 * 
 */
void execute_ANSI_or_print_text(char esc_code[]);

/**
 * @brief Methode, um ein Ascii Kunstwert dazustellten
 * @param ascii_art ist der code bzw zeichenkette "String"
 * @param esc_code_move_right ist der Ansi Code, um das Kunstwerk nach RECHTS zu verschieben
 * 
 */
void print_ascii_art(char ascii_art[], char esc_code_move_right[]);

/**
 * @brief Methode, um stats array auf den Screen zu printen
 * @param values ist das Array mit den Werten
 * @param column_pos Position, wo sich die werte befinden sollen
 * 
 */
void print_values_array(int values[4], char column_pos[]);

/**
 * @brief Methode, um stats auf den Screen zu zeichnen
 * @param statistics_text Einführender Text
 * @param ansi_coordinates Position, wo sich die Stats befinden sollen
 * @param values Werte, die dargestellt werden sollen
 * 
 */
void show_statistics(char statistics_text[], char ansi_coordinates[], int values[4]);

/**
 * @brief Methode, um  ein Stats Array hochzuzählen von den Werten her
 * @param stats_array Stats array, welches hochgezählt wird
 * 
 */
void increment_stats_array(int stats_array[4]);

/**
 * @brief Methode, um  ein Stats Array hzu resetten
 * @param stats_array Stats array, welches resettet wird
 * 
 */
void reset_stats_array(int stats_array[4]);
#endif  // UTILS_H