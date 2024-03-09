/**
 * @file game.c
 * @brief Source-Datei für das "komplette"  Spiel bzw. Varaiblen und Methode, die im gesamten SPiel benötigt werden
 */

#include <stdint.h>
#include "maingame.h"


/**
 * @brief game mode, welches aussagt, in welchem State sich das Spiel befindet
 * game mode = 0 | start
 * game mode = 1 | maingame
 * game mode = 2,3 | end
 */
int game_mode = 0;


/**
 * @brief Methode, um das Board in einen Anfangszutsandt zu versetzen
 * @param board ist das jeweilige übergebene Board
 * 
 */
void setup_board(int* board[10][10]){
  for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
          board[i][j] = ' ';
      }
  }
  placeShip(board);
}


/**
 * @brief Methode, um das Hauptspiel in den Anfangszusatdn zu versetztzen
 * 
 */
void setup_main_game(){

    reset_stats_array(total_shoots_player);
    reset_stats_array(total_hits_player);
    reset_stats_array(total_missess_player);

    reset_stats_array(total_shoots_bot);
    reset_stats_array(total_hits_bot);
    reset_stats_array(total_missess_bot);

    input_counter = 0;
    message_value = 0;

    setup_board(&my_board);
    setup_board(&enemy_board);

}

/**
 * @brief Methode, um ein Baord mit Schiffen zu versorgen
 * @param board ist das jeweilige übergebene Board
 */
void placeShip(int* board[10][10]) {
    int ship_sizes[] = {5, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2};
    int num_ships = 0;

    while (num_ships < 10) {
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

