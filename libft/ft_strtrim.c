/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:14:48 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/12 18:59:16 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	ft_checkf(char const *s1, char const *set)
{
	int	f;

	f = 0;
	while (ft_checkset(s1[f], set) && s1[f])
		f++;
	return (f);
}

int	ft_checkb(char const *s1, char const *set, int size)
{
	int	b;

	if (size <= 0)
		return (0);
	b = 0;
	while (ft_checkset(s1[size - b - 1], set) && size != b)
		b++;
	return (b);
}

char	*set_str(char *str, char const *s1, int len, int f_count)
{
	int	i;

	i = 0;
	while (i < len)
	{
		str[i] = s1[f_count + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		f_count;
	int		b_count;
	int		size;
	int		len;
	char	*str;

	if (s1 == 0 || set == 0)
		return (0);
	size = ft_strlen(s1);
	f_count = ft_checkf(s1, set);
	b_count = ft_checkb(s1, set, size);
	if (size == f_count)
		len = 0;
	else
		len = size - f_count - b_count;
	str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	str = set_str(str, s1, len, f_count);
	return (str);
}
