/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:36:38 by smilch            #+#    #+#             */
/*   Updated: 2026/05/17 22:36:41 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		while (++x < n)
		{
			if (board[y][x][n + 1])
			{
				update_pos_row_col(board, y, x, board[y][x][n + 1]);
			}
		}
	}
}

int	is_repeat(int ***board, int *slot)
{
	int	x;
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
