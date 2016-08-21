/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex_compile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 13:24:21 by igomez            #+#    #+#             */
/*   Updated: 2016/06/17 03:46:32 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static t_regex	*ft_new_item(void)
{
	t_regex *r;

	if ((r = (t_regex *)ft_memalloc(sizeof(t_regex))) == NULL)
		return (NULL);
	ft_bzero((void *)r->list, 100);
	r->next = NULL;
	r->not = 0;
	r->c = 0;
	r->i = 0;
	return (r);
}

static void		ft_parse_list(t_regex *p, char const *s, size_t *i)
{
	char c;

	if (*(s + 1) == '^')
	{
		p->not = 1;
		*i += 1;
		s++;
	}
	while (*++s != ']')
	{
		*i += 1;
		if (*(s + 1) == '-')
		{
			c = *s;
			s += 2;
			*i += 2;
			while (c <= *s && p->i < 100)
				p->list[p->i++] = c++;
		}
		else
			p->list[p->i++] = *s;
	}
	*i += 1;
}

static t_regex	*ft_regex_parse(char const *s, size_t *i, bool escape)
{
	char	*tmp;
	t_regex *p;
	char	*x;

	tmp = "^$.*+?[";
	if ((p = ft_new_item()) == NULL)
		return (NULL);
	if (escape == true || (x = ft_strchr(tmp, *s)) == 0)
		p->type = CHAR;
	else
		p->type = x - tmp;
	p->c = *s;
	if (escape == false && *s == '[')
		ft_parse_list(p, s, i);
	*i += 1;
	return (p);
}

t_regex			*ft_regex_compile(char const *s)
{
	t_regex head;
	t_regex *tail;
	t_regex	*p;
	size_t	i;
	bool	escape;

	i = 0;
	tail = &head;
	while (*(s + i) != 0)
	{
		escape = false;
		if (*(s + i) == '\\')
		{
			++i;
			escape = true;
		}
		p = ft_regex_parse(s + i, &i, escape);
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return (head.next);
}
