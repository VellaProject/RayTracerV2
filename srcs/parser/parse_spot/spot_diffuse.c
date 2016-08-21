/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_diffuse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 02:15:30 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_spot_parse_diffuse(t_spot *spot, char const *line, size_t *count)
{
	char	**p;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 3)
	{
		spot->param.diffuse = ft_get_double_value(p[1]);
		ft_tabdel(&p);
		return (P_DIFFUSE);
	}
	P_ERROR("DIFFUSE", *count);
	spot->param.diffuse = 0;
	ft_tabdel(&p);
	return (0);
}
