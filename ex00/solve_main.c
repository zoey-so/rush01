#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		is_input_valid(char *str);

void	free_board(int ***board, int n);

int		***init_board(int n);

int		*make_clues(char *str, int n);

void	init_clue_board_1(int *clue_list, int ***board, int n);

void	init_clue_board_n(int *clue_list, int ***board, int n);

void	rem_pos_val(int *slot, int min, int max);

void	init_clue_board_1_n(int *clue_list, int ***board, int n);

void	update_pos_row_col(int ***board, int y, int x, int val);

void	update_pos(int ***board, int n);

int		is_safe_col_tb(int ***board, int *slot, int *clue_list);

int		is_safe_col_bt(int ***board, int *slot, int *clue_list);

int		is_safe_row_lr(int ***board, int *slot, int *clue_list);

int		is_safe_row_rl(int ***board, int *slot, int *clue_list);

int		is_repeat(int ***board, int *slot);

int		is_safe(int ***board, int *slot, int *clue_list);

void	print_board(int ***board, int n);

int	solve(int ***board, int *clue_list, int y, int x)
{
	int	val;
	int	n;

	n = board[0][0][0];
	printf("%d", n);
	if (y == n)
	{
		print_board(board, n);
		return (1);
	}
	if (x >= n)
		return (solve(board, clue_list, y + 1, 0));
	if (board[y][x][n + 1])
		return (solve(board, clue_list, y, x + 1));
	val = 0;
	while (++val <= n)
	{
		if (board[y][x][val])
		{
			board[y][x][n + 1] = val;
			if (is_safe(board, board[y][x], clue_list))
			{
				printf("\nassigning %d to slot %d, %d \n", val, y + 1, x + 1);
				if (solve(board, clue_list, y, x + 1))
					return (1);
			}
			board[y][x][n + 1] = 0;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	n;
	int	***board;
	int	*clue_list;

	if (argc == 2)
	{
		n = (is_input_valid(argv[1]));
		if (n)
		{
			//printf("%d", n);
			board = init_board(n);
			for (int y = 0; y < n; y++)
			{
				for(int x = 0; x < n; x++)
					printf(" %d ", (int)board[y][x][n + 1]);
				printf("\n");
			}
			clue_list = make_clues(argv[1], n);
			for (int i = 0; i < 4 * n; i++)
				printf("%d ", clue_list[i]);
			//printf("\n");
			/*
			int i = -1;
			while (++i < n)
			{
				printf("col%dtop: %d\n", i, (int)clue_list[i]);
				printf("col%dbottom: %d\n", i, (int)clue_list[i + n]);
			}
			i--;
			while (++i < 2 * n)
			{
				printf("row%dleft: %d\n", i - n, (int)clue_list[i + 2 * n]);
				printf("rpw%dright: %d\n", i - n, (int)clue_list[i + 3 * n]);
			}
			*/
			init_clue_board_n(clue_list, board, n);
			init_clue_board_1(clue_list, board, n);
			
			for (int y = 0; y < n; y++)
			{
				for(int x = 0; x < n; x++)
					printf(" %d ", (int)board[y][x][n + 1]);
				printf("\n");
			}
			
			
			init_clue_board_1_n(clue_list, board, n);
			update_pos(board, n);

			for (int y = 0; y < n; y++)
			{
				for(int x = 0; x < n; x++)
				{
					printf("slot %d %d possible: ", y + 1, x + 1);
					for(int i = 0; i <  n; i++)
					{
						if (board[y][x][i + 1])
							printf("%d ", i + 1);
					}
					printf("\n");
				}
			}
			solve(board, clue_list, 0, 0);
			free_board(board, n);
		}
		else
			printf("Error");
	}
	return (0);
}
