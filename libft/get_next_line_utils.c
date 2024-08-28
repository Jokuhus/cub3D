/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:58:00 by jsuk              #+#    #+#             */
/*   Updated: 2024/02/12 21:03:22 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*ft_newlst(int fd)
{
	t_file	*node;

	node = (t_file *)malloc(sizeof(t_file));
	if (node == 0)
		return (0);
	node->fd = fd;
	node->str = 0;
	node->buf = 0;
	node->str_len = 0;
	node->buf_len = 0;
	node->buf_size = 0;
	node->idx = 0;
	node->eof = 0;
	node->end = 0;
	node->next = 0;
	return (node);
}

t_file	*check_list(int fd, t_file **file)
{
	t_file	*tmp;

	if (*file == 0)
	{
		*file = ft_newlst(fd);
		return (*file);
	}
	tmp = *file;
	if (tmp->fd == fd)
		return (tmp);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->fd == fd)
			return (tmp);
	}
	tmp->next = ft_newlst(fd);
	return (tmp->next);
}

void	copy_str(char *dest, char *src, size_t d_len, size_t size)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		dest[d_len] = src[idx];
		d_len++;
		idx++;
	}
}

void	new_mal(t_file *file)
{
	char	*tmp;

	if (file->buf_size < file->buf_len + BUFFER_SIZE)
	{
		while (file->buf_size < file->buf_len + BUFFER_SIZE)
			file->buf_size = file->buf_size * 2;
		tmp = file->buf;
		file->buf = (char *)malloc(file->buf_size);
		if (file->buf == 0)
		{
			if (tmp != 0)
				free(tmp);
			return ;
		}
		if (tmp != 0)
		{
			copy_str(file->buf, tmp, 0, file->buf_len);
			free(tmp);
		}
	}
}

void	free_node(t_file *node, t_file **head)
{
	t_file	*tmp;

	if (node == 0)
		return ;
	tmp = *head;
	if (tmp == node)
		*head = tmp->next;
	else
	{
		while (tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
	}
	if (node->str != 0)
		free(node->str);
	if (node->buf != 0)
		free(node->buf);
	free(node);
}
