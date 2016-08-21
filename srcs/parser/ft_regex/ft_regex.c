/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 13:06:12 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 06:11:00 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"
#include <stdlib.h>

static void	ft_free_regex(t_regex *p)
{
	if (p->next != NULL)
		ft_free_regex(p->next);
	free(p);
}

static void	ft_free_split(char **p)
{
	size_t i;

	i = 0;
	while (p[i] != NULL)
		free(p[i++]);
	free(p);
}

static char	*ft_get_deepest_parent(char const *p)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (*p != 0)
	{
		if (*p == ')')
			j--;
		else if (*p == '(')
		{
			j++;
			if (j > i)
			{
				s = (char *)p;
				i = j;
			}
		}
		p++;
	}
	if (i == 0)
		return (NULL);
	return (s + 1);
}

static bool	ft_regex_or(char *s1, char *s2, char *s3, char const *string)
{
	char	buf[0x1000];
	char	**t;
	bool	b;
	size_t	n;
	size_t	i;

	b = false;
	ft_strcpy(buf, s1);
	if ((t = ft_strsplit(s2, '|')) != NULL)
	{
		i = 0;
		while (t[i] != NULL)
		{
			n = ft_strlen(s1);
			ft_bzero((void *)buf + n, 0x1000 - n);
			ft_strcat(buf, t[i++]);
			ft_strcat(buf, s3);
			if ((b = ft_regex(buf, string)) == true)
				break ;
		}
		ft_free_split(t);
	}
	free(s1);
	free(s2);
	return (b);
}

bool		ft_regex(char const *p, char const *s)
{
	t_regex	*r;
	char	*l;
	char	*x;

	if (!*p)
		return (!*s);
	if ((x = ft_get_deepest_parent(p)) != NULL)
	{
		l = x;
		while (*s && *l != ')')
			l++;
		return (ft_regex_or(NDUP(p, x - p - 1), NDUP(x, l - x), l + 1, s));
	}
	else if (ft_strchr(p, '|') != NULL)
		return (ft_regex_or(ft_strdup("("), ft_strdup(p), ")", s));
	if ((r = ft_regex_compile(p)) == NULL)
		return (0);
	if (r->type != BEGIN)
		while (*s != 0 && !ft_matchhere(r, s))
			s++;
	else if (!ft_matchhere(r->next, s))
		s += ft_strlen(s);
	g_regex_match_start = s;
	ft_free_regex(r);
	return (*s != 0);
}
