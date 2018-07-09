/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 13:35:36 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/04/21 14:36:32 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 85

typedef struct		s_gnl
{
	void			*str;
	size_t			str_size;
	struct s_gnl	*next;
	int				fd;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
