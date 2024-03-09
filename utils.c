#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"


int modulo(int zaehler, int nenner) {
    while (zaehler >= nenner) {
        zaehler -= nenner;
    }
    return zaehler;
}

void clear_screen(void){
  execute_ANSI_or_print_text("\033[2J");
  execute_ANSI_or_print_text("\033[H");
}

void execute_ANSI_or_print_text(char esc_code[]){
    for(int i = 0; esc_code[i] != '\0'; i++) {
          uart_writeByte(esc_code[i]);
    }
}

void print_ascii_art(char ascii_art[], char esc_code[]){
  uart_writeByte('\n');
  execute_ANSI_or_print_text(esc_code);
  for(int i = 0; ascii_art[i] != '\0'; i++) {
    uart_writeByte(ascii_art[i]);
    if(ascii_art[i] == '\n'){
      execute_ANSI_or_print_text(esc_code);
    }    
  }
}

void print_values_array(int values[4], char column_pos[]){
  execute_ANSI_or_print_text(column_pos);
  uart_writeByte(values[0] + 48);
  uart_writeByte(values[1] + 48);
  uart_writeByte(values[2] + 48);
  uart_writeByte(values[3] + 48);
}

void show_statistics(char statistics_text[], char ansi_coordinates[], int values[4]){
  execute_ANSI_or_print_text(ansi_coordinates);
  execute_ANSI_or_print_text(statistics_text);
  print_values_array(values, "\033[45G");
}

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

void reset_stats_array(int stats_array[4]){
    stats_array[0] = 0;
    stats_array[1] = 0;
    stats_array[2] = 0;
    stats_array[3] = 0;
}