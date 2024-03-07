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

int input_counter = 0;
int input_user[2];

int total_shoots_player[4] = {0, 0, 0, 0};
int total_hits_player[4] = {0, 0, 0, 0};
int total_missess_player[4] = {0, 0, 0, 0};

int total_shoots_bot[4] = {0, 0, 0, 0};
int total_hits_bot[4] = {0, 0, 0, 0};
int total_missess_bot[4] = {0, 0, 0, 0};

int message_value = 0;
char message_start[] = "Please type in your coordinates!";
char message_hit[] = "That was a hit!";
char message_miss[] = "Nothing was there, unfortunatly!";
char message_not_valid[] = "Input not valid";
char message_already_shot[] = "You shot already there!";


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
  
  uint8_t randomNumber1 = 0;
  uint8_t randomNumber2 = 0;

  
  
  do{
    randomNumber1 = rng_getRandomValue_waiting();
    randomNumber2 = rng_getRandomValue_waiting();

    
  }while(my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] == 'x' || my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] == 'o');

  if(my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] == 1){
      my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] = 'x';
      increment_stats_array(&total_shoots_bot);
      increment_stats_array(&total_hits_bot);
  }
  else{
    my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] = 'o';
    increment_stats_array(&total_shoots_bot);
    increment_stats_array(&total_missess_bot);
  }

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

void show_statistics(char statistics_text[], char ansi_coordinates[], int values[4]){
  execute_ANSI_esc_codes(ansi_coordinates);
  execute_ANSI_esc_codes(statistics_text);
  uart_writeByte(values[0] + 48);
  uart_writeByte(values[1] + 48);
  uart_writeByte(values[2] + 48);
  uart_writeByte(values[3] + 48);
}

void show_input(char statistics_text[], char ansi_coordinates[]){
  execute_ANSI_esc_codes(ansi_coordinates);
  execute_ANSI_esc_codes(statistics_text);
}

int8_t check_if_someone_won(int* board[10][19]){
  int8_t loose = 1;
  for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if(board[i][j] == 1){
              loose = 0;
            }
        }
    }
  return loose;
}

void show_message(int8_t message_value,  char ansi_coordinates[]){
  execute_ANSI_esc_codes(ansi_coordinates);
  execute_ANSI_esc_codes("Message: ");

  switch(message_value) {
        case 0:
            execute_ANSI_esc_codes(message_start);
            break;
        case 1:
            execute_ANSI_esc_codes(message_hit);
            break;
        case 2:
            execute_ANSI_esc_codes(message_miss);
            break;
        case 3:
            execute_ANSI_esc_codes(message_already_shot);
            break;
        case 4:
            execute_ANSI_esc_codes(message_not_valid);
            break;
    }
}

void draw_screen(int* my_board[10][10], int* enemy_board[10][10]){
  
  clear_screeen();

  print_ascii_art(ascii_art_player, "\033[15C");
  draw_board(my_board, "\033[9;5H", 1);

  
  print_ascii_art(ascii_art_bot, "\033[15C");
  draw_board(enemy_board, "\033[28;5H", 0);

  show_statistics("Total Shoots: ", "\033[12;30H", total_shoots_player);
  show_statistics("Total Hits: ", "\033[14;30H", total_hits_player);
  show_statistics("Total Miss: ", "\033[16;30H", total_missess_player);

  show_input("Shoot: ", "\033[19;30H");
  show_message(message_value, "\033[21;30H");
  //show_statistics("Already Shoot: ", "\033[20;30H", &total_shoots);


  show_statistics("Total Shoots: ", "\033[31;30H", total_shoots_bot);
  show_statistics("Total Hits: ", "\033[33;30H", total_hits_bot);
  show_statistics("Total Miss: ", "\033[35;30H", total_missess_bot);
  //show_statistics("Already Shoot: ", "\033[39;30H");

  //execute_ANSI_esc_codes("\033[20;40H");
  //execute_ANSI_esc_codes("hallo");

  execute_ANSI_esc_codes(shoot_input_coordiantes);
  for(int i = 0; i < input_counter; i++){
    uart_writeByte(input_user[i]);
  }
}


void increment_stats_array(int stats_array[4]){
  stats_array[3] += 1;
    if(stats_array[3] == 10){
      stats_array[3] = 0;
      stats_array[2] += 1;
      if(stats_array[2] == 10){
        stats_array[2] = 0;
        stats_array[1] += 1;
        if(stats_array[1] == 10){
          stats_array[1] = 0;
          stats_array[0] += 1;
        }
      }
    }
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


      
      if(check_if_someone_won(&enemy_board) == 1){
        for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            my_board[i][j] = ' ';
            enemy_board[i][j] = ' ';
        }
        }
        break;   
      }
      if(check_if_someone_won(&my_board) == 1){
        for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            my_board[i][j] = ' ';
            enemy_board[i][j] = ' ';
        }
        }
        break;
      }
      

    if(0 != read_char){
      
      //write_board_on_screen(enemy_board, 0);
      
      //do {
      //  value = rng_getRandomValue_immediately();
      //} while (value < 65 || value > 123);

      if(input_counter < 2 && read_char != 127 && read_char != 13){
        uart_writeByte(read_char);
        if(read_char >= 97 && read_char <= 106){
          input_user[input_counter] = read_char - 32;
        }
        else{
          input_user[input_counter] = read_char;
        }
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
            //check input
            input_counter = 0;
            if(input_user[0] >= 'A' && input_user[0] <= 'J' && input_user[1] >= '0' && input_user[1] <= '9'){

              	uart_writeByte(input_user[0]);
                uart_writeByte('s');
                uart_writeByte('s');
                uart_writeByte('s');
                uart_writeByte('s');
              
              
              if(enemy_board[input_user[1] - 48][input_user[0] - 65] == 1){
                enemy_board[input_user[1] - 48][input_user[0] - 65] = 'x';
                increment_stats_array(&total_hits_player);
                increment_stats_array(&total_shoots_player);
                message_value = 1;
              }
              else if(enemy_board[input_user[1] - 48][input_user[0] - 65] == ' '){
                enemy_board[input_user[1] - 48][input_user[0] - 65] = 'o';
                increment_stats_array(&total_missess_player);
                increment_stats_array(&total_shoots_player);
                message_value = 2;
              }
              else{
                message_value = 3;
              }
              
            }
            else{
              message_value = 4;
            }

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
    
      //uart_writeByte(rng_getRandomValue_immediately());

    }
  }

  return 0;
}
