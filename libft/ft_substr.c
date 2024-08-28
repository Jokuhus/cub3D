/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:26:37 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/12 16:32:40 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (s == 0)
		return (0);
	size = ft_strlen(s);
	if (size < start)
		len = 0;
	else if (size < start + len)
		len = size - start;
	sub = (char *)malloc(len + 1);
	if (sub == 0)
		return (0);
	if (size < start)
		sub[0] = '\0';
	else
		ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
