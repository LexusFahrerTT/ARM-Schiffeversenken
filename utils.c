/**
 * @file utils.c
 * @brief Source-Datei für Utils methoden, werden benötigt in jedem Szenario (Start, Game, End)
 */

#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"


/**
 * @brief Methode, die die modulo funktionalität stimuliert
 * @param zaehler ist der Anfangswert
 * @param nenner ist der Wert, durchwelchen der Anfangswert diviert bzw "moduliert" wird ;)
 * 
 */
int modulo(int zaehler, int nenner) {
    while (zaehler >= nenner) {
        zaehler -= nenner;
    }
    return zaehler;
}


/**
 * @brief Methode, um den Screen zu clearen
 * 
 */
void clear_screen(void){
  execute_ANSI_or_print_text("\033[2J");
  execute_ANSI_or_print_text("\033[H");
}

/**
 * @brief Methode, ANSI auszuführen oder Zeichenkette auf den Screen zu printen
 * @param esc_code ist der code bzw zeichenkette "String"
 * 
 */
void execute_ANSI_or_print_text(char esc_code[]){
    for(int i = 0; esc_code[i] != '\0'; i++) {
          uart_writeByte(esc_code[i]);
    }
}


/**
 * @brief Methode, um ein Ascii Kunstwert dazustellten
 * @param ascii_art ist der code bzw zeichenkette "String"
 * @param esc_code_move_right ist der Ansi Code, um das Kunstwerk nach RECHTS zu verschieben
 * 
 */
void print_ascii_art(char ascii_art[], char esc_code_move_right[]){
  uart_writeByte('\n');
  execute_ANSI_or_print_text(esc_code_move_right);
  for(int i = 0; ascii_art[i] != '\0'; i++) {
    uart_writeByte(ascii_art[i]);
    if(ascii_art[i] == '\n'){
      execute_ANSI_or_print_text(esc_code_move_right);
    }    
  }
}

/**
 * @brief Methode, um stats array auf den Screen zu printen
 * @param values ist das Array mit den Werten
 * @param column_pos Position, wo sich die werte befinden sollen
 * 
 */
void print_values_array(int values[4], char column_pos[]){
  execute_ANSI_or_print_text(column_pos);
  uart_writeByte(values[0] + 48);
  uart_writeByte(values[1] + 48);
  uart_writeByte(values[2] + 48);
  uart_writeByte(values[3] + 48);
}


/**
 * @brief Methode, um stats auf den Screen zu zeichnen
 * @param statistics_text Einführender Text
 * @param ansi_coordinates Position, wo sich die Stats befinden sollen
 * @param values Werte, die dargestellt werden sollen
 * 
 */
void show_statistics(char statistics_text[], char ansi_coordinates[], int values[4]){
  execute_ANSI_or_print_text(ansi_coordinates);
  execute_ANSI_or_print_text(statistics_text);
  print_values_array(values, "\033[45G");
}


/**
 * @brief Methode, um  ein Stats Array hochzuzählen von den Werten her
 * @param stats_array Stats array, welches hochgezählt wird
 * 
 */
void increment_stats_array(int stats_array[4]){
  stats_array[3] += 1;
    if(stats_array[3] == 10){
      stats_array[3] = 0;
      stats_array[2] += 1;
      if(stats_array[2] == 10){
        stats_array[2] = 0;
        stats_array[1] += 1;
        if(stats_array[1] == 10){
          stats_array[1] = 0;
          stats_array[0] += 1;
        }
      }
    }
}


/**
 * @brief Methode, um  ein Stats Array hzu resetten
 * @param stats_array Stats array, welches resettet wird
 * 
 */
void reset_stats_array(int stats_array[4]){
    stats_array[0] = 0;
    stats_array[1] = 0;
    stats_array[2] = 0;
    stats_array[3] = 0;
}