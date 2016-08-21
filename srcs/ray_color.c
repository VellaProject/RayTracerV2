/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 13:45:28 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 21:59:30 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

static int		init_light_ray(t_ray *light, t_ray *ray, t_spot *spot)
{
	light->start = M_POINT(
			M_IJ(&(ray->intersection), 0, 0)
			+ ERROR * M_IJ(&(ray->normal), 0, 0),
			M_IJ(&(ray->intersection), 1, 0)
			+ ERROR * M_IJ(&(ray->normal), 1, 0),
			M_IJ(&(ray->intersection), 2, 0)
			+ ERROR * M_IJ(&(ray->normal), 2, 0));
	light->dir = M_DIR(
			M_IJ(&(spot->position), 0, 0) - M_IJ(&(light->start), 0, 0),
			M_IJ(&(spot->position), 1, 0) - M_IJ(&(light->start), 1, 0),
			M_IJ(&(spot->position), 2, 0) - M_IJ(&(light->start), 2, 0));
	mat_normalize(&(light->dir));
	light->obj = NULL;
	light->dist = 0;
	return (0);
}

#define CLAMP(x, y, z)		(((y) < (x)) ? (x) : ((y) > (z)) ? (z) : (y))

static int		get_diffuse(t_ray *ray, t_ray *light, t_spot *spot)
{
	double		dotprod;

	dotprod = mat_dot_product(&(light->dir), &(ray->normal));
	if (dotprod < 0)
		return (0);
	return (color_scale(ray->obj->param.color,
				dotprod * spot->param.diffuse * ray->obj->param.diffuse));
}

static int		get_specular(t_ray *ray, t_ray *light, t_spot *spot)
{
	t_matrix		tmp;
	double			dotprod;

	dotprod = mat_dot_product(&(light->dir), &(ray->normal));
	tmp = M_DIR(
			M_IJ(&(light->dir), 0, 0) - 2 *
			dotprod * M_IJ(&(ray->normal), 0, 0),
			M_IJ(&(light->dir), 1, 0) - 2 *
			dotprod * M_IJ(&(ray->normal), 1, 0),
			M_IJ(&(light->dir), 2, 0) - 2 *
			dotprod * M_IJ(&(ray->normal), 2, 0));
	dotprod = mat_dot_product(&tmp, &ray->dir);
	if (dotprod < 0)
		return (0);
	dotprod = pow(dotprod, ray->obj->param.shininess);
	return (color_scale(spot->param.color, dotprod
				* ray->obj->param.specular
				* spot->param.specular));
}

static int		get_spot(t_ray *ray, t_ray *light, t_spot *spot)
{
	int		color;

	color = get_diffuse(ray, light, spot);
	color = color_add(color, get_specular(ray, light, spot));
	return (color);
}

int				ray_color(t_ray *ray, t_env *e)
{
	double		spot_dist;
	int			color;
	t_list		*lst;
	t_ray		light;

	if (!ray->obj)
		return (e->background_color);
	if (!e->scene->spot)
		return (ray->obj->param.color);
	color = color_with_effect(ray);
	lst = e->scene->spot;
	while (lst)
	{
		init_light_ray(&light, ray, lst->content);
		ray_intersect(&light, e);
		spot_dist = 0;
		if (light.obj)
			spot_dist = mat_dist(&LST_CONTENT(lst, t_spot *)->position,
					&ray->intersection);
		if (!light.obj || spot_dist < light.dist)
			color = color_add(color, get_spot(ray, &light, lst->content));
		lst = lst->next;
	}
	color = color_nois_cool(ray, color);
	return (color);
}
