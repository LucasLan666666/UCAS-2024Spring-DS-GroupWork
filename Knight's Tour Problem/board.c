/*
** {==========================================================================
** 棋盘的一些基础配置
** ===========================================================================
*/

#include "KTP.h"
#include <stdio.h>


/* 棋盘图案 */

static const char     top_left[] = "┌";
static const char    top_right[] = "┐";
static const char  bottom_left[] = "└";
static const char bottom_right[] = "┘";

static const char        top_T[] = "┬";
static const char     bottom_T[] = "┴";
static const char       left_T[] = "├";
static const char      right_T[] = "┤";
static const char        cross[] = "┼";

static const char        h_bar[] = "─";
static const char        v_bar[] = "│";

/* 神烦狗 */
static const char *DOGE[] = {

    YELLOW "                              " RESET,
    YELLOW "░░░░░░░█▐▓▓░████▄▄▄█▀▄▓▓▓▌█   " RESET,
    YELLOW "░░░░░▄█▌▀▄▓▓▄▄▄▄▀▀▀▄▓▓▓▓▓▌█   " RESET,
    YELLOW "░░░▄█▀▀▄▓█▓▓▓▓▓▓▓▓▓▓▓▓▀░▓▌█   " RESET,
    YELLOW "░░█▀▄▓▓▓███▓▓▓███▓▓▓▄░░▄▓▐█▌  " RESET,
    YELLOW "░█▌▓▓▓▀▀▓▓▓▓███▓▓▓▓▓▓▓▄▀▓▓▐█  " RESET,
    YELLOW "▐█▐██▐░▄▓▓▓▓▓▀▄░▀▓▓▓▓▓▓▓▓▓▌█▌ " RESET,
    YELLOW "█▌███▓▓▓▓▓▓▓▓▐░░▄▓▓███▓▓▓▄▀▐█ " RESET,
    YELLOW "█▐█▓▀░░▀▓▓▓▓▓▓▓▓▓██████▓▓▓▓▐█ " RESET,
    YELLOW "▌▓▄▌▀░▀░▐▀█▄▓▓██████████▓▓▓▌█▌" RESET,
    YELLOW "▌▓▓▓▄▄▀▀▓▓▓▀▓▓▓▓▓▓▓▓█▓█▓█▓▓▌█▌" RESET,
    YELLOW "█▐▓▓▓▓▓▓▄▄▄▓▓▓▓▓▓█▓█▓█▓█▓▓▓▐█ " RESET,
    YELLOW "                              " RESET,
    GREEN  "    别吵，我在思考。。。         " RESET

};




/* 插入字符，注意 position 传的是地址，插入结束会改变 */
static void
InsertChar(char *parant, const char *child, int *pos_ptr, int char_size)
{
    int i;
    for (i = 0; i < char_size; i++, (*pos_ptr)++)
        parant[*pos_ptr] = child[i];
}



/* 插入符号，根据 Point 确定以怎样形式打印 */
static void
InsertSign(char *parant, Point block, int *pos_ptr)
{
    char str[13];

    if (!block.isPassed) { /* 还没经过，空格 */
        InsertChar(parant, "  ", pos_ptr, 2);
    }
    else if (block.isCurr) { /* 是当前马的位置，打印马 */
        InsertChar(parant, MAGENTA "♘ " CYAN, pos_ptr, CHAR_SIZE+11);
    }
    else  { /* 已经经过，打印数字 */
        snprintf(str, 13, YELLOW "%2d" CYAN, block.step);
        InsertChar(parant, str, pos_ptr, 12);
    }
}



/* 生成没有落点的行 */
static void
BuildEmptyBorderRows(char *row, const char *left, const char *right,
                     const char *seperate)
{
    int j, k;
    int pos = 0;

    InsertChar(row, left, &pos, CHAR_SIZE);

    for (j = 0; j < BOARD_SIZE - 1; j++) {
        for (k = 0; k < 4; k++)
            InsertChar(row, h_bar, &pos, CHAR_SIZE);
        InsertChar(row, seperate, &pos, CHAR_SIZE);
    }

    for (k = 0; k < 4; k++)
        InsertChar(row, h_bar, &pos, CHAR_SIZE);
    InsertChar(row, right, &pos, CHAR_SIZE + 1); /* '\0' */
}



/* 生成有落点的行 */
static void
BuildMarkedRows(char *display_row, Point *inner_row)
{
    int j;
    int pos = 0;
    for (j = 0; j < BOARD_SIZE; j++) {
        InsertChar(display_row, v_bar, &pos, CHAR_SIZE);
        InsertChar(display_row, " ", &pos, 1);
        InsertSign(display_row, inner_row[j], &pos);
        InsertChar(display_row, " ", &pos, 1);
    }
    InsertChar(display_row, v_bar, &pos, CHAR_SIZE + 1); /* '\0' */
}


/* 将 innerBoard 中记录的棋子位置，转化到 displayBoard 中 */
static void
InnerBoard2Displayboard(Point innerBoard[BOARD_SIZE][BOARD_SIZE],
                        char displayBoard[ROWS][COL_MAX_SIZE])
{
    int i;

    /* 先加上棋盘顶部边框 */
    BuildEmptyBorderRows(displayBoard[0], top_left, top_right, top_T);


    /* 填充中间部分 */
    for (i = 0; i < BOARD_SIZE - 1; i++) {
        BuildMarkedRows(displayBoard[2*i+1], innerBoard[i]);
        BuildEmptyBorderRows(displayBoard[2*i+2], left_T, right_T, cross);
    }

    /* 填充最后一行 */
    BuildMarkedRows(displayBoard[2*BOARD_SIZE-1], innerBoard[BOARD_SIZE - 1]);
    BuildEmptyBorderRows(
        displayBoard[2*BOARD_SIZE],
        bottom_left, bottom_right, bottom_T
    );
}



/* 初始化一个心中棋盘的空棋盘格局 */
void
InitInnerBoard(Point innerBoard[BOARD_SIZE][BOARD_SIZE])
{
    /* 将 innerBoard 清 0 */
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            innerBoard[i][j].isPassed = False;
            innerBoard[i][j].isCurr   = False;
            innerBoard[i][j].step     = 0;
        }
    }
}



/* 打印棋盘 */
void
PrintBoard(Point innerBoard[BOARD_SIZE][BOARD_SIZE], History *history_ptr)
{
    ClearScreen();

    PrintInfo(history_ptr);

    char displayBoard[ROWS][COL_MAX_SIZE]; /* 展示棋盘 */
    InnerBoard2Displayboard(innerBoard, displayBoard); /* 转化 */

    int i, j;

    /* 打印棋盘上的列标 */
    printf("        ");
    for (j = 0; j < BOARD_SIZE; j++)
        printf("  " BLUE "%2d" RESET " ", j);
    printf(" \n");

    /* 打印棋盘主体 */
    for (i = 0; i < ROWS; i++) { /* 一行行打印 */
        if (i % 2 != 0) { /* 展示棋盘的奇数行，打印棋盘前的行标 */
            printf(BLUE "    %2d  " RESET, (i-1)/2);
        } else {
            printf("        ");
        }

        if (i < 14) { /* 神烦狗 */
            printf(CYAN "%s" RESET, displayBoard[i]);
            printf("    %s\n", DOGE[i]);
        } else {
            printf(CYAN "%s\n" RESET, displayBoard[i]);
        }
    }

    /* 打印空行 */
    printf("\n");
}
