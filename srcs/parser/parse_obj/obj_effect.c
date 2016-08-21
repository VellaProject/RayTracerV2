/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_effect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 01:23:01 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_key_value	g_effect_type[] =
{
	{"none", EFFNONE},
	{"noise", NOISE},
	{"damier", DAMIER},
	{"sinus", SINUS},
	{"cool", COOL},
	{0, 0}
};

static int	ft_get_effect(char const *effect)
{
	size_t i;

	i = 0;
	while (g_effect_type[i].key != 0)
	{
		if (ft_strequ(g_effect_type[i].key, effect) != false)
			return (g_effect_type[i].value);
		++i;
	}
	return (0);
}

int			ft_obj_parse_effect(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3)
	{
		obj->param.effect = ft_get_effect(p[1]);
		ft_tabdel(&p);
		return (P_EFFECT);
	}
	P_ERROR("EFFECT", *count);
	obj->param.effect = 0;
	ft_tabdel(&p);
	return (0);
}
