/*
** {==========================================================================
** 算法
** ===========================================================================
*/

#include "KTP.h"
#include <time.h> /* 测试用 */
#include <stdlib.h> /* 测试用 */

/* 更新 history，包括数组元素和栈指针 */
void
GetNextStep(Point innerBoard[BOARD_SIZE][BOARD_SIZE], History *history_ptr)
{
    int x, y;

    history_ptr->pointer++; /* 栈指针 + 1*/

    srand(time(NULL)); /* 使用当前时间作为随机数生成的种子 */

    /* 随机选取马的落点，如果已经落过则重新选取 */
    do {
        x = random0To7();
        y = random0To7();
    } while (innerBoard[x][y].isPassed == True);

    history_ptr->path[history_ptr->pointer].x = x;
    history_ptr->path[history_ptr->pointer].y = y;
}
