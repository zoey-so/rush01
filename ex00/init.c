/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:35:40 by smilch            #+#    #+#             */
/*   Updated: 2026/05/17 22:59:04 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	is_input_valid(char *str)
{
	char	*str_s;
	int		n;

	str_s = str;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
		if (*str)
		{
			if (*str != ' ')
				return (0);
			str++;
		}
	}
	if ((((str - str_s) / 2) + 1) % 4 != 0)
		return (0);
	n = ((((str - str_s) / 2) + 1) / 4);
	if (n < 1 || n > 9)
		return (0);
	return (n);
}

void	free_board(int ***board, int n)
{
	int	x;
	int	y;

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

int	***init_board(int n)
{
	int	x;
	int	y;
	int	***board;
	int	i;

	board = (int ***)malloc(sizeof(int **) * n);
	y = -1;
	while (++y < n)
	{
		board[y] = (int **)malloc(sizeof(int *) * n);
		x = -1;
		while (++x < n)
		{
			board[y][x] = (int *)malloc(sizeof(int) * (n + 4));
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
	int	i;

	clue_list = (int *)malloc(sizeof(int) * (n * 4 + 1));
	i = 0;
	while (i < 4 * n)
	{
		clue_list[i] = (int)(*str - '0');
		str += 2;
		i++;
	}
	clue_list[i] = 0;
	return (clue_list);
}
