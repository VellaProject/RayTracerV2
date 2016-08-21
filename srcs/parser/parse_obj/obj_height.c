/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_height.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 15:36:00 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/22 15:37:39 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_obj_parse_height(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3)
	{
		obj->param.height = ft_get_double_value(p[1]);
		ft_tabdel(&p);
		return (P_HEIGHT);
	}
	P_ERROR("HEIGHT", *count);
	obj->param.height = 0;
	ft_tabdel(&p);
	return (0);
}
