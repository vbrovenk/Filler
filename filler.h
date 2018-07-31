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

typedef	struct	s_filler{
	int		player;
	int		enemy;
	char	**map;
	int		map_n;
	int		map_x;
	char	**token_map;
	int		token_n;
	int		token_x;
	int		my_player_n;
	int		my_player_x;
	int		**tab_man;

}				t_filler;

int				get_map_size(t_filler *filler);
void			get_token_size(t_filler *filler);
void			manhatt(t_filler *filler);
void			first_create(t_filler *filler);
void			create_map(t_filler *filler);
void			create_token(t_filler *filler);
void			free_token(t_filler *filler);
void			free_map_tab(t_filler *filler);
void			coordinates(t_filler *filler);

#endif
