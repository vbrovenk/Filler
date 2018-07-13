/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 13:36:39 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/04/15 13:36:41 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*find_fd(int fd, t_gnl **head)
{
	t_gnl *elem;

	elem = *head;
	while (elem && elem->fd != fd)
		elem = elem->next;
	return (elem);
}

static int		find_line(char *buff, t_gnl **head, int fd)
{
	t_gnl	*elem;
	char	*temp;

	elem = find_fd(fd, head);
	if (elem == NULL)
	{
		if (!(elem = (t_gnl *)ft_lstnew((void *)buff, ft_strlen(buff) + 1)))
			return (-1);
		elem->fd = fd;
		ft_lstadd_back((t_list **)head, (t_list *)elem);
	}
	else
	{
		if (!(temp = ft_strjoin((char *)elem->str, buff)))
			return (-1);
		free(elem->str);
		elem->str = temp;
		elem->str_size = ft_strlen(temp) + 1;
	}
	if (ft_strchr(elem->str, '\n') != NULL)
		return (1);
	return (0);
}

static char		*get_str(t_gnl **head, int fd)
{
	char	*start;
	t_gnl	*elem;

	elem = find_fd(fd, head);
	if (!(start = ft_strdup((char *)elem->str)))
		return (NULL);
	free(elem->str);
	elem->str = NULL;
	elem->str_size = 0;
	return (start);
}

static char		*get_substr(t_gnl **head, int fd)
{
	char	*start;
	char	*end;
	t_gnl	*elem;
	char	*temp;

	elem = find_fd(fd, head);
	if (elem == NULL)
		return (NULL);
	if ((end = ft_strchr(elem->str, '\n')) != NULL)
	{
		if (!(start = ft_strsub((char *)elem->str, 0,
			elem->str_size - ft_strlen(++end) - 2)))
			return (NULL);
		temp = elem->str;
		if (ft_strlen(end) == 0)
			elem->str = NULL;
		else
			elem->str = (void *)ft_strdup(end);
		elem->str_size = ft_strlen(end) + 1;
		free(temp);
	}
	else
		start = get_str(head, fd);
	return (start);
}

int				get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_gnl	*head;
	int				ret;
	int				find;
	
	if (line == NULL || fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		buff[ret] = '\0';
		if ((find = find_line(buff, &head, fd)) == 1)
		{
			*line = get_substr(&head, fd);
			return (1);
		}
		if (find == -1)
			return (-1);
	}
	if ((*line = get_substr(&head, fd)) != NULL)
		return (1);
	return (0);
}
