/**
 * @file endscreen.c
 * @brief Source-Datei für den Endscreen
 */

#include <stdint.h>
#include "maingame.h"


/**
 * @brief startet das spiel erneut, falls r oder R eingegeben worden ist
 * 
 * 
 * @param read_char ist der eingegebene Character des Spielers
 */
void end_screen(uint8_t read_char){
  if(0 != read_char && (read_char == 'r' || read_char == 'R')){
    game_mode = 1;
    setup_main_game();
    timer_init_detailed(28, 30, 11730);
    draw_screen(&my_board, &enemy_board);
  }
}
