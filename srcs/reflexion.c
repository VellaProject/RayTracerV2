/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:34:55 by avella            #+#    #+#             */
/*   Updated: 2016/06/26 18:26:03 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define REFLEXION_NUMBER 4

t_vec3d		ft_reflex(t_vec3d *incident, t_vec3d *n)
{
	t_vec3d v;

	v.x = incident->x - 2 * dot_product(n, incident) * n->x;
	v.y = incident->y - 2 * dot_product(n, incident) * n->y;
	v.z = incident->z - 2 * dot_product(n, incident) * n->z;
	return (v);
}

void		give_reflexion_ray(t_vec3d reflex, t_vec3d intersection,
		t_ray *ray, t_env *e)
{
	ray_setup_camera(ray, (t_cam *)e->scene->cam->content);
	M_IJ(&(ray->start), 0, 0) = intersection.x;
	M_IJ(&(ray->start), 1, 0) = intersection.y;
	M_IJ(&(ray->start), 2, 0) = intersection.z;
	M_IJ(&(ray->dir), 0, 0) = reflex.x;
	M_IJ(&(ray->dir), 1, 0) = reflex.y;
	M_IJ(&(ray->dir), 2, 0) = reflex.z;
}

void		our_reflexion_ray(t_ray *ray, t_env *e)
{
	t_vec3d reflex;
	t_vec3d incident;
	t_vec3d normal;
	t_vec3d intersection;

	intersection = (t_vec3d){M_IJ(&(ray->intersection), 0, 0),
		M_IJ(&(ray->intersection), 1, 0),
		M_IJ(&(ray->intersection), 2, 0)};
	incident = (t_vec3d){M_IJ(&(ray->dir), 0, 0),
		M_IJ(&(ray->dir), 1, 0),
		M_IJ(&(ray->dir), 2, 0)};
	normal = (t_vec3d){M_IJ(&(ray->normal), 0, 0),
		M_IJ(&(ray->normal), 1, 0),
		M_IJ(&(ray->normal), 2, 0)};
	reflex = ft_reflex(&incident, &normal);
	normalize(&reflex);
	normal.x *= 0.001;
	normal.y *= 0.001;
	normal.z *= 0.001;
	intersection.x += normal.x;
	intersection.y += normal.y;
	intersection.z += normal.z;
	give_reflexion_ray(reflex, intersection, ray, e);
}

int			color_reflexion(t_ray *ray, t_env *e, int color)
{
	int		color_tmp;
	double	reflection;

	if (e->nb_reflexion < REFLEXION_NUMBER && ray->obj
		&& ray->obj->param.reflection > 0)
	{
		e->nb_reflexion++;
		ray->obj->param.reflection = limit(ray->obj->param.reflection);
		reflection = 1 - ray->obj->param.reflection;
		our_reflexion_ray(ray, e);
		color = color_scale(color, reflection);
		color_tmp = give_color(ray, e);
		color_tmp = color_scale(color_tmp, 1 - reflection);
		color = color_add(color, color_tmp);
	}
	return (color);
}
