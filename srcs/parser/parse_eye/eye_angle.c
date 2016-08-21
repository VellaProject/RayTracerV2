/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eye_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 02:37:00 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	ft_eye_parse_angle(t_cam *cam, char const *line, size_t *count)
{
	char	**p;
	double	a;
	double	b;
	double	c;

	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 5)
	{
		a = ft_get_double_value(p[1]);
		b = ft_get_double_value(p[2]);
		c = ft_get_double_value(p[3]);
		cam->ang = M_POINT(a, b, c);
		ft_tabdel(&p);
		return (P_ANGLE);
	}
	P_ERROR("ANGLE", *count);
	cam->ang = M_POINT(0, 0, 0);
	ft_tabdel(&p);
	return (0);
}
