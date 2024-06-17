#include "KTP.h"

#ifdef _WIN32
#include <stdlib.h>
#endif /* _WIN32 */

int
main(void)
{
#ifdef _WIN32
    system("chcp 65001"); /* 设置 Windows 控制台编码为 utf-8 */
#endif /* _WIN32 */

    Point innerBoard[BOARD_SIZE][BOARD_SIZE];   /* 心中棋盘的格局 */
    History history;                            /* 历史记录 */
    RefreshHistory(&history);                   /* 刷新历史记录 */

    Title();                                    /* 标题界面 */

    InitInnerBoard(innerBoard);                 /* 初始化心中棋盘 */
    PrintBoard(innerBoard, &history);           /* 打印心中棋盘 */
    GetStart(&history);                         /* 获取起始坐标 */
    UpdateInnerBoard(&history, innerBoard);     /* 根据历史记录更新心中棋盘 */

    while (1) {
        PrintBoard(innerBoard, &history);       /* 打印心中棋盘 */
        JudgeOver(&history);                    /* 判断是否结束，是则退出 */
        GetNextStep(innerBoard, &history);      /* 下一步 */
        // Continue();                             /* 手动停顿 */
        SleepForAWhile(500);                    /* 自动停顿 */
        UpdateInnerBoard(&history, innerBoard); /* 根据历史记录更新心中棋盘 */
    }
    return 0;
}
