/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:02:59 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/07/08 17:03:01 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

typedef struct  s_filler{
	char 	player;
	char	enemy;

	char 	**map;
	int		map_n;
	int 	map_x;
	
	char	**token_map;
	int 	token_n;
	int 	token_x;

	int		my_player_n;
	int 	my_player_x;

	int		enemy_n;
	int		enemy_x;


}				t_filler;


#endif 
