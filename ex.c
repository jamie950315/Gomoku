//棋盘可分为三部分，第一行，最后一行，中间行
//用i代表行，j代表列
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>   
#define MAX_COL 15
void draw_chessboardn(int row, int col, int chessboard[][MAX_COL]) {
	for (int i = 0; i < row ; i++) {
		if (i == 0) {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					draw_chessman(chessboard[i][j], "┌ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┐");
				else
					draw_chessman(chessboard[i][j], "┬ ");
			}
			printf("\n");//第一行┌┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┐
		} else if (i == 14) {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					draw_chessman(chessboard[i][j], "└ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┘ ");
				else
					draw_chessman(chessboard[i][j], "┴ ");
			}
			printf("\n");//最后一行└┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┘
		} else {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					draw_chessman(chessboard[i][j], "├ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┤");
				else
					draw_chessman(chessboard[i][j], "┼ ");
			}
			printf("\n");//其他行├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
		}
	}
}
 