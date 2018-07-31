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

#include "filler.h"

void	main_loop(t_filler *filler)
{
	int ret;

	ret = 0;
	free_token(filler);
	while (1)
	{
		ret = get_map_size(filler);
		if (ret == -1)
			break ;
		create_map(filler);
		get_token_size(filler);
		create_token(filler);
		manhatt(filler);
		filler->my_player_n = 0;
		filler->my_player_x = 0;
		coordinates(filler);
		free_token(filler);
	}
	free_map_tab(filler);
}

int		main(int argc, char **argv)
{
	char		*line;
	t_filler	*filler;

	filler = (t_filler *)malloc(sizeof(t_filler));
	get_next_line(0, &line);
	if (ft_strstr(line, "p1"))
		filler->player = -1;
	else
		filler->player = -2;
	if (filler->player == -1)
		filler->enemy = -2;
	else
		filler->enemy = -1;
	ft_strdel(&line);
	get_map_size(filler);
	first_create(filler);
	create_map(filler);
	get_token_size(filler);
	create_token(filler);
	manhatt(filler);
	coordinates(filler);
	main_loop(filler);
	return (0);
}
