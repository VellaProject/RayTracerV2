/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_transparancy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:57:47 by avella            #+#    #+#             */
/*   Updated: 2016/06/26 18:28:04 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3d		refract(t_vec3d *ray_dir, t_vec3d *normal, t_ray *ray)
{
	double	n;
	double	cosi;
	double	sint2;
	double	cost;
	t_vec3d	result;

	n = 1 / (1 + ray->obj->param.refraction);
	cosi = -1 * dot_product(normal, ray_dir);
	sint2 = n * n * (1.0 - cosi * cosi);
	if (sint2 > 1.0)
		return (*ray_dir);
	cost = sqrt(1.0 - sint2);
	result.x = n * ray_dir->x + (n * cosi - cost) * normal->x;
	result.y = n * ray_dir->y + (n * cosi - cost) * normal->y;
	result.z = n * ray_dir->z + (n * cosi - cost) * normal->z;
	return (result);
}

void		give_ray_refraction(t_ray *ray, t_vec3d ray_dir, t_env *e)
{
	ray_setup_camera(ray, (t_cam *)e->scene->cam->content);
	M_IJ(&(ray->dir), 0, 0) = ray_dir.x;
	M_IJ(&(ray->dir), 1, 0) = ray_dir.y;
	M_IJ(&(ray->dir), 2, 0) = ray_dir.z;
	M_IJ(&(ray->start), 0, 0) = M_IJ(&(ray->intersection), 0, 0);
	M_IJ(&(ray->start), 1, 0) = M_IJ(&(ray->intersection), 1, 0);
	M_IJ(&(ray->start), 2, 0) = M_IJ(&(ray->intersection), 2, 0);
}

int			color_scale_add(t_ray *ray, t_env *e,
		double transparancy, int color)
{
	int color_tmp;

	color = color_scale(color, transparancy);
	color_tmp = give_color(ray, e);
	color_tmp = color_scale(color_tmp, 1 - transparancy);
	color = color_add(color, color_tmp);
	return (color);
}

int			color_refraction_transparancy(t_ray *ray, t_env *e, int color)
{
	t_vec3d		ray_dir;
	t_vec3d		normal;
	double		transparancy;

	if (ray->obj && (ray->obj->param.refraction > 0 ||
				ray->obj->param.transparancy > 0))
	{
		ray->obj->param.refraction = limit(ray->obj->param.refraction);
		transparancy = 1 - ray->obj->param.transparancy;
		e->obj_refraction = ray->obj;
		e->in_refraction = 1;
		normal = (t_vec3d){M_IJ(&(ray->normal), 0, 0),
			M_IJ(&(ray->normal), 1, 0),
			M_IJ(&(ray->normal), 2, 0)};
		ray_dir = (t_vec3d){M_IJ(&(ray->dir), 0, 0),
			M_IJ(&(ray->dir), 1, 0),
			M_IJ(&(ray->dir), 2, 0)};
		ray_dir = refract(&ray_dir, &normal, ray);
		normalize(&ray_dir);
		give_ray_refraction(ray, ray_dir, e);
		color = color_scale_add(ray, e, transparancy, color);
	}
	return (color);
}
