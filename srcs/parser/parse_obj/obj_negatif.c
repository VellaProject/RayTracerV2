/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_negatif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 01:22:40 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_obj_parse_negatif(t_obj *obj, char const *line, size_t *count)
{
	char	**p;
	int		tmp;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3)
	{
		tmp = 0;
		if (ft_strlen(p[1]) == ft_strlen_func(p[1], &ft_isdigit))
			tmp = ft_atoi(p[1]);
		if (ft_strequ(p[1], "true") || tmp == 1)
			obj->param.negatif = true;
		else
			obj->param.negatif = false;
		ft_tabdel(&p);
		return (P_NEGATIF);
	}
	P_ERROR("NEGATIF", *count);
	obj->param.negatif = 0;
	ft_tabdel(&p);
	return (0);
}
