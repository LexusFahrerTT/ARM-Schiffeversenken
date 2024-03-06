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

char clear_screen[] = "\033[2J";
char set_pos[] = "\033[H";

int enemy_board[10][10]; 
int my_board[10][10];


void setup_board(int board[10][10]){
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j] = 55;
        }
    }
}


void execute_ANSI_esc_codes(char esc_code[]){
    for(int i = 0; esc_code[i] != '\0'; i++) {
          uart_writeByte(esc_code[i]);
    }
}

void write_board_on_screen(int board[][10], int rows, int cols, int player){
  
  //enemy player
  if(player == 0){

    execute_ANSI_esc_codes("\033[3;5H");
    //A-J
    for(int j = 0; j < 10; j++) {
      uart_writeByte(65 + j);
      uart_writeByte(' ');
    }
    uart_writeByte('\n');

    execute_ANSI_esc_codes("\033[2C");
    //execute_ANSI_esc_codes("\033[4;3H");
    
    //print top border
    uart_writeByte(' ');
    for(int i = 0; i < 21; i++){
      uart_writeByte(205);
    }

    uart_writeByte('\n');

    for(int i = 0; i < 10; i++) {
        uart_writeByte(48 + i);
        uart_writeByte(' ');
        uart_writeByte(206);
        uart_writeByte(' ');
        for(int j = 0; j < 10; j++) {
            uart_writeByte(board[i][j]);
            uart_writeByte(' ');
        }
        uart_writeByte(206);
        uart_writeByte('\n');
    }

    execute_ANSI_esc_codes("\033[3C");
    for(int i = 0; i < 21; i++){
      uart_writeByte(205);
    }

  }


}

int main( void )
{
  uart_init();
  rng_init();


  int input_user[2]; 
  int input_counter = 0;

  int enemy_board[10][10]; 
  int my_board[10][10];

  for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            my_board[i][j] = 55;
        }
  }

  //setup_board(my_board);
  //setup_board(enemy_board);


  write_board_on_screen(my_board,1,1, 0);
  execute_ANSI_esc_codes("\033[15;2H");
  //clean_board(my_board);

  for(;;){
    uint8_t read_char = uart_readByte();

    uint8_t value = 48;


    //execute_ANSI_esc_codes(clear_screen);
    //execute_ANSI_esc_codes(set_pos);
    

    /*do
    {
      uint8_t value = rng_getRandomValue_immediately();
    } while (value < 48 && value > 60);
    */

    if(0 != read_char){
      
      //write_board_on_screen(enemy_board, 0);
      
      //do {
      //  value = rng_getRandomValue_immediately();
      //} while (value < 65 || value > 123);

      if(input_counter < 2 && read_char != 127 && read_char != 13){
        uart_writeByte(read_char);
        input_user[input_counter] = read_char - 48;
        input_counter++;
      }
      


      //return
      if(read_char == 127){
          execute_ANSI_esc_codes("\033[15;2H");
          uart_writeByte(' ');
          uart_writeByte(' ');
          execute_ANSI_esc_codes("\033[15;2H");
          input_counter = 0;
      }

      //enter 
      if(read_char == 13){
          if(input_counter >= 2){
            uart_writeByte('s');
            input_counter = 0;
            my_board[input_user[0]][input_user[1]] = 50;

            execute_ANSI_esc_codes(clear_screen);
            execute_ANSI_esc_codes(set_pos);
            write_board_on_screen(my_board,1,1, 0);
            execute_ANSI_esc_codes("\033[15;2H");
          }
      }


      //execute_ANSI_esc_codes(clear_screen);
      //execute_ANSI_esc_codes(set_pos);

      //uart_writeByte(my_board[1][1]);
      //uart_writeByte(my_board[11][11]);
      



      if ((int)read_char == 48){
        
      }
      
      
      
      //uart_writeByte(rng_getRandomValue_immediately());

    }
  }

  return 0;
}
