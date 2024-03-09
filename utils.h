#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"

#ifndef UTILS_H
#define UTILS_H

int modulo(int zaehler, int nenner);
void clear_screen(void);
void execute_ANSI_or_print_text(char esc_code[]);
void print_ascii_art(char ascii_art[], char esc_code[]);
void print_values_array(int values[4], char column_pos[]);
void show_statistics(char statistics_text[], char ansi_coordinates[], int values[4]);
void increment_stats_array(int stats_array[4]);
void reset_stats_array(int stats_array[4]);
#endif  // UTILS_H