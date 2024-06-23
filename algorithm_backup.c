/*
** {==========================================================================
** 算法
** ===========================================================================
*/


#include "KTP.h"


/* 交换两个数的值 */
static void
Swap(int *a, int *b)
{
    if (a == b)
        return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}


/* 判断是否在棋盘内 */
static boolen
isValid(Coord coord, Point innerBoard[BOARD_SIZE][BOARD_SIZE])
{
    return coord.x >= 0 && coord.x < BOARD_SIZE && \
           coord.y >= 0 && coord.y < BOARD_SIZE && \
           innerBoard[coord.x][coord.y].isPassed == False;
}


static void
UpdateDirection(Coord *coord_ptr, Coord *coord_t_ptr, int index)
{
    /* 8 个方向 */
    int dir[8][2] = {
        {2, -1}, {-2, -1}, {-2, 1}, {2, 1},
        {1, -2}, {-1, -2}, {-1, 2}, {1, 2}
    };
    coord_t_ptr->x = coord_ptr->x + dir[index][0];
    coord_t_ptr->y = coord_ptr->y + dir[index][1];
}


/* 分别得到如果走向周围的 8 个点，那么将会有多少个下一步 */
static void
getNext(Coord coord, int* next, Point innerBoard[BOARD_SIZE][BOARD_SIZE])
{
    Coord coord_t, coord_tt;
    for (int i = 0; i < 8; i++) {
        UpdateDirection(&coord, &coord_t, i);
        if (isValid(coord_t, innerBoard)) {
            for (int j = 0; j < 8; j++) {
                UpdateDirection(&coord_t, &coord_tt, j);
                if (isValid(coord_tt, innerBoard))
                    next[i]++;
            }
        }
    }
}


/* 入栈 */
static void
push(Coord coord, History* history_ptr)
{
    history_ptr->pointer++;
    history_ptr->path[history_ptr->pointer] = coord;
}


// /* 出栈 */
// static void
// pop(History* history_ptr)
// {
//     history_ptr->path[history_ptr->pointer] = (Coord) {0, 0};
//     history_ptr->pointer--;
// }


/*
** 由贪心算法，我们要给 next 数组进行非递减排序
** 并将具体方向对应地编号写到 seq 数组中
** 例如 next[3] = {5, 8, 2}
** 那么 seq [3] = {2, 0, 1}
*/
static void
getSeq(int* next, int* seq)
{
    int n[8];
    for (int i = 0; i < 8; i++)
        n[i] = next[i];

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7 - i; j++) {
            if (n[j] > n[j + 1]) {
                Swap(&n[j], &n[j + 1]);
                Swap(&seq[j], &seq[j + 1]);
            }
        }
    }
}


/* 更新 history，包括数组元素和栈指针 */
void
GetNextStep(Point innerBoard[BOARD_SIZE][BOARD_SIZE], History* history_ptr)
{
    Coord coord = history_ptr->path[history_ptr->pointer];

    int next[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int  seq[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    getNext(coord, next, innerBoard);
    getSeq(next, seq);

    for (int i = 0; i < 8; i++) {
        Coord coord_t;
        UpdateDirection(&coord, &coord_t, seq[i]);
        if (isValid(coord_t, innerBoard)) {
            push(coord_t, history_ptr);
            break;
        }
    }
}
