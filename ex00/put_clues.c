void	put_val(int *slot, int val, int n);
void	rem_pos_val(int *slot, int min, int max);

void	init_clue_board_1(int *clue_list, int ***board, int n)
{
	int	i;

	i = -1;
	while (++i < n * 4)
	{
		if (clue_list[i] == 1 && i / n == 0)
			put_val(board[0][i], n, n);
		if (clue_list[i] == 1 && i / n == 1)
			put_val(board[n - 1][i - n], n, n);
		if (clue_list[i] == 1 && i / n == 2)
			put_val(board[i - 2 * n][0], n, n);
		if (clue_list[i] == 1 && i / n == 3)
			put_val(board[i - 3 * n][n - 1], n, n);
	}
}

void	init_clue_board_n_pt2(int *clue_list, int ***board, int n)
{
	int	i;
	int	k;

	i = 2 * n - 1;
	while (++i < 4 * n)
	{
		if (clue_list[i] == n && i / n == 2)
		{
			k = -1;
			while (++k < n)
				put_val(board[i - 2 * n][k], k + 1, n);
		}
		if (clue_list[i] == n && i / n == 3)
		{
			k = n;
			while (--k > 0)
				put_val(board[i - 3 * n][k], n - k, n);
		}
	}
}

void	init_clue_board_n(int *clue_list, int ***board, int n)
{
	int	i;
	int	k;

	i = -1;
	while (++i < 2 * n)
	{
		if (clue_list[i] == n && i / n == 0)
		{
			k = -1;
			while (++k < n)
				put_val(board[k][i], k + 1, n);
		}
		if (clue_list[i] == n && i / n == 1)
		{
			k = n;
			while (--k > 0)
				put_val(board[k][i - n], n - k, n);
		}
	}
	init_clue_board_n_pt2(clue_list, board, n);
}

void	init_clue_board_1_n_pt2(int *clue_list, int ***board, int n)
{
	int	i;
	int	k;

	i = 2 * n - 1;
	while (++i < 4 * n)
	{
		if (clue_list[i] > 1 && clue_list[i] < n && i / n == 2)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[i - 2 * n][k], n - clue_list[i] + 2 + k, n);
		}
		if (clue_list[i] > 1 && clue_list[i] < n && i / n == 3)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[i - 3 * n][n - 1 - k],
					n - clue_list[i] + 2 + k, n);
		}
	}
}

void	init_clue_board_1_n(int *clue_list, int ***board, int n)
{
	int	i;
	int	k;

	i = -1;
	while (++i < 2 * n)
	{
		if (clue_list[i] > 1 && clue_list[i] < n && i / n == 0)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[k][i], n - clue_list[i] + 2 + k, n);
		}
		if (clue_list[i] > 1 && clue_list[i] < n && i / n == 1)
		{
			k = -1;
			while ((++k - clue_list[i] + 2) <= 0)
				rem_pos_val(board[n - 1 - k][i - n],
					n - clue_list[i] + 2 + k, n);
		}
	}
	init_clue_board_1_n_pt2(clue_list, board, n);
}
