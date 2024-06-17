/*
** {==========================================================================
** 花活
** ===========================================================================
*/
#include "KTP.h"
#include <stdio.h>


static const char *KT[] = {

RED"888    d8P " YELLOW" 888b    888" GREEN" 8888888" BLUE" .d8888b. " CYAN" 888    888" YELLOW" 88888888888" RESET" d8b" MAGENTA"  .d8888b. ",
RED"888   d8P  " YELLOW" 8888b   888" GREEN"   888  " BLUE"d88P  Y88b" CYAN" 888    888" YELLOW"     888    " RESET" 88P" MAGENTA" d88P  Y88b",
RED"888  d8P   " YELLOW" 88888b  888" GREEN"   888  " BLUE"888    888" CYAN" 888    888" YELLOW"     888    " RESET" 8P " MAGENTA" Y88b.     ",
RED"888d88K    " YELLOW" 888Y88b 888" GREEN"   888  " BLUE"888       " CYAN" 8888888888" YELLOW"     888    " RESET" '  " MAGENTA"  'Y888b.  ",
RED"8888888b   " YELLOW" 888 Y88b888" GREEN"   888  " BLUE"888  88888" CYAN" 888    888" YELLOW"     888    " RESET"    " MAGENTA"     'Y88b.",
RED"888  Y88b  " YELLOW" 888  Y88888" GREEN"   888  " BLUE"888    888" CYAN" 888    888" YELLOW"     888    " RESET"    " MAGENTA"       '888",
RED"888   Y88b " YELLOW" 888   Y8888" GREEN"   888  " BLUE"Y88b  d88P" CYAN" 888    888" YELLOW"     888    " RESET"    " MAGENTA" Y88b  d88P",
RED"888    Y88b" YELLOW" 888    Y888" GREEN" 8888888" BLUE" 'Y8888P88" CYAN" 888    888" YELLOW"     888    " RESET"    " MAGENTA"  'Y8888'  ",
"                                                                               ",
"               " MAGENTA"88888888888" RED" .d88888b. " GREEN" 888     888" BLUE" 8888888b. "RESET,
"               " MAGENTA"    888    " RED"d88P' 'Y88b" GREEN" 888     888" BLUE" 888   Y88b"RESET,
"               " MAGENTA"    888    " RED"888     888" GREEN" 888     888" BLUE" 888    888"RESET,
"               " MAGENTA"    888    " RED"888     888" GREEN" 888     888" BLUE" 888   d88P"RESET,
"               " MAGENTA"    888    " RED"888     888" GREEN" 888     888" BLUE" 8888888P' "RESET,
"               " MAGENTA"    888    " RED"888     888" GREEN" 888     888" BLUE" 888 T88b  "RESET,
"               " MAGENTA"    888    " RED"Y88b. .d88P" GREEN" Y88b. .d88P" BLUE" 888  T88b "RESET,
"               " MAGENTA"    888    " RED" 'Y88888P' " GREEN"  'Y88888P' " BLUE" 888   T88b"RESET

};



/* 打印大标题 */
void
Title(void)
{
    ClearScreen();

    int i;
    for (i = 0; i < 17; i++)
        printf("%s\n", KT[i]);

    printf(BOLD "\n按下回车键进入......\n" RESET);
    Continue();
}
