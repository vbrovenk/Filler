/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manhattan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 19:04:10 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/07/28 19:04:15 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static	int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	else
		return (number);
}

static	int	minimal(t_filler *filler, int i, int j)
{
	int x;
	int y;
	int temp;
	int sum;

	y = -1;
	sum = 0;
	while (++y < filler->map_n)
	{
		x = -1;
		while (++x < filler->map_x)
		{
			temp = sum;
			if (filler->tab_man[y][x] == filler->enemy)
				sum = ft_abs(i - y) + ft_abs(j - x);
			if (temp < sum && temp != 0)
				sum = temp;
		}
	}
	return (temp);
}

void		manhatt(t_filler *filler)
{
	int i;
	int j;

	i = -1;
	while (++i < filler->map_n)
	{
		j = -1;
		while (++j < filler->map_x)
		{
			if (filler->map[i][j] == '.')
				filler->tab_man[i][j] = minimal(filler, i, j);
			else if (filler->map[i][j] == 'O')
				filler->tab_man[i][j] = -1;
			else
				filler->tab_man[i][j] = -2;
		}
	}
}
