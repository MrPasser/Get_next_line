/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrasin <skrasin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:53:15 by skrasin           #+#    #+#             */
/*   Updated: 2019/11/01 01:19:44 by skrasin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// static t_list	*ft_search_node_by_content_size(t_list *lst,
// 														size_t content_size)
// {
// 	while (lst)
// 	{
// 		if ((*lst).content_size == content_size)
// 			return (lst);
// 		lst = (*lst).next;
// 	}
// 	return (NULL);
// }

// int				get_next_line(const int fd, char **line)
// {
// 	ssize_t			len;
// 	ssize_t			i;
// 	static t_list	*store;
// 	t_list			*tmp_node;
// 	char			buf[BUFF_SIZE + 1];
// 	char			*tmp;

// 	if (fd == -1)
// 		return (-1);
// 	tmp_node = ft_search_node_by_content_size(store, fd);
// 	i = 0;
// 	while ((len = read(fd, buf, BUFF_SIZE)) > 0)
// 	{
// 		buf[len] = '\0';
// 		if ((tmp_node))
// 			tmp_node->content = ft_strjoin(tmp_node->content, buf);/* leak */
// 		else
// 		{
// 			ft_lstadd(&store, ft_lstnew(buf, len));
// 			store->content_size = fd;
// 			tmp_node = store;
// 		}
// 		while (buf[i] != '\n' && i < len)
// 			i++;
// 		if (buf[i] == '\n')
// 			break;
// 	}
// 	if (tmp_node && ((char)(tmp_node->content + i) == '\n' || (char)(tmp_node->content + i) == '\0'))
// 	{
// 		free(*line);
// 		*line = ft_strsub(tmp_node->content, 0, i);
// 		if (buf[i] != '\0') //()?():()
// 		{
// 			tmp = ft_strdup(tmp_node->content + i + 1);
// 		}
// 		else
// 		{
// 			tmp = NULL;
// 		}
// 		printf("FREE\n");
// 		printf("content = %s\n = content\n", tmp_node->content);
// 		free(tmp_node->content);
// 		printf("FREE\n");
// 		tmp_node->content = tmp;
// 		printf("content = %s\n = content\n", tmp_node->content);
// 		free(tmp);
// 	}
// 	return (1);
// }

static t_list	*ft_search_node_by_content_size(t_list *lst,
														size_t content_size)
{
	while (lst)
	{
		if ((*lst).content_size == content_size)
			return (lst);
		lst = (*lst).next;
	}
	return (NULL);
}

static int		ft_i_of_nl_or_null_in_content_of_node(t_list node)
{
	int i;

	i = 0;
	while(*(char *)(node.content + i) != '\0' && *(char *)(node.content + i) != '\n')
			i++;
	return (i);
}

void	uf_del_callback(void *d, size_t s)
{
	printf("DELTEST\n");
	free(d);
	printf("DELTEST\n");
	(void)s;
}

int				get_next_line(const int fd, char **line)
{
	ssize_t			len;
	ssize_t			i;
	static t_list	*store;
	t_list			*tmp_node;
	char			*tmp;

	if (fd == -1 || !line)
		return (-1);
	free(*line);
	if (!(tmp_node = ft_search_node_by_content_size(store, fd)))
	{
		ft_lstadd(&store, ft_lstnew(ft_strnew(BUFF_SIZE), BUFF_SIZE + 1));
		store->content_size = fd;
		tmp_node = store;
	}
	i = 0;
	while ((len = read(fd, tmp_node->content, BUFF_SIZE)) > 0)
	{
		*(char *)(tmp_node->content + len) = '\0';
		i = ft_i_of_nl_or_null_in_content_of_node(*tmp_node);
		if (*(char *)(tmp_node->content + i) == '\n')
			break ;
		tmp = ft_strjoin(*line, tmp_node->content);
		if (*line)
			free(*line);
		*line = tmp;
		free(tmp);
	}
	if (len < 0)
		return (-1);
	if (!i)
		i = ft_i_of_nl_or_null_in_content_of_node(*tmp_node);
	*line = ft_strsub(tmp_node->content, 0, i);
	if (*(char *)(tmp_node->content + i) == '\n') //move
	{
		tmp = ft_strdup(tmp_node->content + i + 1);
		free(tmp_node->content);
		tmp_node->content = tmp;
	}
	else if (*(char *)(tmp_node->content + i) == '\0')
		ft_strdel(tmp_node->content);
	printf("TEST\n");
	if (len == 0 && i == 0)
		return (0);
	return (1);
}

// int				main(int argc, char **argv)
// {
// 	int		j;
// 	int		out;
// 	int		fd;
// 	char	*line;

// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	line = ft_strnew(1);
// 	while (j++ < 7)
// 	{
// 		out |= get_next_line(fd, &line);
// 		printf("main = %s\n", line);
// 	}
// 	close(fd);
// 	return (out);
// }
