/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:38:49 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/07/31 17:38:55 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_map_size(t_filler *filler)
{
	char	*line;
	char	**coord;

	get_next_line(0, &line);
	if (line == NULL)
		return (-1);
	if (ft_strstr(line, "Plateau"))
	{
		coord = ft_strsplit(line, ' ');
		ft_strdel(&coord[0]);
		filler->map_n = ft_atoi(coord[1]);
		ft_strdel(&coord[1]);
		filler->map_x = ft_atoi(coord[2]);
		ft_strdel(&coord[2]);
		free(coord);
	}
	ft_strdel(&line);
	return (1);
}

void	get_token_size(t_filler *filler)
{
	char	**coord;
	char	*line;

	get_next_line(0, &line);
	if (ft_strstr(line, "Piece"))
	{
		coord = ft_strsplit(line, ' ');
		ft_strdel(&coord[0]);
		filler->token_n = ft_atoi(coord[1]);
		ft_strdel(&coord[1]);
		filler->token_x = ft_atoi(coord[2]);
		ft_strdel(&coord[2]);
		free(coord);
	}
	ft_strdel(&line);
}

void	free_token(t_filler *filler)
{
	int i;

	i = 0;
	while (i < filler->token_n)
	{
		free(filler->token_map[i]);
		i++;
	}
	free(filler->token_map);
}

void	free_map_tab(t_filler *filler)
{
	int i;

	i = 0;
	while (i < filler->map_n)
	{
		free(filler->map[i]);
		free(filler->tab_man[i]);
		i++;
	}
	free(filler->map);
	free(filler->tab_man);
}
