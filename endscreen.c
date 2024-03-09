/**
 * @file endscreen.c
 * @brief Source-Datei für den Endscreen
 */

#include <stdint.h>
#include "maingame.h"


/**
 * @brief startet das spiel erneut, falls r oder R eingegeben worden ist
 * 
 * 
 * @param read_char ist der eingegebene Character des Spielers
 */
void end_screen(uint8_t read_char){
  if(0 != read_char && (read_char == 'r' || read_char == 'R')){
    game_mode = 1;
    setup_main_game();
    timer_init_detailed(28, 30, 11730);
    draw_main_game_screen(&my_board, &enemy_board);
  }
}


/**
 * @brief Methode, um den Loser End Screen darzustellen
 * 
 * @param player_stats ist ein array mit allen Stats Arrays des Spielers
 * @param bot_stats ist ein array mit allen Stats Arrays des Bots
 */
void draw_you_lost(int* player_stats[3], int* bot_stats[3]) {
    char *ascii_art = 
        "                        __   __            _           _     _ \n"
        "                       \\ \\ / /           | |         | |   | |\n"
        "                        \\ V /___  _   _  | | ___  ___| |_  | |\n"
        "                         \\ // _ \\| | | | | |/ _ \\/ __| __| | |\n"
        "                         | | (_) | |_| | | | (_) \\__ \\ |_  |_|\n"
        "                         \\_/\\___/ \\__,_| |_|\\___/|___/\\__| (_)\n"
        "                                                                       \n"
        "                                                                           \n"
        "                                                                           \n"
        "   ______                   ______   _         ______          _             _   \n"
        "   | ___ \\                  | ___ \\ | |        | ___ \\        | |           | |  \n"
        "   | |_/ / __ ___  ___ ___  | |_/ / | |_ ___   | |_/ /___  ___| |_ __ _ _ __| |_ \n"
        "   |  __/ '__/ _ \\/ __/ __| |    /  | __/ _ \\  |    // _ \\/ __| __/ _` | '__| __|\n"
        "   | |  | | |  __/\\__ \\__ \\ | |\\ \\  | || (_) | | |\\ \\  __/\\__ \\ || (_| | |  | |_ \n"
        "   \\_|  |_|  \\___||___/___/ \\_| \\_|  \\__\\___/  \\_| \\_\\___||___/\\__\\__,_|_|   \\__|\n"
        "                                                                              \n"
        "                                                                               \n";
    print_ascii_art(ascii_art, "\033[15C");


    execute_ANSI_or_print_text("Player Stats \n\n\n");
    show_statistics("Total Shoots: ", "\033[21;16H", player_stats[0]);
    show_statistics("Total Hits: ", "\033[22;16H", player_stats[1]);
    show_statistics("Total Miss: ", "\033[23;16H", player_stats[2]);

    execute_ANSI_or_print_text("\n \n \n \n \033[13C Bot Stats");
    show_statistics("Total Shoots: ", "\033[29;16H", bot_stats[0]);
    show_statistics("Total Hits: ", "\033[30;16H", bot_stats[1]);
    show_statistics("Total Miss: ", "\033[31;16H", bot_stats[2]);
}


/**
 * @brief Methode, um den Win End Screen darzustellen
 * 
 * @param player_stats ist ein array mit allen Stats Arrays des Spielers
 * @param bot_stats ist ein array mit allen Stats Arrays des Bots
 */
void draw_you_won(int* player_stats[3], int* bot_stats[3]) {
    char *ascii_art =
        "                    __   __                                  _ \n"
        "                   \\ \\ / /                                 | |\n"
        "                    \\ V /___  _   _  __      _____  _ __   | |\n"
        "                     \\ // _ \\| | | | \\ \\ /\\ / / _ \\| '_ \\  | |\n"
        "                     | | (_) | |_| |  \\ V  V / (_) | | | | |_|\n"
        "                     \\_/\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_| (_)\n"
        "                                                                       \n"
        "                                                                           \n"
        "   ______                   ______   _         ______          _             _   \n"
        "   | ___ \\                  | ___ \\ | |        | ___ \\        | |           | |  \n"
        "   | |_/ / __ ___  ___ ___  | |_/ / | |_ ___   | |_/ /___  ___| |_ __ _ _ __| |_ \n"
        "   |  __/ '__/ _ \\/ __/ __| |    /  | __/ _ \\  |    // _ \\/ __| __/ _` | '__| __|\n"
        "   | |  | | |  __/\\__ \\__ \\ | |\\ \\  | || (_) | | |\\ \\  __/\\__ \\ || (_| | |  | |_ \n"
        "   \\_|  |_|  \\___||___/___/ \\_| \\_|  \\__\\___/  \\_| \\_\\___||___/\\__\\__,_|_|   \\__|\n"
        "                                                                              \n"
        "                                                                               \n";

    print_ascii_art(ascii_art, "\033[15C");

    execute_ANSI_or_print_text("Player Stats \n");
    show_statistics("Total Shoots: ", "\033[20;16H", player_stats[0]);
    show_statistics("Total Hits: ", "\033[21;16H", player_stats[1]);
    show_statistics("Total Miss: ", "\033[22;16H", player_stats[2]);

    execute_ANSI_or_print_text("\n \n \n \n \033[13C Bot Stats");
    show_statistics("Total Shoots: ", "\033[28;16H", bot_stats[0]);
    show_statistics("Total Hits: ", "\033[29;16H", bot_stats[1]);
    show_statistics("Total Miss: ", "\033[30;16H", bot_stats[2]);
}
