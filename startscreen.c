#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"
#include "utils.h"
#include "maingame.h"


void start_screen(uint8_t read_char){
  if(0 != read_char && (read_char == 's' || read_char == 'S')){
    game_mode = 1;
    setup_main_game();
    timer_init_detailed(28, 30, 11730);
    draw_screen(&my_board, &enemy_board);
  }
}