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
  
  //show start screen
  draw_start_screen();

  //main game loop
  for(;;){
    uint8_t read_char = uart_readByte();

    if(game_mode == 0){
      start_screen(read_char);
    }
    else if(game_mode == 1){
      main_game(read_char);      
    }
    else if(game_mode == 2){
      end_screen(read_char);
    }
    else if(game_mode == 3){
      end_screen(read_char);
    }
  }

  return 0;
}
