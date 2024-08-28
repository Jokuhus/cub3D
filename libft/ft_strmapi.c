/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:18:29 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/13 07:51:24 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	idx;
	char	*str;

	if (s == 0)
		return (0);
	size = ft_strlen(s);
	str = (char *)malloc(size + 1);
	if (str == 0)
		return (0);
	idx = 0;
	while (idx < size)
	{
		str[idx] = f(idx, s[idx]);
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
