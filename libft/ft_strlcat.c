/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:58:44 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/12 13:50:56 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(src);
	if (dst == 0 && dstsize == 0)
		return (s_len);
	d_len = ft_strlen(dst);
	i = 0;
	while (d_len + i + 1 < dstsize && src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	if (d_len > dstsize)
		return (dstsize + s_len);
	return (d_len + s_len);
}
