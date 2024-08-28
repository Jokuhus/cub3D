/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:20:39 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/12 13:23:11 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	if (dst == 0 && src == 0)
		return (dst);
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	while (n--)
	{
		*a = *b;
		a++;
		b++;
	}
	return (dst);
}
