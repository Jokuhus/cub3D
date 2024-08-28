/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:18:40 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/13 07:34:27 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	size;
	size_t	idx;

	if (s == 0)
		return ;
	size = ft_strlen(s);
	idx = 0;
	while (idx < size)
	{
		f(idx, &s[idx]);
		idx++;
	}
}
