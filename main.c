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


char ascii_art_player[] = 
"  ____  _                       \n"
" |  _ \\| | __ _ _   _  ___ _ __ \n"
" | |_) | |/ _` | | | |/ _ \\ '__|\n"
" |  __/| | (_| | |_| |  __/ |   \n"
" |_|   |_|\\__,_|\\__, |\\___|_|   \n"
"                |___/            \n";


char ascii_art_bot[] = 
        "   ____ ____  _   _    ____        _   \n"
        "  / ___|  _ \\| | | |  | __ )  ___ | |_ \n"
        " | |   | |_) | | | |  |  _ \\ / _ \\| __|\n"
        " | |___|  __/| |_| |  | |_) | (_) | |_ \n"
        "  \\____|_|    \\___/   |____/ \\___/ \\__|\n";


#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"

char clear_screen[] = "\033[2J";
char set_pos[] = "\033[H";

char shoot_input_coordiantes[] = "\033[19;45H";

int enemy_board[10][10]; 
int my_board[10][10];


void placeShip(int* board[10][10]) {
    int ship_sizes[] = {2, 3, 4, 5};
    int num_ships = 0;

    while (num_ships < 4) {
        int length = ship_sizes[num_ships];
        int row, col;
        uint8_t horizontal = rng_getRandomValue_waiting() & 0x01;

        if (horizontal) {
            row = modulo(rng_getRandomValue_waiting(), 10);
            col = modulo(rng_getRandomValue_waiting(), 10 - length + 1);

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
            row = modulo(rng_getRandomValue_waiting(), 10 - length + 1);
            col = modulo(rng_getRandomValue_waiting(), 10);

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


int modulo(int zaehler, int nenner) {
    while (zaehler >= nenner) {
        zaehler -= nenner;
    }
    return zaehler;
}

void clear_screeen(void){
  execute_ANSI_esc_codes("\033[2J");
  execute_ANSI_esc_codes("\033[H");
}

//timer method, which will be executed
void Interrupt8_Handler(void){
  
  timer_clearCompareEvent();
  
  uint8_t randomNumber1 = rng_getRandomValue_waiting();
  uint8_t randomNumber2 = rng_getRandomValue_waiting();

  //uart_writeByte(modulo(randomNumber1, 10) + 48);
  //uart_writeByte(modulo(randomNumber2, 10) + 48);

  my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] = 'x';
  //my_board[0][0] = modulo(randomNumber2, 10) + 48;
  //my_board[0][0] = 49;
  //uart_writeByte(my_board[0][0]);
  //timer_init_detailed(5, 30, 19530);
  

  int time_offset = 3730;
  int new_time_delay = modulo(rng_getRandomValue_waiting(), 16) * 1000;
  time_offset += new_time_delay;
  timer_init_detailed(28, 30, time_offset);

  draw_screen(&my_board, &enemy_board);
}


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

void print_ascii_art(char ascii_art[], char esc_code[]){
  uart_writeByte('\n');
  execute_ANSI_esc_codes(esc_code);
  for(int i = 0; ascii_art[i] != '\0'; i++) {
    uart_writeByte(ascii_art[i]);
    if(ascii_art[i] == '\n'){
      execute_ANSI_esc_codes(esc_code);
    }    
  }
}

void show_statistics(char statistics_text[], char ansi_coordinates[]){
  execute_ANSI_esc_codes(ansi_coordinates);
  execute_ANSI_esc_codes(statistics_text);
}

void draw_screen(int* my_board[10][10], int* enemy_board[10][10]){
  
  clear_screeen();

  print_ascii_art(ascii_art_player, "\033[15C");
  draw_board(my_board, "\033[9;5H", 1);

  
  print_ascii_art(ascii_art_bot, "\033[15C");
  draw_board(enemy_board, "\033[28;5H", 0);

  show_statistics("Total Shoots: ", "\033[12;30H");
  show_statistics("Total Hits: ", "\033[14;30H");
  show_statistics("Total Miss: ", "\033[16;30H");

  show_statistics("Shoot: ", "\033[19;30H");
  show_statistics("Already Shoot: ", "\033[20;30H");


  show_statistics("Total Shoots: ", "\033[31;30H");
  show_statistics("Total Hits: ", "\033[33;30H");
  show_statistics("Total Miss: ", "\033[35;30H");
  show_statistics("Already Shoot: ", "\033[39;30H");

  //execute_ANSI_esc_codes("\033[20;40H");
  //execute_ANSI_esc_codes("hallo");

  execute_ANSI_esc_codes(shoot_input_coordiantes);
}


void draw_board(int board[10][10], char start_pos[], int8_t visible){
  //execute_ANSI_esc_codes("\033[3;5H");
  execute_ANSI_esc_codes(start_pos);
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
          if(visible == 0 && board[i][j] == 1){
            uart_writeByte(' ');
          }
          else{
            uart_writeByte(board[i][j]);
          }
          
          uart_writeByte(' ');
      }
      uart_writeByte(206);
      
      if(i == 5){
        //execute_ANSI_esc_codes("\033[20;40H");
        //execute_ANSI_esc_codes("hallo");
        //("Total shoots: ", 0,0,0, "\033[10C");
      }
      
      uart_writeByte('\n');
  }

  execute_ANSI_esc_codes("\033[3C");
  for(int i = 0; i < 21; i++){
    uart_writeByte(205);
  }

}


int main( void )
{
  uart_init();
  rng_init();
  
  // 5 seconds
  //timer_init_detailed(28, 30, 19730);

  // 4 seconds
  //timer_init_detailed(28, 30, 15730);

  // 3 seconds
  timer_init_detailed(28, 30, 11730);

  // 2 seconds
  //timer_init_detailed(28, 30, 7730);

  // 1 second
  //timer_init_detailed(28, 30, 3730);

  // range is between 16.000

  int input_user[2]; 
  int input_counter = 0;

  for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            my_board[i][j] = ' ';
            enemy_board[i][j] = ' ';
        }
  }

  placeShip(&my_board);
  placeShip(&enemy_board);

  //setup_board(my_board);
  //setup_board(enemy_board);


  draw_screen(&my_board, &enemy_board);
  //execute_ANSI_esc_codes("\033[15;2H");
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
          execute_ANSI_esc_codes(shoot_input_coordiantes);
          uart_writeByte(' ');
          uart_writeByte(' ');
          execute_ANSI_esc_codes(shoot_input_coordiantes);
          input_counter = 0;
      }

      //enter 
      if(read_char == 13){
          if(input_counter >= 2){
            input_counter = 0;
            enemy_board[input_user[0]][input_user[1]] = 'x';

            execute_ANSI_esc_codes(clear_screen);
            execute_ANSI_esc_codes(set_pos);
            draw_screen(&my_board, &enemy_board);
            execute_ANSI_esc_codes(shoot_input_coordiantes);
            
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
