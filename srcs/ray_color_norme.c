/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_norme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 19:31:46 by avella            #+#    #+#             */
/*   Updated: 2016/06/27 22:49:28 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		color_nois_cool(t_ray *ray, int color)
{
	color = color_noise(ray, color);
	color = color_cool(ray, color);
	return (color);
}

int		color_with_effect(t_ray *ray)
{
	int color;

	give_effect(ray);
	color = color_scale(ray->obj->param.color, ray->obj->param.ambiant);
	return (color);
}

void	here_we_go(t_ray *ray, t_env *e)
{
	mat_normalize(&(ray->dir));
	ray_setup_camera(ray, (t_cam *)e->scene->cam->content);
}
