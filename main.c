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

int main(int argc, char **argv)
{
	int fd;
	char *line;
	char **array_token;
	int  **array_manhet;

	t_token token;

	char arr[4][4] = {
		{'O','.','.','.'},
		{'.','.','.','.'},
		{'.','.','X','.'},
		{'.','.','.','.'},
	};

	// print_array_char(arr , 4, 4);
	array_manhet = manhet(arr);


	fd = open("token.txt", O_RDONLY);
	get_next_line(fd, &line);
	token.n = ft_atoi(&line[6]); // lines
	token.x = ft_atoi(&line[8]); // columns
	
	// printf("token.n = %d token.x = %d\n", token.n, token.x);

	int i = -1;
	int j = -1;
	array_token = malloc(sizeof(char *) * token.n);
	while (++i < token.n)
		array_token[i] = malloc(sizeof(char) * (token.x + 1));
	fill_token(array_token, token, fd);


	set_token(array_manhet, array_token, arr, token);

	return (0);
}
