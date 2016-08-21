/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 17:35:44 by avella            #+#    #+#             */
/*   Updated: 2016/06/27 22:20:47 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	floorf(float x)
{
	int r;

	if ((r = x) > 0)
		return (r);
	return (r - (r > x));
}

int		damier_color(t_ray *ray)
{
	t_vec3d		pos;
	int			color;

	pos.x = M_IJ(&(ray->start), 0, 0) + ray->dist * M_IJ(&(ray->dir), 0, 0);
	pos.y = M_IJ(&(ray->start), 1, 0) + ray->dist * M_IJ(&(ray->dir), 1, 0);
	pos.z = M_IJ(&(ray->start), 2, 0) + ray->dist * M_IJ(&(ray->dir), 2, 0);
	pos.x = floorf(pos.x / 2);
	pos.y = floorf(pos.y / 2);
	pos.z = floorf(pos.z / 2);
	if (fmod(pos.x + pos.z + pos.y, 2) == 0)
		color = 0x000000;
	else
		color = 0xffffff;
	return (color);
}

int		color_noise(t_ray *ray, int color)
{
	double xa;

	if (ray->obj->param.effect == NOISE)
	{
		xa = ft_fnoise(M_IJ(&(ray->intersection), 0, 0),
				M_IJ(&(ray->intersection), 1, 0),
				M_IJ(&(ray->intersection), 2, 0));
		color *= cos(20 * xa);
		if (((color >> 24) & 0xff) != 0)
			color = 0;
	}
	return (color);
}

int		color_cool(t_ray *ray, int color)
{
	double xa;
	double coef;

	if (ray->obj->param.effect == COOL)
	{
		xa = ft_fnoise(M_IJ(&(ray->intersection), 0, 0),
				M_IJ(&(ray->intersection), 1, 0),
				M_IJ(&(ray->intersection), 2, 0));
		coef = cos(M_IJ(&(ray->intersection), 0, 0) * xa);
		color = color_scale(color, coef);
		if (((color >> 24) & 0xff) != 0)
			color = 0;
	}
	return (color);
}

void	give_effect(t_ray *ray)
{
	if (ray->obj)
	{
		if (ray->obj->param.effect == DAMIER)
			ray->obj->param.color = damier_color(ray);
		if (ray->obj->param.effect == SINUS)
		{
			M_IJ(&(ray->normal), 0, 0) += sin(5);
			M_IJ(&(ray->normal), 1, 0) += sin(5);
			M_IJ(&(ray->normal), 2, 0) += sin(5);
		}
	}
}
