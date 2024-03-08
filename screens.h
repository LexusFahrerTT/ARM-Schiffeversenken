#include "uart.h"

void uart_writeString(const char* str) {
    while (*str != '\0') {
        uart_writeByte(*str);
        str++;
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

void draw_you_lost(const char* player_name, char* total_shoots, char* total_hits, char* total_miss) {
    char *ascii_art = 
        " __   __            _           _     _ \n"
        "\\ \\ / /           | |         | |   | |\n"
        " \\ V /___  _   _  | | ___  ___| |_  | |\n"
        "  \\ // _ \\| | | | | |/ _ \\/ __| __| | |\n"
        "  | | (_) | |_| | | | (_) \\__ \\ |_  |_|\n"
        "  \\_/\\___/ \\__,_| |_|\\___/|___/\\__| (_)\n"
        "                                        \n"
        "                                        \n";
    print_ascii_art(ascii_art, "\033[15C");
    uart_writeByte('\n');
    uart_writeByte('\n');
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(player_name);
    uart_writeString(" lost the Game!\n");
    uart_writeByte('\n');
    uart_writeString("\t \tTotal Shoots: ");
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(total_shoots);
    uart_writeString("\n \t \tTotal Hits: ");
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(total_hits);
    uart_writeString("\n \t \tTotal Miss: ");
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(total_miss);
    uart_writeByte('\n');
}

void draw_you_won(const char* player_name, char* total_shoots, char* total_hits, char* total_miss) {
    char *ascii_art =
        "  __   __                                  _ \n"
        " \\ \\ / /                                 | |\n"
        "  \\ V /___  _   _  __      _____  _ __   | |\n"
        "   \\ // _ \\| | | | \\ \\ /\\ / / _ \\| '_ \\  | |\n"
        "   | | (_) | |_| |  \\ V  V / (_) | | | | |_|\n"
        "   \\_/\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_| (_)\n"
        "                                            \n"
        "                                            \n";
    print_ascii_art(ascii_art, "\033[15C");
    uart_writeByte('\n');
    uart_writeByte('\n');
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(player_name);
    uart_writeString(" won the Game!\n");
    uart_writeByte('\n');
    uart_writeString("\t \tTotal Shoots: ");
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(total_shoots);
    uart_writeString("\n \t \tTotal Hits: ");
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(total_hits);
    uart_writeString("\n \t \tTotal Miss: ");
    uart_writeByte('\t');
    uart_writeByte('\t');
    uart_writeString(total_miss);
    uart_writeByte('\n');
}