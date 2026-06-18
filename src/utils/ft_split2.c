/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:44:07 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 13:44:09 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_size(char const *s, char *set)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (ft_strchr(set, *s) && *s)
			s++;
		if (*s)
			count++;
		while (!ft_strchr(set, *s) && *s)
			s++;
	}
	return (count);
}

static void	allocate(char **ptr)
{
	char	**ptr2;

	ptr2 = ptr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(ptr2);
}

static int	copy(char *start, char *end, char **ptr_o, char **res_o)
{
	char	*ptr;
	char	*res;

	ptr = (char *)malloc(sizeof(char) * (end - start + 1));
	res = ptr;
	if (!ptr)
	{
		allocate(res_o);
		return (0);
	}
	while (start < end)
	{
		*ptr = *start;
		ptr++;
		start++;
	}
	*ptr = 0;
	*ptr_o = res;
	return (1);
}

char	**ft_split2(char const *s, char *set)
{
	char	**res;
	char	**ptr;
	char	*start;

	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (find_size(s, set) + 1));
	res = ptr;
	if (!ptr)
		return (0);
	while (*s)
	{
		while (ft_strchr(set, *s) && *s)
			s++;
		if (*s)
			start = (char *)s;
		else
			break ;
		while (!ft_strchr(set, *s) && *s)
			s++;
		if (!copy(start, (char *)s, ptr++, res))
			return (0);
	}
	*ptr = 0;
	return (res);
}
