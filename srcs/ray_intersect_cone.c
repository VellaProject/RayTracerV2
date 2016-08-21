/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_cone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:07:43 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:27:57 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		rescue_texture_color(t_ray *r, t_obj *o)
{
	double	pitch;
	double	x;
	double	y;
	t_pix	p;

	pitch = (M_IJ(&(r->normal), 1, 0) > 0 ? 1 : -1)
		* acos(M_IJ(&(r->normal), 0, 0) / sqrt(M_IJ(&(r->normal), 0, 0)
		* M_IJ(&(r->normal), 0, 0) + M_IJ(&(r->normal), 1, 0)
		* M_IJ(&(r->normal), 1, 0)));
	x = (pitch + 3.1415) / (2 * 3.1415);
	y = M_IJ(&(r->intersection), 2, 0);
	x = x * M_IJ(&(o->param.text_mod), 0, 0) + M_IJ(&(o->param.text_mod), 0, 1);
	y = y * M_IJ(&(o->param.text_mod), 1, 0) + M_IJ(&(o->param.text_mod), 1, 1);
	ft_draw_getp(x, y, &p, o->param.texture);
	r->obj->param.color = p.c;
	return (0);
}

static int		ray_solution_cone(t_ray *ray, t_obj *obj)
{
	int		sign;

	ray->obj = obj;
	ray->intersection = M_POINT(
		M_IJ(&(ray->start), 0, 0) + ray->dist * M_IJ(&(ray->dir), 0, 0),
		M_IJ(&(ray->start), 1, 0) + ray->dist * M_IJ(&(ray->dir), 1, 0),
		M_IJ(&(ray->start), 2, 0) + ray->dist * M_IJ(&(ray->dir), 2, 0));
	if ((M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0))
		> (M_IJ(&(ray->start), 2, 0) * M_IJ(&(ray->start), 2, 0)))
		sign = 1;
	else
		sign = -1;
	ray->normal = M_DIR(
		sign * M_IJ(&(ray->intersection), 0, 0),
		sign * M_IJ(&(ray->intersection), 1, 0),
		-sign * M_IJ(&(ray->intersection), 2, 0));
	if (obj->param.texture)
		rescue_texture_color(ray, obj);
	return (0);
}

int				ray_intersect_cone(t_ray *ray, t_obj *obj)
{
	double		a;
	double		b;
	double		c;

	a = M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0)
		- M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->dir), 2, 0);
	b = 2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- 2 * M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->start), 2, 0);
	c = M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- M_IJ(&(ray->start), 2, 0) * M_IJ(&(ray->start), 2, 0);
	ray->dist = solve_2_degree_neg(a, b, c, ray);
	if (ray->dist > 0)
		ray_solution_cone(ray, obj);
	return (0);
}
