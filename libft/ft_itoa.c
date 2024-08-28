/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:17:54 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/12 18:55:08 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_digit(long nbr)
{
	int	digit;

	digit = 0;
	if (nbr <= 0)
	{
		digit++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		digit++;
		nbr = nbr / 10;
	}
	return (digit);
}

int	set_nbr(char *str, long nbr, int idx)
{
	if (nbr > 9)
	{
		idx = set_nbr(str, nbr / 10, idx);
	}
	str[idx] = nbr % 10 + '0';
	idx++;
	return (idx);
}

char	*ft_itoa(int n)
{
	int		digit;
	int		idx;
	char	*str;

	digit = check_digit(n);
	str = (char *)malloc(digit + 1);
	if (str == 0)
		return (0);
	idx = 0;
	if (n < 0)
	{
		str[0] = '-';
		idx = set_nbr(str, -(long)n, idx + 1);
	}
	else
		idx = set_nbr(str, n, idx);
	str[idx] = '\0';
	return (str);
}
