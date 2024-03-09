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


int modulo(int dividend, int divisor) {
    while (dividend >= divisor) {
        dividend -= divisor;
    }
    return dividend;
}
/*
void printBoardDebug(int board[][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            uart_writeByte(board[i][j] + '0'); // Convert integer to character and print
            uart_writeByte(' '); // Add space between elements
        }
        uart_writeByte('\n'); // Move to the next line after printing each row
    }
}
*/
void placeShip(int board[][10]) {
    int ship_sizes[] = {2, 3, 4, 5};
    int num_ships = 0;

    while (num_ships < 4) {
        int length = ship_sizes[num_ships];
        int row, col;
        uint8_t horizontal = rng_getRandomValue_immediately() & 0x01;

        if (horizontal) {
            row = modulo(rng_getRandomValue_immediately(), 10);
            col = modulo(rng_getRandomValue_immediately(), 10 - length + 1);

            int i;
            for (i = col; i < col + length; i++) {
                if (board[row][i] == 1 || (row > 0 && board[row - 1][i] == 1) || (row < 9 && board[row + 1][i] == 1) ||
                    (i > 0 && board[row][i - 1] == 1) || (i < 9 && board[row][i + 1] == 1) ||
                    ((row > 0 && i > 0) && board[row - 1][i - 1] == 1) ||
                    ((row > 0 && i < 9) && board[row - 1][i + 1] == 1) ||
                    ((row < 9 && i > 0) && board[row + 1][i - 1] == 1) ||
                    ((row < 9 && i < 9) && board[row + 1][i + 1] == 1)) {
                    break;
                }
            }
            if (i != col + length) {
                continue;
            }

            for (int i = col; i < col + length; i++) {
                board[row][i] = 1;
            }
        } else {
            row = modulo(rng_getRandomValue_immediately(), 10 - length + 1);
            col = modulo(rng_getRandomValue_immediately(), 10);

            int i;
            for (i = row; i < row + length; i++) {
                if (board[i][col] == 1 || (col > 0 && board[i][col - 1] == 1) || (col < 9 && board[i][col + 1] == 1) ||
                    (i > 0 && board[i - 1][col] == 1) || (i < 9 && board[i + 1][col] == 1) ||
                    ((i > 0 && col > 0) && board[i - 1][col - 1] == 1) ||
                    ((i > 0 && col < 9) && board[i - 1][col + 1] == 1) ||
                    ((i < 9 && col > 0) && board[i + 1][col - 1] == 1) ||
                    ((i < 9 && col < 9) && board[i + 1][col + 1] == 1)) {
                    break;
                }
            }
            if (i != row + length) {
                continue;
            }

            for (int i = row; i < row + length; i++) {
                board[i][col] = 1;
            }
        }
        num_ships++;
    }
}

int main( void )
{
  uart_init();
  rng_init();

  //int board[10][10]; 

  //placeShip(board); 
  //printBoardDebug(board);

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

      uart_writeByte(read_char);
      if ((int)read_char == 10){
        uart_writeByte('s');
        uart_writeByte('\n');
      }
      
      
      
      //uart_writeByte(rng_getRandomValue_immediately());

    }
  }

  return 0;
}
