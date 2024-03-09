/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 * @author Sven Reis
 *
 * @brief *Main* Entry
 **/


#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"


#include "utils.h"
#include "maingame.h"
#include "startscreen.h"
#include "endscreen.h"
#include "game.h"

int main( void )
{
  uart_init();
  rng_init();
  
  // 5 seconds
  //timer_init_detailed(28, 30, 19730);

  // 4 seconds
  //timer_init_detailed(28, 30, 15730);

  // 3 seconds
  //timer_init_detailed(28, 30, 11730);

  // 2 seconds
  //timer_init_detailed(28, 30, 7730);

  // 1 second
  //timer_init_detailed(28, 30, 3730);

  // range is between 16.000


  //draw start screen
  for(;;){
    uint8_t read_char = uart_readByte();

    if(game_mode == 0){
      start_screen(read_char);
    }
    else if(game_mode == 1){
      main_game(read_char);      
    }
    else if(game_mode == 2){
      clear_screen();
      end_screen(read_char);
    }
    else if(game_mode == 3){
      clear_screen();
      end_screen(read_char);
    }
  }

  return 0;
}
