#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	is_safe_col_tb(int ***board, int *slot, int *clue_list)
{
	int	y;
	int	max;
	int	visible;
	int	n;

	max = 0;
	visible = 0;
	y = -1;
	n = board[0][0][0];
	while (++y < n)
	{
		if (board[y][slot[n + 3]][n + 1] > max)
		{
			visible++;
			max = board[y][slot[n + 3]][n + 1];
		}
	}
	//if (max == n && (clue_list[slot[n + 3]] - visible) != 0)
	//	return (-1);
	return (clue_list[slot[n + 3]] - visible);
}

int	is_safe_col_bt(int ***board, int *slot, int *clue_list)
{
	int	y;
	int	max;
	int	visible;
	int	n;

	max = 0;
	visible = 0;
	n = board[0][0][0];
	y = n;
	while (--y >= 0)
	{
		if (board[y][slot[n + 3]][n + 1] > max)
		{
			visible++;
			max = board[y][slot[n + 3]][n + 1];
		}
	}
	return (clue_list[slot[n + 3] + n] - visible);
}

int	is_safe_row_lr(int ***board, int *slot, int *clue_list)
{
	int	x;
	int	max;
	int	visible;
	int	n;

	max = 0;
	visible = 0;
	x = -1;
	n = board[0][0][0];
	while (++x < n)
	{
		if (board[slot[n + 2]][x][n + 1] > max)
		{
			visible++;
			max = board[slot[n + 2]][x][n + 1];
		}
	}
	//printf("\n%d %d\n", max, n);
	//if (max == n && (clue_list[slot[n + 2] + 2 * n] - visible) != 0)
	//	return (-1);
	//printf("\nclue: %d\n", clue_list[slot[n + 2] + 2 * n]);
	//printf("\nvisible: %d\n", visible);
	return (clue_list[slot[n + 2] + 2 * n] - visible);
}

int	is_safe_row_rl(int ***board, int *slot, int *clue_list)
{
	int	x;
	int	max;
	int	visible;
	int	n;

	max = 0;
	visible = 0;
	n = board[0][0][0];
	x = n;
	while (--x >= 0)
	{
		if (board[slot[n + 2]][x][n + 1] > max)
		{
			visible++;
			max = board[slot[n + 2]][x][n + 1];
		}
	}
	return (clue_list[slot[n + 2] + 3 * n] - visible);
}
