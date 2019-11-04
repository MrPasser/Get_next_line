/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrasin <skrasin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:53:15 by skrasin           #+#    #+#             */
/*   Updated: 2019/11/04 15:04:22 by skrasin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define CONT (store->content)
#define P_NL (ft_strchr(CONT, '\n'))
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static t_list	*ft_lstsearch(size_t content_size)
{
	static t_list	*store;
	t_list			*tmp;

	tmp = store;
	while (tmp)
	{
		if (tmp->content_size == content_size)
			return (tmp);
		tmp = tmp->next;
	}
	ft_lstadd(&tmp, ft_lstnew(ft_strnew(BUFF_SIZE), BUFF_SIZE));
	tmp->content_size = content_size;
	store = tmp;
	return (tmp);
}

static char		*ft_strextend(char **dst, char const *src, size_t len)
{
	char *tmp;

	tmp = ft_strjoin(*dst, ft_strsub(src, 0, len));
	if (*dst)
		free(*dst);
	*dst = tmp;
	return (*dst);
}

static void		ft_strcut(char **str, char *sep)
{
	char	*tmp;
	size_t	i;

	i = sep - *str;
	if (*sep != '\0')
		i++;
	tmp = ft_strdup(*str + i);
	free(*str);
	*str = tmp;
}

int				get_next_line(const int fd, char **line)
{
	ssize_t			len;
	t_list			*store;

	if (fd < 0 || !line)
		return (-1);
	free(*line);
	*line = ft_strnew(0);
	store = ft_lstsearch(fd);
	while ((len = read(fd, CONT, BUFF_SIZE)) > 0)
	{
		if (P_NL)
			break ;
		*line = ft_strextend(line, CONT, len);
		ft_strcut((char **)&(CONT), (CONT) + ft_strlen(CONT));
	}
	if (len < 0)
		return (-1);
	if (P_NL - (char *)(CONT) > -1 && *(char *)CONT != '\0')
	{
		*line = ft_strextend(line, CONT, P_NL - (char *)(CONT));
		ft_strcut((char **)&(CONT), P_NL);
		return (1);
	}
	*line = ft_strextend(line, CONT, ft_strlen(CONT));
	ft_strcut((char **)&(CONT), (CONT) + ft_strlen(CONT));
	if (len == 0 && *(char *)CONT == '\0' && **line == '\0')
		return (0);
	return (1);
}
