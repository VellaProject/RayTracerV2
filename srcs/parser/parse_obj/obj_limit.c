/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_limit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 16:48:47 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/26 20:02:40 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parse_limit(t_obj *obj, char **p)
{
	if (ft_strcmp(p[1], "x_rot") == 0)
		obj->param.limit = 1;
	if (ft_strcmp(p[1], "y_rot") == 0)
		obj->param.limit = 2;
	if (ft_strcmp(p[1], "z_rot") == 0)
		obj->param.limit = 3;
	if (ft_strcmp(p[1], "x_abs") == 0)
		obj->param.limit = 4;
	if (ft_strcmp(p[1], "y_abs") == 0)
		obj->param.limit = 5;
	if (ft_strcmp(p[1], "z_abs") == 0)
		obj->param.limit = 6;
	return (0);
}

int		parse_limit2(t_obj *obj, char **p)
{
	if (ft_strcmp(p[1], "x_rot") == 0)
		obj->param.limit2 = 1;
	if (ft_strcmp(p[1], "y_rot") == 0)
		obj->param.limit2 = 2;
	if (ft_strcmp(p[1], "z_rot") == 0)
		obj->param.limit2 = 3;
	if (ft_strcmp(p[1], "x_abs") == 0)
		obj->param.limit2 = 4;
	if (ft_strcmp(p[1], "y_abs") == 0)
		obj->param.limit2 = 5;
	if (ft_strcmp(p[1], "z_abs") == 0)
		obj->param.limit2 = 6;
	return (0);
}

int		ft_obj_parse_limit2(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3 || ft_tablen(p) == 5)
	{
		if (ft_tablen(p) == 5)
			obj->param.limit_coeff2 = ft_atoi_double(p[3]);
		parse_limit2(obj, p);
		ft_tabdel(&p);
		return (P_LIMIT2);
	}
	P_ERROR("LIMIT2", *count);
	obj->param.limit2 = 0;
	ft_tabdel(&p);
	return (0);
}

int		ft_obj_parse_limit(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3 || ft_tablen(p) == 5)
	{
		if (ft_tablen(p) == 5)
			obj->param.limit_coeff = ft_atoi_double(p[3]);
		parse_limit(obj, p);
		ft_tabdel(&p);
		return (P_LIMIT);
	}
	P_ERROR("LIMIT", *count);
	obj->param.limit = 0;
	ft_tabdel(&p);
	return (0);
}
