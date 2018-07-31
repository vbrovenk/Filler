/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:18:45 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/07/31 17:18:48 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	first_create(t_filler *filler)
{
	int i;

	filler->map = (char **)malloc(sizeof(char *) * filler->map_n);
	filler->tab_man = (int **)malloc(sizeof(int *) * filler->map_n);
	i = 0;
	while (i < filler->map_n)
	{
		filler->map[i] = (char *)malloc(sizeof(char) * (filler->map_x + 1));
		filler->tab_man[i] = (int *)malloc(sizeof(int) * filler->map_x);
		i++;
	}
}

void	create_map(t_filler *filler)
{
	char	*line;
	int		i;

	i = -1;
	get_next_line(0, &line);
	ft_strdel(&line);
	while (++i < filler->map_n)
	{
		get_next_line(0, &line);
		ft_strcpy(filler->map[i], &line[4]);
		ft_strdel(&line);
	}
}

void	create_token(t_filler *filler)
{
	char	*line;
	int		i;

	i = -1;
	filler->token_map = (char **)malloc(sizeof(char *) * filler->token_n);
	while (++i < filler->token_n)
	{
		get_next_line(0, &line);
		filler->token_map[i] = ft_strdup(line);
		ft_strdel(&line);
	}
}
