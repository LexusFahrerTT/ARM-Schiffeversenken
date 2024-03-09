#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"
#include "utils.h"

extern char ascii_art_player[];
extern char ascii_art_bot[];

extern char set_pos[];
extern char shoot_input_coordiantes[];

extern int enemy_board[10][10];
extern int my_board[10][10];

extern int input_counter;
extern int input_user[2];

extern int total_shoots_player[4];
extern int total_hits_player[4];
extern int total_missess_player[4];

extern int total_shoots_bot[4];
extern int total_hits_bot[4];
extern int total_missess_bot[4];


extern int* player_stats[4];
extern int* bot_stats[4];


extern int message_value;
extern char message_start[];
extern char message_hit[];
extern char message_miss[];
extern char message_not_valid[];
extern char message_already_shot[];

extern int game_mode;

void placeShip(int* board[10][10]);
void Interrupt8_Handler(void);
void show_input(char statistics_text[], char ansi_coordinates[]);
int8_t check_if_someone_won(int* board[10][10]);
void show_message(int8_t message_value, char ansi_coordinates[]);
void draw_screen(int* my_board[10][10], int* enemy_board[10][10]);
void draw_board(int board[10][10], char start_pos[], int8_t visible);
void setup_board(int* board[10][10]);
void setup_main_game(void);
void main_game(uint8_t read_char);
void end_screen(uint8_t read_char);
