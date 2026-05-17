#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
typedef struct	s_clue
{
	char	is_col;
	char	v_1;
	char	v_2;
}				t_clue;

typedef struct	s_slot
{
	char	val;
	char	*pos_val;
	int		s_y;
	int		s_x;
	int		s_n;
}				t_slot;
*/
int	is_input_valid(char *str)
{
	char	*str_s;
	int		i;
	int		n;

	str_s = str;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
		if (*str)
		{	
			if  (*str != ' ')
				return (0);
			str++;
		}	
	}
	i = 3;
	while (++i < 10)
	{
		if ((((str - str_s) / 2) + 1) == i * 4)
		{
			n = i;
			i = 0;
			break ;
		}
	}
	if (i)
		return (0);
	return (n);
}

void free_board(int ***board, int n)
{
	int x;
	int y;

	if (!board)
		return ;
	y = -1;
	while (++y < n)
	{
		if (board[y])
		{
			x = -1;
			while (++x < n)
			{
				if (board[y][x])
					free(board[y][x]);
			}
		}
	}
	free(board);
}

/*
void	init_slot(t_slot *slot, int n, int y, int x)
{
	int	i;

	slot -> val = 0;
	slot -> pos_val = (char *)malloc(sizeof(char) * n);
	if (!slot -> pos_val)
		return ;
	i = -1;
	while (++i < n)
		slot -> pos_val[i] = 1;
	slot -> s_y = y;
	slot -> s_x = x;
	slot -> s_n = n;
}*/

/*
t_slot **init_board(int n)
{
	t_slot	**board;
	int x;
	int y;

	board = (t_slot **)malloc(sizeof(t_slot *) * n);
	if (!board)
		return ((void *)0);
	y = -1;
	while (++y < n)
	{
		board[y] = (t_slot*)malloc(sizeof(t_slot) * n);
		if (!board[y])
		{
			free(board);
			return ((void *)0);
		}
		x = -1;
		while (++x < n)
			init_slot(&board[y][x], n, y, x);
		
	}
	return (board);
}*/

int	***init_board(int n)
{
	int	x;
	int	y;
	int	***board;
	int	i;

	board = (int***)malloc(sizeof(int**) * n);
	y = -1;
	while (++y < n)
	{
		board[y] = (int**)malloc(sizeof(int*) * n);
		x = -1;
		while(++x < n)
		{
			board[y][x] = (int*)malloc(sizeof(int) * (n + 4));
			board[y][x][0] = n;
			i = 0;
			while (++i <= n)
				board[y][x][i] = 1;
			board[y][x][n + 1] = 0;
			board[y][x][n + 2] = y;
			board[y][x][n + 3] = x;
		}
	}
	return (board);
}


int	*make_clues(char *str, int n)
{
	int	*clue_list;
	int		i;

	clue_list = (int *)malloc(sizeof(int) * n * 4);
	i = 0;
	while (i < 4 * n)
	{
		clue_list[i] = (int)(*str - '0');
		str += 2;
		i++;
	}
	return (clue_list);
}
/*
t_clue	*make_clues(char *str, int n)
{
	t_clue	*clue_list;
	int		i;

	clue_list = (t_clue *)malloc(sizeof(t_clue) * n * 2);
	i = 0;
	while (i < 2 * n)
	{
		if (i < n)
			clue_list[i].v_1 = *str - '0';
		else
			clue_list[i - n].v_2 = *str - '0';
		str += 2;
		i++;
	}
	while (i < 4 * n)
	{
		if (i < 3 * n)
			clue_list[i - n].v_1 = *str - '0';
		else
			clue_list[i - 2 * n].v_2 = *str - '0';
		str += 2;
		i++;
	}
	return (clue_list);
}*/

void	put_val(int *slot, int val, int n)
{
	int	i;

	if (slot[n + 1])
		return ;
	slot[n + 1] = val;
	i = 0;
	while (++i <= n)
	{
		if (i != val)
			slot[i] = 0;
	}
}

/*
void	init_clue_board_1(int *clue_list, char ***board, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (clue_list[i].v_1 == 1)
				put_val(&board[0][i], (char)n, n);
		if (clue_list[i].v_2 == 1)
				put_val(&board[n - 1][i], (char)n, n);
	}
	i--;
	while (++i < 2 * n)
	{
		if (clue_list[i].v_1 == 1)
				put_val(&board[i - n][0], (char)n, n);
		if (clue_list[i].v_2 == 1)
				put_val(&board[i - n][n - 1], (char)n, n);
	}
}*/

void	init_clue_board_1(int *clue_list, int ***board, int n)
{
	int	i;

	
	i = -1;
	while (++i < n)
	{
		if (clue_list[i] == 1)
				put_val(board[0][i], n, n);
	}
	i--;
	while (++i < 2 * n)
	{
		if (clue_list[i] == 1)
				put_val(board[n - 1][i - n], n, n);
	}
	i--;
	while (++i < 3 * n)
	{
		if (clue_list[i] == 1)
				put_val(board[i - 2 * n][0], n, n);
	}
	i--;
	while (++i < 4 * n)
	{
		if (clue_list[i] == 1)
				put_val(board[i - 3 * n][n - 1], n, n);
	}
}

void	init_clue_board_n(int *clue_list, int ***board, int n)
{
	int	i;
	int k;

	i = -1;
	while (++i < n)
	{
		if (clue_list[i] == n)
		{
			k = -1;
			while (++k < n)
				put_val(board[k][i], k + 1, n);
		}
	}
	i--;
	while (++i < 2 * n)
	{
		if (clue_list[i] == n)
		{
			k = n;
			while (--k > 0)
				put_val(board[k][i - n], n - k, n);
		}
	}
	i--;
	while (++i < 3 * n)
	{
		if (clue_list[i] == n)
		{
			write(1, "here", 4);
			k = -1;
			while (++k < n)
				put_val(board[i - 2 * n][k], k + 1, n);
		}
	}
	i--;
	while (++i < 4 * n)
	{
		if (clue_list[i] == n)
		{
			k = n;
			while (--k > 0)
				put_val(board[i - 3 * n][k], n - k, n);
		}
	}
}


void	rem_pos_val(int *slot, int min, int max)
{
	if (slot[slot[0] + 1])
		return ;
	while (min <= max)
	{
		slot[min] = 0;
		min++;
	}
}

void	init_clue_board_1_n(int *clue_list, int ***board, int n)
{
	int	i;
	int	k;

	i = -1;
	while (++i < n)
	{
		if (clue_list[i] > 1 && clue_list[i] < n)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[k][i], n - clue_list[i] + 2 + k, n);
		}
	}
	i--;
	while (++i < 2 * n)
	{
		if (clue_list[i] > 1 && clue_list[i] < n)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[n - 1 - k][i - n], n - clue_list[i] + 2 + k, n);
		}
	}
	i--;
	while (++i < 3 * n)
	{
		if (clue_list[i] > 1 && clue_list[i] < n)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[i - 2 * n][k], n - clue_list[i] + 2 + k, n);
		}
	}
	i--;
	while (++i < 4 * n)
	{
		if (clue_list[i] > 1 && clue_list[i] < n)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[i - 3 * n][n - 1 - k], n - clue_list[i] + 2 + k,n);
		}
	}
}

void	update_pos_row_col(int ***board, int y, int x, int val)
{
	int	i;
	int	n;

	i = -1;
	n = board[0][0][0];
	while (++i < n)
	{
		if (i != x)
			board[y][i][val] = 0;
	}
	i = -1;
	while (++i < n)
	{
		if (i != y)
			board[i][x][val] = 0;
	}
}

void	update_pos(int ***board, int n)
{
	int	x;
	int	y;

	y = -1;
	while (++y < n)
	{
		x = -1;
		while(++x < n)
		{
			if (board[y][x][n + 1])
			{
				update_pos_row_col(board, y, x, board[y][x][n + 1]);
			}
		}
	}	
}

int	is_safe_col_tb(int ***board, int *slot, int *clue_list)
{
	int	y;
	int	max;
	int visible;
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
	int visible;
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
	int visible;
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
	int visible;
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

int	is_repeat(int ***board, int *slot)
{
	int x;
	int	y;
	int	n;

	x = -1;
	n = board[0][0][0];
	while (++x < slot[0])
	{
		if (x != slot[n + 3] && board[slot[n + 2]][x][n + 1] == slot[n + 1])
			return (0);
	}
	y = -1;
	while (++y < slot[0])
	{
		if (y != slot[n + 2] && board[y][slot[n + 3]][n + 1] == slot[n + 1])
			return (0);
	}
	return (1);
}

int	is_safe(int ***board, int *slot, int *clue_list)
{
	int	i;
	int count;
	int	n;

	n = board[0][0][0];
	//printf("\nn=%d\n", n);
	if (!is_repeat(board, slot))
		return (0);
	//printf("-1-");
	i = -1;
	count = 0;
	while (++i < n)
	{
		//printf("y=%d, x=%d, val=%d\n", slot[n+2], i, board[slot[n + 2]][i][n +1]);
		if (board[slot[n + 2]][i][n + 1] != 0)
			count++;
	}
	//printf("\n.%d.\n", count);
	if (count == slot[0])
	{
		if (is_safe_row_lr(board, slot, clue_list))
			return (0);
		//printf("-2-");
		if (is_safe_row_rl(board, slot, clue_list))
			return (0);
		//printf("-3-");
	}
	i = -1;
	count = 0;
	while (++i < n)
	{
		if (board[i][slot[n + 3]][n + 1])
			count++;
	}
	printf("\n.count %d.\n", count);
	if (count == slot[0])
	{
		if (is_safe_col_tb(board, slot, clue_list))
			return (0);
		//printf("-4-");
		if (is_safe_col_bt(board, slot, clue_list))
			return (0);
		//printf("-5-");
	}
	//printf("\nOK\n");
	return (1);
}

void	print_board(int ***board, int n)
{
	int	x;
	int	y;
	char c;

	y = -1;
	while (++y < n)
	{
		x = -1;
		while (++x < n)
		{
			c = '0' + board[y][x][n + 1];
			write(1, &c, 1);
			if (x != n - 1)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}	
}

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
	while(++val <= n)
	{
		if (board[y][x][val])
		{
			board[y][x][n + 1] = val;
			if (is_safe(board, board[y][x], clue_list))
			{
				printf("\nassigning %d to slot %d, %d \n", val, y + 1, x + 1);
				if (solve(board, clue_list, y, x + 1))
					return(1);
			}
			board[y][x][n + 1] = 0;
		}
	}
	return(0);
}

int	main(int argc, char **argv)
{
	int		n;
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
