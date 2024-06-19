/*
** {==========================================================================
** 算法
** ===========================================================================
*/

#include "KTP.h"
#include <time.h> /* 测试用 */
#include <stdlib.h> /* 测试用 */

int dir[8][2] = { {2,-1},{-2,-1},{-2,1},{2,1},{1,-2},{-1,-2},{-1,2},{1,2}};


int valid(int x, int y,Point innerBoard[BOARD_SIZE][BOARD_SIZE]);
void getNext(int x, int y, int* next,Point innerBoard[BOARD_SIZE][BOARD_SIZE]);
void getSeq(int* next, int* seq);
void push(int x, int y, History* history_ptr);
void pop(History* history_ptr);

/* 更新 history，包括数组元素和栈指针 */
void
GetNextStep(Point innerBoard[BOARD_SIZE][BOARD_SIZE], History* history_ptr)
{
	int x = history_ptr->path[history_ptr->pointer].x;
	int y = history_ptr->path[history_ptr->pointer].y;

	int next[8] = { 0,0,0,0,0,0,0,0 };
	getNext(x, y, next,innerBoard);
	int seq[8] = { 0,1,2,3,4,5,6,7 };
	getSeq(next, seq);

	for (int i =0; i < 8; i++)
	{
		int tx = x + dir[seq[i]][0];
		int ty = y + dir[seq[i]][1];
		if (valid(tx, ty,innerBoard))
		{
			push(tx, ty, history_ptr);
			break;
		}
	}
}

int valid(int x, int y,Point innerBoard[BOARD_SIZE][BOARD_SIZE])
{
	return x >= 0 && x <8 && y >= 0 && y < 8 && (innerBoard[x][y].isPassed == 0);
}

//分别得到如果走向周围的8个点，那么将会有多少个下一步
void getNext(int x, int y, int* next,Point innerBoard[BOARD_SIZE][BOARD_SIZE])
{
	for (int i = 0; i < 8; i++)
	{
		int tx = x + dir[i][0];
		int ty = y + dir[i][1];
		if (valid(tx, ty, innerBoard))
		{
			for (int j = 0; j < 8; j++)
			{
				int ttx = tx + dir[j][0];
				int tty = ty + dir[j][1];
				if (valid(ttx, tty,innerBoard))
				{
					next[i]++;
				}
			}
		}
	}
}

//由贪心算法，我们要给next数组进行非递减排序
//并将具体方向对应地编号写到seq数组中
//例如next[3] = {5, 8, 2}
//那么seq [3] = {2, 0, 1}
void getSeq(int* next, int* seq)
{
	int n[8];
	for (int i = 0; i < 8; i++) {
		n[i] = next[i];
	}
		
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7 - i; j++)
		{
			if (n[j] > n[j + 1])
			{
				int t = n[j];
				n[j] = n[j + 1];
				n[j + 1] = t;

				t = seq[j];
				seq[j] = seq[j + 1];
				seq[j + 1] = t;
			}
		}
	}
}

//入栈
void push(int x, int y, History* history_ptr){
	history_ptr->pointer++;
	history_ptr->path[history_ptr->pointer].x = x;
	history_ptr->path[history_ptr->pointer].y = y;
}

//出栈
void pop(History* history_ptr)
{
	history_ptr->path[history_ptr->pointer].x = 0;
	history_ptr->path[history_ptr->pointer].y = 0;
	history_ptr->pointer--;
}

