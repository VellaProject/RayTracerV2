/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_compose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 20:28:24 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/26 20:03:18 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init_cylinder(t_obj *verre, t_obj *cyl)
{
	cyl->param.type = 2;
	cyl->position = M_POINT(
		M_IJ(&(verre->position), 0, 0),
		M_IJ(&(verre->position), 1, 0),
		M_IJ(&(verre->position), 2, 0) + 1);
	cyl->param.limit = 3;
	cyl->param.limit_coeff = 2;
	cyl->param.limit2 = 3;
	cyl->param.limit_coeff2 = -2;
}

void		ft_init_cone(t_obj *cone)
{
	cone->param.type = 3;
	cone->param.limit = 3;
	cone->param.limit2 = 3;
	cone->param.limit_coeff2 = -2;
}

void		ft_init_sphere(t_obj *verre, t_obj *sphere)
{
	sphere->param.type = 0;
	sphere->position = M_POINT(
		M_IJ(&(verre->position), 0, 0),
		M_IJ(&(verre->position), 1, 0),
		M_IJ(&(verre->position), 2, 0) + 4);
	sphere->scale = M_POINT(
		M_IJ(&(verre->scale), 0, 0) * 2,
		M_IJ(&(verre->scale), 1, 0) * 2,
		M_IJ(&(verre->scale), 2, 0) * 2);
	sphere->param.limit = 3;
}
