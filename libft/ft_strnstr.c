/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:43:04 by jsuk              #+#    #+#             */
/*   Updated: 2024/02/13 20:19:09 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	size_t	idx;

	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *)haystack);
	idx = 0;
	while (idx < len && *haystack)
	{
		if (n_len + idx > len)
			return (0);
		if (haystack[idx] == *needle)
		{
			if (ft_strncmp(&haystack[idx], needle, n_len) == 0)
				return ((char *)&haystack[idx]);
		}
		idx++;
	}
	return (0);
}
