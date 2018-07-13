/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:54:53 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/04/22 17:58:59 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "filler.h"
#include "filler.h"


typedef struct s_point{
	int x;
	int y;
}				t_point;

typedef struct  s_token
{
	int n;
	int x;
}				t_token;


void	get_map_size(int fd, t_filler *filler)
{
	char *line;
	char **coord;

	get_next_line(fd, &line);
	if (ft_strstr(line, "Plateau"))
	{
		coord = ft_strsplit(line, ' ');
		filler->map_n = ft_atoi(coord[1]);
		filler->map_x = ft_atoi(coord[2]);
	}
}

void	get_token_size(char *line, t_filler *filler)
{
	char	**coord;

	coord = ft_strsplit(line, ' ');
	filler->token_n = ft_atoi(coord[1]); // lines
	filler->token_x = ft_atoi(coord[2]); // columns
	// dprintf(2 , "temp5 \n");

}

int		minimal(t_filler *filler, int i, int j)
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
			if (filler->map[y][x] == 'X')
			{
				sum = abs(i - y) + abs(j - x);
			}
			if (temp < sum && temp != 0)
				sum = temp;
		}
	}
	return (temp);
}

int **manhatt(t_filler *filler)
{
	int i;
	int j;
	int **tab;

	tab = malloc(sizeof(int *) * filler->map_n);

	i = -1;
	while (++i < filler->map_n && (j = -1))
	{
		tab[i] = malloc(sizeof(int) * filler->map_x);
		while (++j < filler->map_x)
		{
			if (filler->map[i][j] == '.')
			{
				tab[i][j] = minimal(filler, i, j);
			}
			else if (filler->map[i][j] == 'O')
				tab[i][j] = -1;
			else
				tab[i][j] = -2;
		}
	}
	return (tab);
}


void 	create_token(int fd, t_filler *filler)
{
	char *line;
	int i;

	i = -1;
	// dprintf(2, "token_n = %d\n", filler->token_n);
	filler->token_map = (char **)malloc(sizeof(char *) * filler->token_n);
	while (++i < filler->token_n)
	{
		get_next_line(fd, &line);
		filler->token_map[i] = ft_strdup(line);
	}
}

int 	try_insert(t_filler *filler, int i, int j)
{
	if (i + filler->token_n > filler->map_n)
		return (0);
	else if (j + filler->token_x > filler->map_x)
		return (0);
	else
		return (1);
}

void	push_token(t_filler *filler, int i, int j, int **tab)
{
	int x;
	int y;

	int sum;
	int cell;

	sum = 0;
	x = 0;
	while (x < filler->token_n)
	{
		y = 0;
		while (y < filler->token_x)
		{
			if (filler->token_map[x][y] == '*')
				sum += tab[i][j];
			if (tab[i][j] == -1)
				cell++;
			y++;
		}
		x++;
	}
}

void	coordinates(t_filler *filler, int **tab)
{
	int i;
	int j;

	int sum;
	int temp_sum;
	int cell;

	int x;
	int y;

	int xx = 0;
	int yy = 0;

	i = -1;
	temp_sum = filler->map_n * filler->map_x;
	while (++i < filler->map_n && (j = -1))
		while (++j < filler->map_x)
		{
			x = -1;
			cell = 0;
			sum = 0;
			while (++x < filler->token_n && (y = -1))
				while (++y < filler->token_x)
				{
					if (filler->token_map[x][y] == '*')
					{
						sum += tab[i][j];
					}
				}
			if (sum < temp_sum)
			{
				filler->my_player_n = i;
				filler->my_player_x = j;
				temp_sum = sum;
			}
		}

	ft_putnbr(filler->my_player_n);
	ft_putchar(' ');
	ft_putnbr(filler->my_player_x);
}


void	create_map(int fd, t_filler *filler)
{
	char *line;
	int i;

	i = -1;
	dprintf(2, "%d %d \n", filler->map_n, filler->map_x);
	filler->map = (char **)malloc(sizeof(char *) * filler->map_n);
	while (++i < filler->map_n)
	{
		filler->map[i] = (char *)malloc(sizeof(char) * (filler->map_x + 1));
	}
	
	i = -1;
	while (get_next_line(fd, &line) && !ft_strstr(line, "Piece"))
	{
		if (++i < filler->map_n)
			filler->map[i] = &line[4];
	}
	get_token_size(line, filler);
}

int main(int argc, char **argv)
{
	char *line;


	t_filler *filler;

	filler = malloc(sizeof(filler));

	// line[10] == '1' ? (filler->player = 'O') : (filler->player = 'X');
	get_next_line(0, &line);
	if (ft_strstr(line, "p1"))
		filler->player = 'O';
	else
		filler->player = 'X';
	if (filler->player == 'O')
		filler->enemy = 'X';
	else
		filler->enemy = 'O';
	// dprintf(2 , "temp1 \n");
	int k = 0;

	int fd = open("piece", O_RDONLY);
	get_map_size(fd,filler);  // size of map
	// dprintf(2 , "temp2 \n");
	create_map(fd, filler);
	// dprintf(2 , "temp6 \n");
	create_token(fd, filler);
	// dprintf(2 , "temp7 \n");
	
	// if (filler->my_player_n == 0 && filler->my_player_x == 0)
	// 	determine_coord(filler);

	// int **tab = manhatt(filler);

	// for (int y = 0; y < filler->map_n; y++)
	// {
	// 	for (int x = 0; x < filler->map_x; x++)
	// 	{
	// 		if (ft_countdigits(tab[y][x]) == 2)
	// 			dprintf(2, "%d ", tab[y][x]);
	// 		else
	// 			dprintf(2, "%d  ", tab[y][x]);
	// 	}
	// 	dprintf(2, "\n");
	// }
	// coordinates(filler, tab);
		
	// ft_putchar('\n');
	// ft_putstr("9 2");

	return (0);
}
