/**
 * @file maingame.h
 * @brief Header-Datei für das Hauptspiel
 */

#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"
#include "utils.h"
#include "game.h"

extern char ascii_art_player[];
extern char ascii_art_bot[];

extern char set_pos[];

/**
 * @brief Satischer Wert, wo das eingetragene vom spieler stehen wird (Koords Angriff)
 */
extern char shoot_input_coordiantes[];


/**
 * @brief Generisches Board
 */
extern int enemy_board[10][10];

/**
 * @brief Spieler Board
 */
extern int my_board[10][10];

/**
 * @brief Ist Counter, wieviel ein User bereits eingebene hat und fungiert als pointer für das Array input_user
 */
extern int input_counter;
/**
 * @brief speichert das eingetragene vom spieler
 */
extern int input_user[2];

extern int total_shoots_player[4];
extern int total_hits_player[4];
extern int total_missess_player[4];

extern int total_shoots_bot[4];
extern int total_hits_bot[4];
extern int total_missess_bot[4];



/**
 * @brief Array, mit pointer zu den stats vom Spieler
 */
extern int* player_stats[4];


/**
 * @brief Array, mit pointer zu den stats vom Gegner Bot
 */
extern int* bot_stats[4];

/**
 * @brief Wert sagt auf, welche Message dann angezeigt wird
 */
extern int message_value;
extern char message_start[];
extern char message_hit[];
extern char message_miss[];
extern char message_not_valid[];
extern char message_already_shot[];



/**
 * @brief Methode, die beim erreichen des Timerwerts ausgeführt wird.
 * 
 */
void Interrupt8_Handler(void);

/**
 * @brief Methode, die das eingegebene vom user auf dem Screen einleitend darstellt
 * @param text Text, der dargestellt wird
 * @param ansi_coordinates Position, wo der Text angezeigt wird
 * 
 */
void show_input(char text[], char ansi_coordinates[]);

/**
 * @brief Methode die überprüft, ob das Board vollständig zerbombt ist
 * @param board ist das jeweilige übergebene Board
 * 
 */
int8_t check_if_someone_won(int* board[10][10]);

/**
 * @brief Methode die eine ausgewählte Nachricht auf dem Screen herausprintet
 * @param message_value ist die ausgewählte nachricht
 * @param ansi_coordinates Position der Nachricht
 * 
 */
void show_message(int8_t message_value, char ansi_coordinates[]);

/**
 * @brief Methode, um den kompletten Main Game Screen zu printen
 * @param my_board ist das Board des spielers
 * @param enemy_board ist das Baord des Gegeners
 * 
 */
void draw_main_game_screen(int* my_board[10][10], int* enemy_board[10][10]);

/**
 * @brief Helper Methode, um ein komplettes Board zu zeichnen
 * @param board ist das Board welches gezeichnet werden soll
 * @param start_pos Position der zeichnung
 * @param visible 1 falls die Schiffe dargestellt werden sollen, 0 falls nein
 * 
 */
void draw_board(int board[10][10], char start_pos[], int8_t visible);

/**
 * @brief hauptspiel methode
 * @param read_char eingegebene vom Spieler
 * 
 */
void main_game(uint8_t read_char);
