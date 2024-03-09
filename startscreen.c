/**
 * @file startscreen.c
 * @brief Source-Datei für den Startscreen
 */

#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"
#include "utils.h"
#include "maingame.h"


/**
 * @brief Methode, die das Spiel starte, wenn man S oder s eingibt
 * @param read_char ist das eingelesene vom SPieler
 * 
 */
void start_screen(uint8_t read_char){
  if(0 != read_char && (read_char == 's' || read_char == 'S')){

    //setup whole game
    setup_main_game();

    //starte timer
    timer_init_detailed(28, 30, 11730);
    game_mode = 1;
    draw_screen(&my_board, &enemy_board);
  }
}