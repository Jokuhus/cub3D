/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:17:29 by jsuk              #+#    #+#             */
/*   Updated: 2024/02/12 16:36:24 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s != c)
			{
				s++;
				if (*s == '\0')
					return (count);
			}
		}
	}
	return (count);
}

int	make_arr(char **arr, char const *s, char c, int idx)
{
	int	len;

	len = 0;
	while (*(s + len) != c && *(s + len) != '\0')
		len++;
	arr[idx] = (char *)malloc(len + 1);
	if (arr[idx] == 0)
	{
		while (idx > 0)
		{
			idx--;
			free(arr[idx]);
		}
		free(arr);
		return (0);
	}
	ft_strlcpy(arr[idx], s, len + 1);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		idx;
	int		check;
	char	**arr;

	if (s == 0)
		return (0);
	count = count_word(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (arr == 0)
		return (0);
	idx = 0;
	while (idx < count)
	{
		while (*s == c)
			s++;
		check = make_arr(arr, s, c, idx);
		if (check == 0)
			return (0);
		while (*s != c && *s != '\0')
			s++;
		idx++;
	}
	arr[idx] = 0;
	return (arr);
}
