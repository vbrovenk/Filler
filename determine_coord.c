/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_coord.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:04:48 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/07/31 19:25:56 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static	int	find_sum(t_filler *filler, int i, int j, int sum)
{
	int y;
	int x;
	int cell;
	int enemy;

	cell = 0;
	enemy = 0;
	y = -1;
	while (++y < filler->token_n && (x = -1))
	{
		while (++x < filler->token_x)
			if (filler->token_map[y][x] == '*')
			{
				if ((y + i) < 0 || (y + i) >= filler->map_n
					|| (x + j) < 0 || (x + j) >= filler->map_x)
					return (0);
				if (filler->tab_man[y + i][x + j] == filler->player)
					cell++;
				if (filler->tab_man[y + i][x + j] == filler->enemy)
					enemy++;
				sum += filler->tab_man[y + i][x + j];
			}
	}
	return ((enemy == 0 && cell == 1) ? sum : 0);
}

void		coordinates(t_filler *filler)
{
	int i;
	int j;
	int sum;
	int manhattan;

	manhattan = filler->map_n * filler->map_x;
	i = -filler->token_n;
	while (++i < filler->map_n + filler->token_n && (j = -filler->token_x))
	{
		while (++j < filler->map_x + filler->token_x)
		{
			sum = 0;
			sum = find_sum(filler, i, j, sum);
			if (sum != 0 && sum < manhattan)
			{
				filler->my_player_n = i;
				filler->my_player_x = j;
				manhattan = sum;
			}
		}
	}
	ft_putnbr(filler->my_player_n);
	ft_putchar(' ');
	ft_putnbr(filler->my_player_x);
	ft_putchar('\n');
}
