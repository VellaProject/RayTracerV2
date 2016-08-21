/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_radius.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 15:32:55 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/22 15:40:39 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_obj_parse_radius(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3)
	{
		obj->param.radius = ft_get_double_value(p[1]);
		ft_tabdel(&p);
		return (P_RADIUS);
	}
	P_ERROR("RADIUS", *count);
	obj->param.radius = 0;
	ft_tabdel(&p);
	return (0);
}
