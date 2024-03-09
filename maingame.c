/**
 * @file maingame.c
 * @brief Source-Datei für das Hauptspiel
 */

#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"
#include "utils.h"
#include "game.h"

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


/**
 * @brief Satischer Wert, wo das eingetragene vom spieler stehen wird (Koords Angriff)
 */
char shoot_input_coordiantes[] = "\033[19;45H";

/**
 * @brief Generisches Board
 */
int enemy_board[10][10]; 

/**
 * @brief Spieler Board
 */
int my_board[10][10];

/**
 * @brief Ist Counter, wieviel ein User bereits eingebene hat und fungiert als pointer für das Array input_user
 */
int input_counter = 0;

/**
 * @brief speichert das eingetragene vom spieler
 */
int input_user[2];

int total_shoots_player[4] = {0, 0, 0, 0};
int total_hits_player[4] = {0, 0, 0, 0};
int total_missess_player[4] = {0, 0, 0, 0};

int total_shoots_bot[4] = {0, 0, 0, 0};
int total_hits_bot[4] = {0, 0, 0, 0};
int total_missess_bot[4] = {0, 0, 0, 0};

/**
 * @brief Array, mit pointer zu den stats vom Spieler
 */
int* player_stats[4] = {
    total_shoots_player,
    total_hits_player,
    total_missess_player
};

/**
 * @brief Array, mit pointer zu den stats vom Gegner Bot
 */
int* bot_stats[4] = {
    total_shoots_bot,
    total_hits_bot,
    total_missess_bot
};


/**
 * @brief Wert sagt auf, welche Message dann angezeigt wird
 */
int message_value = 0;
char message_start[] = "Please type in your coordinates!";
char message_hit[] = "That was a hit!";
char message_miss[] = "Nothing was there, unfortunatly!";
char message_not_valid[] = "Input not valid";
char message_already_shot[] = "You shot already there!";



/**
 * @brief Methode, die beim erreichen des Timerwerts ausgeführt wird.
 * 
 */
void Interrupt8_Handler(void){
  
  // timer reset
  timer_clearCompareEvent();
  
  uint8_t randomNumber1 = 0;
  uint8_t randomNumber2 = 0;


  // solange zufallszahlen generieren, bis diese "neu" sind bzw. die position noch nicht beschossen worden ist
  do{
    randomNumber1 = rng_getRandomValue_waiting();
    randomNumber2 = rng_getRandomValue_waiting();

    
  }while(my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] == 'x' || my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] == 'o');


  //falls treffer
  if(my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] == 1){
      my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] = 'x';
      increment_stats_array(&total_shoots_bot);
      increment_stats_array(&total_hits_bot);
  }
  //falls kein treffer
  else{
    my_board[modulo(randomNumber1, 10)][modulo(randomNumber2, 10)] = 'o';
    increment_stats_array(&total_shoots_bot);
    increment_stats_array(&total_missess_bot);
  }


  //timer neu einstellen auf eine zufallszeit zwischen 1-5 sekunden
  int time_offset = 3730;
  int new_time_delay = modulo(rng_getRandomValue_waiting(), 16) * 1000;
  time_offset += new_time_delay;
  

  //neueingestellter timer starten
  timer_init_detailed(28, 30, time_offset);
  //timer_init_detailed(8, 30, 5000);

  //draw screen zum schluss hihi
  draw_main_game_screen(&my_board, &enemy_board);
}


/**
 * @brief Methode, die das eingegebene vom user auf dem Screen einleitend darstellt
 * @param text Text, der dargestellt wird
 * @param ansi_coordinates Position, wo der Text angezeigt wird
 * 
 */
void show_input(char text[], char ansi_coordinates[]){
  execute_ANSI_or_print_text(ansi_coordinates);
  execute_ANSI_or_print_text(text);
}

/**
 * @brief Methode die überprüft, ob das Board vollständig zerbombt ist
 * @param board ist das jeweilige übergebene Board
 * 
 */
int8_t check_if_someone_won(int* board[10][10]){
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

/**
 * @brief Methode die eine ausgewählte Nachricht auf dem Screen herausprintet
 * @param message_value ist die ausgewählte nachricht
 * @param ansi_coordinates Position der Nachricht
 * 
 */
void show_message(int8_t message_value,  char ansi_coordinates[]){
  execute_ANSI_or_print_text(ansi_coordinates);
  execute_ANSI_or_print_text("Message: ");

  switch(message_value) {
        case 0:
            execute_ANSI_or_print_text(message_start);
            break;
        case 1:
            execute_ANSI_or_print_text(message_hit);
            break;
        case 2:
            execute_ANSI_or_print_text(message_miss);
            break;
        case 3:
            execute_ANSI_or_print_text(message_already_shot);
            break;
        case 4:
            execute_ANSI_or_print_text(message_not_valid);
            break;
    }
}


/**
 * @brief Methode, um den kompletten Main Game Screen zu printen
 * @param my_board ist das Board des spielers
 * @param enemy_board ist das Baord des Gegeners
 * 
 */
void draw_main_game_screen(int* my_board[10][10], int* enemy_board[10][10]){
  
  //erst den Screen clean machen :)
  clear_screen();

  //dann zeichnen und malen
  print_ascii_art(ascii_art_player, "\033[15C");
  draw_board(my_board, "\033[9;5H", 1);

  
  print_ascii_art(ascii_art_bot, "\033[15C");
  draw_board(enemy_board, "\033[28;5H", 0);

  show_statistics("Total Shoots: ", "\033[12;30H", total_shoots_player);
  show_statistics("Total Hits: ", "\033[14;30H", total_hits_player);
  show_statistics("Total Miss: ", "\033[16;30H", total_missess_player);

  show_input("Shoot: ", "\033[19;30H");
  show_message(message_value, "\033[21;30H");

  show_statistics("Total Shoots: ", "\033[31;30H", total_shoots_bot);
  show_statistics("Total Hits: ", "\033[33;30H", total_hits_bot);
  show_statistics("Total Miss: ", "\033[35;30H", total_missess_bot);

  execute_ANSI_or_print_text(shoot_input_coordiantes);

  //basierend darauf, wie viel der User bereits eingeben hat, wird diese herausgesprintet
  for(int i = 0; i < input_counter; i++){
    uart_writeByte(input_user[i]);
  }
}


/**
 * @brief Helper Methode, um ein komplettes Board zu zeichnen
 * @param board ist das Board welches gezeichnet werden soll
 * @param start_pos Position der zeichnung
 * @param visible 1 falls die Schiffe dargestellt werden sollen, 0 falls nein
 * 
 */
void draw_board(int board[10][10], char start_pos[], int8_t visible){
  execute_ANSI_or_print_text(start_pos);
  
  //A-J
  for(int j = 0; j < 10; j++) {
    uart_writeByte(65 + j);
    uart_writeByte(' ');
  }
  uart_writeByte('\n');
  execute_ANSI_or_print_text("\033[2C");
  
  //print top border
  uart_writeByte(' ');
  for(int i = 0; i < 21; i++){
    uart_writeByte(205);
  }

  uart_writeByte('\n');

  //print board values
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
      uart_writeByte('\n');
  }

  // draw button border
  execute_ANSI_or_print_text("\033[3C");
  for(int i = 0; i < 21; i++){
    uart_writeByte(205);
  }
}


/**
 * @brief hauptspiel methode
 * @param read_char eingegebene vom Spieler
 * 
 */
void main_game(uint8_t read_char){

  //falls enemy baord zerstört ist
  if(check_if_someone_won(&enemy_board) == 1){
    message_value = 0;
    timer_disable();
    clear_screen();
    draw_you_won(player_stats, bot_stats);
    game_mode = 2;  
    //print endscreen won
    return;
  }

  //falls spieler board zerstört ist
  if(check_if_someone_won(&my_board) == 1){
    message_value = 0;
    timer_disable();
    clear_screen();
    draw_you_lost(player_stats, bot_stats);
    game_mode = 3;
    // print endscreen loose
    return;
  }


  if(0 != read_char){
    //input darf kein enter order return sein und man darf nur 2 zeichen max eingegeben haben
    if(input_counter < 2 && read_char != 127 && read_char != 13){
      uart_writeByte(read_char);

      //damit wird lower case hochskaliert und gespeichert in high case
      if(read_char >= 97 && read_char <= 106){
        input_user[input_counter] = read_char - 32;
      }
      else{
        input_user[input_counter] = read_char;
      }
      input_counter++;
    }
    
    //return wird gedrückt
    if(read_char == 127){

        execute_ANSI_or_print_text(shoot_input_coordiantes);
        uart_writeByte(' ');
        uart_writeByte(' ');
        execute_ANSI_or_print_text(shoot_input_coordiantes);

        //reset input (pointer of inputarray)
        input_counter = 0;
    }

    //enter wird gedrückt
    if(read_char == 13){

        //geht nur weiter, wenn 2 sachen eingebene worden sind, ätsch bätsch!
        if(input_counter >= 2){

          //check input
          input_counter = 0;
          if(input_user[0] >= 'A' && input_user[0] <= 'J' && input_user[1] >= '0' && input_user[1] <= '9'){

            uart_writeByte(input_user[0]);              
            
            //falls treffer
            if(enemy_board[input_user[1] - 48][input_user[0] - 65] == 1){
              enemy_board[input_user[1] - 48][input_user[0] - 65] = 'x';
              increment_stats_array(&total_hits_player);
              increment_stats_array(&total_shoots_player);
              message_value = 1;
            }//falls kein treffer
            else if(enemy_board[input_user[1] - 48][input_user[0] - 65] == ' '){
              enemy_board[input_user[1] - 48][input_user[0] - 65] = 'o';
              increment_stats_array(&total_missess_player);
              increment_stats_array(&total_shoots_player);
              message_value = 2;
            }
            //falls bereits getroffen
            else{
              message_value = 3;
            }
          }//falls input invalide
          else{
            message_value = 4;
          }
          clear_screen();
          draw_main_game_screen(&my_board, &enemy_board);
          execute_ANSI_or_print_text(shoot_input_coordiantes);
        }
    }
  }
}

