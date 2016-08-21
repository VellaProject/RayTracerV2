/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:47:53 by igomez            #+#    #+#             */
/*   Updated: 2016/06/17 05:27:21 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, int (*f)(int))
{
	int	i;
	int	j;
	int	w;

	w = 1;
	i = 0;
	while (*(s + i) != 0)
	{
		while (f(*(s + i)) != 0)
			++i;
		j = i;
		while (*(s + i) != 0 && f(*(s + i)) == 0)
			++i;
		if (i != j)
			++w;
	}
	return (w);
}

char		**ft_strsplit_func(char const *s, int (*f)(int))
{
	char	**tab;
	int		i;
	int		j;
	int		w;

	if ((tab = ft_tabnew(ft_count(s, f))) == 0)
		return (0);
	w = 0;
	i = 0;
	while (*(s + i) != 0)
	{
		while (f(*(s + i)) != 0)
			++i;
		j = i;
		while (*(s + i) != 0 && f(*(s + i)) == 0)
			++i;
		if (i != j)
			tab[w++] = ft_strsub(s, j, i - j);
	}
	tab[w] = 0;
	return (tab);
}
