/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 13:06:21 by igomez            #+#    #+#             */
/*   Updated: 2016/06/17 03:46:34 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static bool	ft_is_in_list(char c, char const *s, t_regex *r)
{
	if (r == NULL && s != NULL)
	{
		while (*s != 0 && *s != c)
			s++;
		return (*s == c);
	}
	if (r->type != LIST)
		return (false);
	s = r->list;
	if (s != NULL)
		while (*s != 0 && *s != c)
			s++;
	return ((*s != 0) ^ r->not);
}

static bool	ft_matchstar(t_regex *cur, t_regex *r, char const *s)
{
	while (true)
	{
		if (ft_matchhere(r, s))
			return (true);
		if (!*s || !MATCH(cur, s))
			break ;
		s++;
	}
	return (false);
}

static bool	ft_matchplus(t_regex *cur, t_regex *r, char const *s)
{
	while (*s != 0 && MATCH(cur, s))
		if (ft_matchhere(r, ++s))
			return (true);
	return (false);
}

static bool	ft_matchques(t_regex *cur, t_regex *r, char const *s)
{
	char const *t;

	t = s;
	if (*t != 0 && MATCH(cur, s))
		t++;
	while (true)
	{
		if (ft_matchhere(r, t))
			return (true);
		if (s > t--)
			break ;
	}
	return (false);
}

bool		ft_matchhere(t_regex *r, char const *s)
{
	g_regex_match_end = s;
	if (r == NULL)
		return (true);
	if (r->type == END && r->next == NULL)
		return (*s == 0);
	if (r->next != NULL)
	{
		if (r->next->type == STAR)
			return (ft_matchstar(r, r->next->next, s));
		if (r->next->type == PLUSS)
			return (ft_matchplus(r, r->next->next, s));
		if (r->next->type == QUEST)
			return (ft_matchques(r, r->next->next, s));
	}
	if (*s != 0 && MATCH(r, s))
		return (ft_matchhere(r->next, s + 1));
	return (false);
}
