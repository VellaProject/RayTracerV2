/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_torus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 15:58:40 by arthur            #+#    #+#             */
/*   Updated: 2016/06/27 22:52:34 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		rescue_texture_color(t_ray *r, t_obj *o)
{
	double	yaw;
	double	pitch;
	double	x;
	double	y;
	t_pix	p;

	pitch = (M_IJ(&(r->normal), 1, 0) > 0 ? 1 : -1)
		* acos(M_IJ(&(r->normal), 0, 0) / sqrt(M_IJ(&(r->normal), 0, 0)
		* M_IJ(&(r->normal), 0, 0) + M_IJ(&(r->normal), 1, 0)
		* M_IJ(&(r->normal), 1, 0)));
	yaw = -acos(M_IJ(&(r->normal), 2, 0));
	x = (pitch + 3.1415) / (2 * 3.1415);
	y = fabs((yaw - 3.1415) / 3.1415);
	x = x * M_IJ(&(o->param.text_mod), 0, 0) + M_IJ(&(o->param.text_mod), 0, 1);
	y = y * M_IJ(&(o->param.text_mod), 1, 0) + M_IJ(&(o->param.text_mod), 1, 1);
	ft_draw_getp(x, y, &p, o->param.texture);
	r->obj->param.color = p.c;
	return (0);
}

static int		ray_solution_torus(t_ray *ray, t_obj *obj)
{
	double d;

	ray->obj = obj;
	ray->intersection = M_POINT(
		M_IJ(&(ray->start), 0, 0) + ray->dist * M_IJ(&(ray->dir), 0, 0),
		M_IJ(&(ray->start), 1, 0) + ray->dist * M_IJ(&(ray->dir), 1, 0),
		M_IJ(&(ray->start), 2, 0) + ray->dist * M_IJ(&(ray->dir), 2, 0));
	d = sqrt(M_IJ(&(ray->intersection), 0, 0) * M_IJ(&(ray->intersection), 0, 0)
		+ M_IJ(&(ray->intersection), 1, 0) * M_IJ(&(ray->intersection), 1, 0));
	ray->normal = M_DIR(
		(1 - obj->param.radius / d) *
		M_IJ(&(ray->intersection), 0, 0) / obj->param.height,
		(1 - obj->param.radius / d) *
		M_IJ(&(ray->intersection), 1, 0) / obj->param.height,
		M_IJ(&(ray->intersection), 2, 0) / obj->param.height);
	if (obj->param.texture)
		rescue_texture_color(ray, obj);
	return (0);
}

static double	get_t3(double o[3][3], double v[3][3])
{
	return (2 * ((o[0][0] * v[0][0] * v[1][1] + v[0][1] * o[1][0] * v[1][0])
		+ (o[0][0] * v[0][0] * v[2][1] + v[0][1] * o[2][0] * v[2][0])
		+ (o[1][0] * v[1][0] * v[0][1] + v[1][1] * o[0][0] * v[0][0])
		+ (o[1][0] * v[1][0] * v[2][1] + v[1][1] * o[2][0] * v[2][0])
		+ (o[2][0] * v[2][0] * v[0][1] + v[2][1] * o[0][0] * v[0][0])
		+ (o[2][0] * v[2][0] * v[1][1] + v[2][1] * o[1][0] * v[1][0])
		+ 2 * (o[0][0] * v[0][2] + o[1][0] * v[1][2] + o[2][0] * v[2][2])));
}

static void		get_t4t2t1t0(double t[5],
	double o[3][3], double v[3][3], double c[2])
{
	t[4] = (v[0][1] + v[1][1] + v[2][1]) * (v[0][1] + v[1][1] + v[2][1]);
	t[2] = o[0][1] * v[1][1] + v[0][1] * o[1][1] + o[0][1] * v[2][1]
		+ v[0][1] * o[2][1] + o[1][1] * v[0][1] + v[1][1] * o[0][1]
		+ o[1][1] * v[2][1] + v[1][1] * o[2][1] + o[2][1] * v[0][1]
		+ v[2][1] * o[0][1] + o[2][1] * v[1][1] + v[2][1] * o[1][1]
		+ 2 * (2 * (o[0][0] * v[0][0] * (o[1][0] * v[1][0] + o[2][0] * v[2][0])
			+ o[1][0] * v[1][0] * (o[0][0] * v[0][0] + o[2][0] * v[2][0])
			+ o[2][0] * v[2][0] * (o[0][0] * v[0][0] + o[1][0] * v[1][0]))
			+ 3 * (o[0][1] * v[0][1] + o[1][1] * v[1][1] + o[2][1] * v[2][1])
			+ c[1] * ((v[0][1] + v[1][1] + v[2][1]) - 2 * (v[0][1] + v[1][1]))
			- (c[0] * (v[0][1] + v[1][1] + v[2][1])));
	t[1] = 2 * ((o[0][1] * o[1][0] * v[1][0] + o[0][0] * v[0][0] * o[1][1])
		+ (o[0][1] * o[2][0] * v[2][0] + o[0][0] * v[0][0] * o[2][1])
		+ (o[1][1] * o[0][0] * v[0][0] + o[1][0] * v[1][0] * o[0][1])
		+ (o[1][1] * o[2][0] * v[2][0] + o[1][0] * v[1][0] * o[2][1])
		+ (o[2][1] * o[0][0] * v[0][0] + o[2][0] * v[2][0] * o[0][1])
		+ (o[2][1] * o[1][0] * v[1][0] + o[2][0] * v[2][0] * o[1][1])
		+ 2 * (o[0][2] * v[0][0] + o[1][2] * v[1][0] + o[2][2] * v[2][0] - c[0]
			* (o[0][0] * v[0][0] + o[1][0] * v[1][0] + o[2][0] * v[2][0]) + c[1]
			* (o[2][0] * v[2][0] - o[0][0] * v[0][0] - o[1][0] * v[1][0])));
	t[0] = (o[0][1] + o[1][1] + o[2][1] + c[1] - c[0]) * (o[0][1] + o[1][1]
		+ o[2][1] + c[1] - c[0]) - 4 * c[1] * (o[0][1] + o[1][1]);
}

int				ray_intersect_torus(t_ray *ray, t_obj *obj)
{
	double	t[5];
	double	o[3][3];
	double	v[3][3];
	double	c[2];
	int		i;

	i = -1;
	while (++i < 9)
	{
		o[i / 3][i % 3] = pow(M_IJ(&(ray->start), i / 3, 0), (i % 3) + 1);
		v[i / 3][i % 3] = pow(M_IJ(&(ray->dir), i / 3, 0), (i % 3) + 1);
	}
	c[0] = obj->param.height * obj->param.height;
	c[1] = obj->param.radius * obj->param.radius;
	t[3] = get_t3(o, v);
	get_t4t2t1t0(t, o, v, c);
	ray->dist = solve_4_degree(t[4], t[3], t[2], t[1], t[0]);
	ray->dist = floorf(ray->dist * 1000) / 1000.0;
	if (ray->dist > 0)
		ray_solution_torus(ray, obj);
	return (0);
}
