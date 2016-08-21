/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 01:48:47 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_obj_parse_texture(t_obj *obj, char const *line, size_t *count)
{
	char	**p;

	obj->param.texture = 0;
	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 7)
	{
		obj->param.texture_file = ft_strdup(p[1]);
		obj->param.text_mod = M_NEW(2, 2);
		M_IJ(&obj->param.text_mod, 0, 0) = ft_get_double_value(p[2]);
		M_IJ(&obj->param.text_mod, 1, 0) = ft_get_double_value(p[3]);
		M_IJ(&obj->param.text_mod, 0, 1) = ft_get_double_value(p[4]);
		M_IJ(&obj->param.text_mod, 1, 1) = ft_get_double_value(p[5]);
		ft_tabdel(&p);
		return (P_TEXTURE);
	}
	P_ERROR("TEXTURE", *count);
	obj->param.texture = 0;
	obj->param.texture_file = 0;
	obj->param.text_mod = M_NEW(0, 0);
	ft_tabdel(&p);
	return (0);
}
