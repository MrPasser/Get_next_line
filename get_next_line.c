/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svet <svet@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:53:15 by skrasin           #+#    #+#             */
/*   Updated: 2020/05/26 14:08:03 by svet             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static inline t_list	*ft_lstsearch(size_t content_size)
{
	static t_list	*store = NULL;
	t_list			*node;
	char			*tmp;

	node = store;
	while (node != NULL)
	{
		if (node->content_size == content_size)
			return (node);
		node = node->next;
	}
	tmp = ft_strnew(BUFF_SIZE);
	ft_lstadd(&store, ft_lstnew(tmp, BUFF_SIZE + 1));
	free(tmp);
	if (store == NULL)
		return (NULL);
	store->content_size = content_size;
	return (store);
}

int				get_next_line(const int fd, char **line)
{
	ssize_t			len;
	t_list			*node;
	char			buf[BUFF_SIZE + 1];
	char			*nl;

	if (fd < 0 || line == NULL || read(fd, 0, 0) == -1 || (node = ft_lstsearch(fd)) == NULL)
		return (-1);
	while ((nl = ft_strchr(node->content, '\n')) == NULL)
	{
		if ((len = read(fd, buf, BUFF_SIZE)) <= 0)
			break ;
		buf[len] = '\0';
		ft_strextend((char **)&node->content, buf);
	}
	*line = nl ? ft_strsub(node->content, 0, nl - (char *)node->content) : ft_strdup(node->content);
	*(char *)node->content = '\0';
	nl ? ft_strextend((char **)&node->content, nl + 1) :
									ft_strextend((char **)&node->content, node->content);
	return ((**line == '\0' && !len) ? 0 : 1);
}
