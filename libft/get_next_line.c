/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:30:00 by jsuk              #+#    #+#             */
/*   Updated: 2024/06/30 15:16:38 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_line(char *line, int len)
{
	int	idx;

	idx = 0;
	if (line == 0)
		return (-1);
	while (idx < len)
	{
		if (line[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

void	read_file(t_file *file)
{
	int	read_size;

	while (1)
	{
		new_mal(file);
		if (file->buf == 0)
			return ;
		read_size = read(file->fd, file->buf + file->buf_len, BUFFER_SIZE);
		if (read_size < 0)
			return ;
		file->idx = check_line(file->buf + file->buf_len, read_size);
		if (read_size < BUFFER_SIZE)
			file->eof = 1;
		if (file->idx >= 0)
			break ;
		file->buf_len = file->buf_len + read_size;
		if (file->idx < 0 && file->eof)
		{
			file->str_len = file->buf_len;
			return ;
		}
	}
	file->str_len = file->buf_len + file->idx + 1;
	file->buf_len = file->buf_len + read_size;
	return ;
}

int	make_str(t_file *file)
{
	char	*tmp;

	if (file->buf_len == 0)
		return (0);
	file->buf_len = file->buf_len - file->str_len;
	tmp = file->buf;
	file->str = (char *)malloc(file->str_len);
	if (file->str == 0)
		return (0);
	if (file->buf_len)
	{
		file->buf = (char *)malloc(file->buf_len);
		if (file->buf == 0)
		{
			free(tmp);
			return (0);
		}
		copy_str(file->buf, tmp + file->str_len, 0, file->buf_len);
	}
	else
		file->buf = 0;
	copy_str(file->str, tmp, 0, file->str_len);
	free(tmp);
	return (1);
}

int	set_line(t_file *file)
{
	file->buf_size = file->buf_len;
	file->str_len = check_line(file->buf, file->buf_len) + 1;
	if (file->str_len > 0)
		return (make_str(file));
	if (file->buf == 0)
	{
		file->buf = (char *)malloc(BUFFER_SIZE);
		if (file->buf == 0)
			return (0);
		file->buf_size = BUFFER_SIZE;
	}
	file->idx = -1;
	read_file(file);
	if (file->buf == 0)
		return (0);
	if (file->eof && file->idx < 0)
	{
		file->end = 1;
		return (make_str(file));
	}
	else if (file->idx < 0)
		return (0);
	return (make_str(file));
}

char	*get_next_line(int fd)
{
	static t_file	*head;
	t_file			*file;
	char			*str;

	if (fd < 0)
		return (0);
	file = check_list(fd, &head);
	if (file == 0)
		return (0);
	if (file->end || set_line(file) == 0)
	{
		free_node(file, &head);
		return (0);
	}
	str = (char *)malloc(file->str_len + 1);
	if (str == 0)
	{
		free_node(file, &head);
		return (0);
	}
	copy_str(str, file->str, 0, file->str_len);
	str[file->str_len] = '\0';
	free(file->str);
	file->str = 0;
	return (str);
}
