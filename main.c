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

typedef struct s_point{
	int x;
	int y;
}				t_point;

typedef struct  s_token
{
	int n;
	int x;
}				t_token;

typedef struct  s_filler{
	char 	player;
	int		map_n;
	int 	map_x;
	int 	token_n;
	int 	token_x;


}				t_filler;



void	print_array(int array[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}
}

void	print_array_char(char array[4][4], int n, int x)
{
	printf("\nInput 2d array\n\n");
	for (int i = 0; i < n; i++)
	{
		for(int j = 0; j < x; j++)
			printf("%C ", array[i][j]);
		printf("\n");
	}
	printf("\n=======================\n");
}

int		abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}

t_point	deter_coord(char arr_char[4][4])
{
	t_point point;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arr_char[i][j] == 'X')
			{
				point.x = i;
				point.y = j;
			}
		}
	}
	return (point);
}

int	 **manhet(char arr_char[4][4])
{
	int **array;
	t_point p1;


	int x = -1;
	int y = -1;
	array = malloc(sizeof(int *) * 4);
	while (++x < 4)
		array[x] = malloc(sizeof(int) * 4);

	p1 = deter_coord(arr_char);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arr_char[i][j] == '.')
				array[i][j] = abs(i - p1.x) + abs(j - p1.y);
		}
	}
	// print_array(array);

	return (array);
}

void	fill_token(char **array_token, t_token token, int fd)
{
	int i;
	int j;
	int l;
	char *line;

	i = -1;
	while (++i < token.n)
	{
		get_next_line(fd, &line);
		l = -1;
		j = -1;
		while (++j < token.x)
		{
			array_token[i][j] = line[++l];
		}
	}
	// print_array_char(array_token, token.n, token.x);
}

void	set_token(int **array_manhet, char **array_token, char arr[4][4], t_token token)
{
	int x;
	int y;
	int i;
	int j;

	i = -1;
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			if (arr[x][y] == 'O')
			{
				while (++i < token.n)
				{
					j = -1;
					while (++j < token.x)
					{
						arr[x][y] = array_token[i][j];
						if (y < 4)
							y++;
						else if (x < 4)
						{
							y = 0;
							x++;
						}
					}
				}
			}

		}
	}
	print_array_char(arr, 4, 4);
}

void	get_map_size(int fd, t_filler *filler)
{
	char *line;
	int i;
	int start;
	char **coord;

	i = 0;
	get_next_line(0, &line);
	if (ft_strstr(line, "Plateau"))
	{
		// while (!ft_isdigit(line[i]))
		// 	i++;
		// start = i;
		// while (ft_isdigit(line[i]))
		// 	i++;
		// coord = ft_strsub(line, start, i - start);
		// filler->map_n = ft_atoi(coord);
		// free(coord);
		// i++;
		// start = i;
		// while (ft_isdigit(line[i]))
		// 	i++;
		// coord = ft_strsub(line, start, i - start);
		// filler->map_x = ft_atoi(coord);
		// free(coord);
		coord = ft_strsplit(line, ' ');
		filler->map_n = ft_atoi(coord[1]);
		filler->map_x = ft_atoi(coord[2]);
	}
}

void	get_token_size(int fd, char *line, t_filler *filler)
{
	char	**coord;

	coord = ft_strsplit(line, ' ');
	filler->token_n = ft_atoi(coord[1]); // lines
	filler->token_x = ft_atoi(coord[2]); // columns
}


char	**create_map(int fd, t_filler *filler)
{
	char *line;
	int n;
	char **map;
	int i;

	i = -1;
	map = (char **)malloc(sizeof(char **) * filler->map_n);
	// while (++i < filler->map_n)
	// 	map[i] = (char *)malloc(sizeof(char) * (filler->map_x + 1));
	i = 0;
	while (get_next_line(0, &line) > 0 && !ft_strstr(line, "Piece"))
	{
		if (line[4] == '.')
		{
			map[i] = ft_strsub(line, 4, filler->map_x);
			i++;
		}
	}

	get_token_size(fd, line, filler);
	return (map);
}

int main(int argc, char **argv)
{
	int fd;
	char *line;
	// char **array_token;
	// int  **array_manhet;

	t_token token;

	t_filler *filler;


	// print_array_char(arr , 4, 4);
	// array_manhet = manhet(arr);

	filler = malloc(sizeof(filler));

	fd = open("input.txt", O_WRONLY);
	get_next_line(0, &line);

	line[10] == '1' ? (filler->player = 'X') : (filler->player = 'O');

	get_map_size(fd, filler);  // size of map
	char **map = create_map(fd, filler);

	// for (int j = 0; j < filler->map_n; j++)
	// 	dprintf(fd, "%s\n", map[j]);
	// dprintf(fd, "token_n = %d token_x = %d\n", filler->token_n, filler->token_x);


	// printf("token.n = %d token.x = %d\n", token.n, token.x);

	// int i = -1;
	// int j = -1;
	// array_token = malloc(sizeof(char *) * token.n);
	// while (++i < token.n)
	// 	array_token[i] = malloc(sizeof(char) * (token.x + 1));
	// fill_token(array_token, token, fd);


	// set_token(array_manhet, array_token, arr, token);

	return (0);
}
