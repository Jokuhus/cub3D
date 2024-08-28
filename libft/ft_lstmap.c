/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:19:56 by jsuk              #+#    #+#             */
/*   Updated: 2023/10/16 14:34:47 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	map_lst(t_list *lst, t_list *new, void *(*f)(void *), void (*del)(void *))
{
	void	*cont;
	t_list	*node;

	while (lst->next)
	{
		lst = lst->next;
		cont = f(lst->content);
		node = ft_lstnew(cont);
		if (node == 0)
		{
			del(cont);
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, node);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*cont;
	int		check;

	if (lst == 0)
		return (0);
	cont = f(lst->content);
	new = ft_lstnew(cont);
	if (new == 0)
	{
		del(cont);
		return (0);
	}
	check = map_lst(lst, new, f, del);
	if (check == 0)
		return (0);
	return (new);
}
