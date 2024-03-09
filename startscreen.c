/**
 * @file startscreen.c
 * @brief Source-Datei für den Startscreen
 */
#include <stdint.h>
#include "register_access.h"
#include "uart.h"
#include "random.h"
#include "timer.h"
#include "utils.h"
#include "maingame.h"


/**
 * @brief Methode, die das Spiel starte, wenn man S oder s eingibt
 * @param read_char ist das eingelesene vom SPieler
 * 
 */
void start_screen(uint8_t read_char){
  if(0 != read_char && (read_char == 's' || read_char == 'S')){

    //setup whole game
    setup_main_game();

    //starte timer
    timer_init_detailed(28, 30, 11730);
    game_mode = 1;
    draw_main_game_screen(&my_board, &enemy_board);
  }
}

void draw_start_screen() {
    char *ascii_art =
        "                                     |__\n"
        "                                     |\\/ \n"
        "                                     ---\n"
        "                                     / | [\n"
        "                              !      | |||\n"
        "                            _/|     _/|-++'\n"
        "                        +  +--|    |--|--|_ |-\n"
        "                     { /|__|  |/\\__|  |--- |||__/\n"
        "                    +---------------___[}-_===_.'____                 /\\\n"
        "                ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _\n"
        " __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7\n"
        "|                                                                           /\n"
        "|                               von    Dominik, Miguel, Lavpreet, Valentin /\n"
        " \\_________________________________________________________________________|\n"
        "\n"
        "                       Schiffe versenken: ARM Edition                             \n"
        "                                                                                   \n"
        "                                                                                   \n"
        "                                                                                   \n"
        " ______                        _____       _               _____ _             _   \n"
        " | ___ \\                      /  ___|     | |             /  ___| |           | |  \n"
        " | |_/ / __ ___  ___ ___      \\ `--.      | |_ ___        \\ `--.| |_ __ _ _ __| |_ \n"
        " |  __/ '__/ _ \\/ __/ __|      `--. \\     | __/ _ \\        `--. \\ __/ _` | '__| __|\n"
        " | |  | | |  __/\\__ \\__ \\     /\\__/ /     | || (_) |      /\\__/ / || (_| | |  | |_ \n"
        " \\_|  |_|  \\___||___/___/     \\____/       \\__\\___/       \\____/ \\__\\__,_|_|   \\__|\n"
        "                                                                               \n";
    print_ascii_art(ascii_art, "\033[15C");
}
