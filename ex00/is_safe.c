/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_safe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:36:08 by smilch            #+#    #+#             */
/*   Updated: 2026/05/17 22:36:11 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	is_safe_col_tb(int ***board, int *slot, int *clue_list);

int	is_safe_col_bt(int ***board, int *slot, int *clue_list);

int	is_safe_row_lr(int ***board, int *slot, int *clue_list);
int	is_safe_row_rl(int ***board, int *slot, int *clue_list);

int	is_repeat(int ***board, int *slot);

int	count_if_last_x(int ***board, int *slot)
{
	int	i;
	int	count;
	int	n;

	n = board[0][0][0];
	i = -1;
	count = 0;
	while (++i < n)
	{
		if (board[slot[n + 2]][i][n + 1] != 0)
			count++;
	}
	return (count);
}

int	count_if_last_y(int ***board, int *slot)
{
	int	i;
	int	count;
	int	n;

	n = board[0][0][0];
	i = -1;
	count = 0;
	while (++i < n)
	{
		if (board[i][slot[n + 3]][n + 1])
			count++;
	}
	return (count);
}

int	is_safe(int ***board, int *slot, int *clue_list)
{
	int	count;

	if (!is_repeat(board, slot))
		return (0);
	count = count_if_last_x(board, slot);
	if (count == slot[0])
	{
		if (is_safe_row_lr(board, slot, clue_list))
			return (0);
		if (is_safe_row_rl(board, slot, clue_list))
			return (0);
	}
	count = count_if_last_y(board, slot);
	if (count == slot[0])
	{
		if (is_safe_col_tb(board, slot, clue_list))
			return (0);
		if (is_safe_col_bt(board, slot, clue_list))
			return (0);
	}
	return (1);
}

void	print_board(int ***board, int n)
{
	int		x;
	int		y;
	char	c;

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
