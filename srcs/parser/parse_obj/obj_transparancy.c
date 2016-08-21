/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_transparancy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 01:22:40 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_obj_parse_transparancy(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3)
	{
		obj->param.transparancy = ft_get_double_value(p[1]);
		ft_tabdel(&p);
		return (P_TRANSPARANCY);
	}
	P_ERROR("TRANSPARANCY", *count);
	obj->param.transparancy = 0;
	ft_tabdel(&p);
	return (0);
}
