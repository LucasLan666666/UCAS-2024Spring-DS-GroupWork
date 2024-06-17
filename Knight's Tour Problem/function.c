/*
** {==========================================================================
** 一些功能性函数
** ===========================================================================
*/

#include "KTP.h"
#include <stdio.h>
#include <stdlib.h>

/* 清屏 */
void
ClearScreen(void)
{
    int clear = system(CLEAR_SCREEN);
    (void)clear;
}


/* 按下回车继续，读到 EOF 退出，不接受实际输入 */
void
Continue(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    if (c == EOF) exit(0); /* 接收到 EOF 直接退出 */
}


/* 刷新历史记录 */
void
RefreshHistory(History *history_ptr)
{
    int i;
    for (i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
        history_ptr->path[i].x = 0;
        history_ptr->path[i].y = 0;
    }
    history_ptr->pointer = 0;
}


/* 获取初始位置，写入路径栈 */
void
GetStart(History *history_ptr)
{
    int x, y;
    int status; /* 检查输入状态 */
    boolen isValid = False; /* 输入是否合法 */

    printf("         ");
    printf(BOLD "请输入马的起始坐标（例如：5 3）：" RESET);
    do {
        if ((status = scanf ("%d%d", &x, &y)) == EOF)
            exit(0);
        if (status == 2 &&
            x >= 0 && x < BOARD_SIZE &&
            y >= 0 && y < BOARD_SIZE)
        {
            history_ptr->path[0].x = x;
            history_ptr->path[0].y = y;
            history_ptr->pointer = 0;
            isValid = True;
        }
        else {
            printf(RED "输入不合法，请重新输入起始坐标（例如：5 3）：" RESET);
        }
        while (getchar() != '\n') /* 丢弃缓冲区中的剩余字符，直到遇到换行符 */
            ;
    } while (!isValid);
}


/* 打印重要信息 */
void
PrintInfo(History *history_ptr)
{
    // if (history_ptr->)
    printf("        ");
    printf(YELLOW "当前步数：" RESET);
    printf(GREEN "%2d" RESET, history_ptr->pointer);
    printf("             ");
    printf(YELLOW "坐标：" RESET);
    printf(
        GREEN "(%d, %d)\n\n" RESET,
        history_ptr->path[history_ptr->pointer].x,
        history_ptr->path[history_ptr->pointer].y
    );
}


/* 根据历史记录更新心中棋盘 */
void
UpdateInnerBoard(History *history_ptr, Point innerBoard[BOARD_SIZE][BOARD_SIZE])
{
    InitInnerBoard(innerBoard);
    int i;
    for (i = 0; i <= history_ptr->pointer; i++) {
        innerBoard
            [history_ptr->path[i].x]
            [history_ptr->path[i].y]
        .isPassed = True;

        innerBoard
            [history_ptr->path[i].x]
            [history_ptr->path[i].y]
        .step = i;
    }
    innerBoard
        [history_ptr->path[history_ptr->pointer].x]
        [history_ptr->path[history_ptr->pointer].y]
    .isCurr = True;
}


/* 判断是否结束，是则退出 */
void
JudgeOver(History *history_ptr)
{
    printf("        ");
    if (history_ptr->pointer == BOARD_SIZE*BOARD_SIZE-1) { /* 走完了 */
        printf(MAGENTA "已经走完全程，按回车键退出..." RESET);
        Continue();
        exit(0);
    }
    printf(GREEN "按下回车键继续..." RESET);
}
