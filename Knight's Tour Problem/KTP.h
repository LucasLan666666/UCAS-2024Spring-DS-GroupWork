/*
** {==========================================================================
** 马踏棋盘头文件
** ===========================================================================
*/

#ifndef KTP_H
#define KTP_H

#ifdef           _WIN32
#define    CLEAR_SCREEN           "cls"   // Windows 下清屏指令
#else
#define    CLEAR_SCREEN         "clear"   // Unix-like 环境下清屏指令
#endif /* _WIN32 */

#define   BOARD_SIZE   8                        /* 棋盘大小 8*8 */
#define    CHAR_SIZE   3                        /* UTF-8 编码，一个字符 3 个字节 */
#define         ROWS   2 * BOARD_SIZE + 1       /* 展示棋盘的行数 */
#define COL_MAX_SIZE   (15 * BOARD_SIZE + 1) \
                       * CHAR_SIZE + 1          /* 展示棋盘的最大列数 */

#define          RED   "\x1b[31m"
#define        GREEN   "\x1b[32m"
#define       YELLOW   "\x1b[33m"
#define         BLUE   "\x1b[34m"
#define      MAGENTA   "\x1b[35m"
#define         CYAN   "\x1b[36m"
#define         BOLD   "\x1b[01m"
#define    UNDERLINE   "\x1b[04m"
#define        RESET   "\x1b[00m"


typedef enum {
    False,
    True
} boolen;

/* innerBoard 结点类型 */
typedef struct {
    boolen isPassed;      /* 是否已经走过 */
    boolen isCurr;        /* 是否为当前马的位置 */
    int    step;          /* 步数 */
} Point;

/* 坐标 */
typedef struct {
    int x, y;
} Coord;

/* 历史记录 */
typedef struct {
    Coord path[BOARD_SIZE*BOARD_SIZE]; /* 历史路径 */
    int pointer;                       /* 栈指针 */
} History;


/* 按下回车继续，读到 EOF 退出，不接受实际输入 */
extern void Continue(void);

/* 清屏 */
extern void ClearScreen(void);

/* 获取初始位置，写入路径栈 */
extern void GetStart(History *history_ptr);

/* 小睡一会儿 */
extern void SleepForAWhile(unsigned int msec);

/* 刷新历史记录 */
extern void RefreshHistory(History *history_ptr);

/* 打印重要信息 */
extern void PrintInfo(History *history_ptr);

/* 根据历史记录更新心中棋盘 */
extern void
UpdateInnerBoard(History *history_ptr, Point innerBoard[BOARD_SIZE][BOARD_SIZE]);

/* 判断是否结束，是则退出 */
extern void JudgeOver(History *history_ptr);



/* 标题界面 */
extern void Title(void);

/* 初始化一个心中棋盘的空棋盘格局 */
extern void InitInnerBoard(Point innerBoard[BOARD_SIZE][BOARD_SIZE]);

/* 打印棋盘 */
extern void
PrintBoard(Point innerBoard[BOARD_SIZE][BOARD_SIZE], History *history_ptr);



/* 更新 history，包括数组元素和栈指针 */
extern void
GetNextStep(Point innerBoard[BOARD_SIZE][BOARD_SIZE], History *history_ptr);



/* 测试用 */
boolen randomBoolen(void);
int random0To7(void);



#endif /* KTP_H */
