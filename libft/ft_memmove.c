/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:52:37 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/12 18:57:26 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_overlap(unsigned char *a, unsigned char *b, size_t len)
{
	while (len)
	{
		if (b == a)
			return (1);
		len--;
		b++;
	}
	return (0);
}

void	ft_copy(unsigned char *a, unsigned char *b, size_t len)
{
	int	check;

	check = check_overlap(a, b, len);
	if (check == 0)
	{
		while (len--)
		{
			*a = *b;
			a++;
			b++;
		}
	}
	else
	{
		while (len--)
			a[len] = b[len];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;

	if (dst == src)
		return (dst);
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	ft_copy(a, b, len);
	return (dst);
}
