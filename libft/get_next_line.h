/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:46:39 by jsuk              #+#    #+#             */
/*   Updated: 2024/06/30 15:16:44 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_file{
	char			*str;
	char			*buf;
	int				str_len;
	int				buf_len;
	int				buf_size;
	int				idx;
	int				fd;
	int				eof;
	int				end;
	struct s_file	*next;
}	t_file;

t_file	*ft_newlst(int fd);
t_file	*check_list(int fd, t_file **file);
void	copy_str(char *dest, char *src, size_t d_len, size_t size);
void	new_mal(t_file *file);
void	free_node(t_file *node, t_file **head);
void	read_file(t_file *file);
int		make_str(t_file *file);
int		set_line(t_file *file);
char	*get_next_line(int fd);

#endif
