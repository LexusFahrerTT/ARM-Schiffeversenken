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


void clear_screen(void){
  for(int i = 0; i < 2550; i++){
    uart_writeByte("\033[1;31mHallo Welt\033[0m\n");
  }
}


char clear_screeen[] = "\033[2J";
char set_pos[] = "\033[H";


void execute_ANSI_esc_codes(char esc_code[]){
    for(int i = 0; esc_code[i] != '\0'; i++) {
          uart_writeByte(esc_code[i]);
    }
}


int main( void )
{
  uart_init();
  rng_init();

  for(;;){
    uint8_t read_char = uart_readByte();

    uint8_t value = 48;
    /*do
    {
      uint8_t value = rng_getRandomValue_immediately();
    } while (value < 48 && value > 60);
    */

    if(0 != read_char){

      //do {
      //  value = rng_getRandomValue_immediately();
      //} while (value < 65 || value > 123);

      //uart_writeByte(test);

      execute_ANSI_esc_codes(clear_screeen);
      execute_ANSI_esc_codes(set_pos);

      uart_writeByte(read_char);
      uart_writeByte(read_char);
      uart_writeByte(read_char);
      if ((int)read_char == 48){
        clear_screen();
      }
      
      
      
      //uart_writeByte(rng_getRandomValue_immediately());

    }
  }

  return 0;
}
