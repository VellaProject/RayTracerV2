/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_limit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 12:06:17 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/24 13:34:29 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		set_limit(int limit, t_ray *ray, t_obj *obj)
{
	t_matrix	tmp;
	t_matrix	tmp2;

	if (!ray || !ray->obj)
		return (0);
	if (limit == 0)
		return (0);
	else if (limit >= 4)
	{
		tmp2 = ray->intersection;
		M_IJ(&(tmp2), 0, 0) *= M_IJ(&(obj->scale), 0, 0);
		M_IJ(&(tmp2), 1, 0) *= M_IJ(&(obj->scale), 1, 0);
		M_IJ(&(tmp2), 2, 0) *= M_IJ(&(obj->scale), 2, 0);
		tmp = tmp2;
		mat_prod(&tmp2, &(obj->cleanup), &tmp);
		if (M_IJ(&(tmp2), (limit - 4), 0)
			> M_IJ(&(obj->position), (limit - 4), 0) + obj->param.limit_coeff)
			return (1);
		return (0);
	}
	else if (M_IJ(&(ray->start), (limit - 1), 0) + ray->dist
	* M_IJ(&(ray->dir), (limit - 1), 0) > obj->param.limit_coeff)
		return (1);
	else
		return (0);
}

int		check_limit(t_obj *obj)
{
	return (obj->param.limit);
}

int		set_limit2(int limit, t_ray *ray, t_obj *obj)
{
	t_matrix	tmp;
	t_matrix	tmp2;

	if (!ray || !ray->obj)
		return (0);
	if (limit == 0)
		return (0);
	else if (limit >= 4)
	{
		tmp2 = ray->intersection;
		M_IJ(&(tmp2), 0, 0) *= M_IJ(&(obj->scale), 0, 0);
		M_IJ(&(tmp2), 1, 0) *= M_IJ(&(obj->scale), 1, 0);
		M_IJ(&(tmp2), 2, 0) *= M_IJ(&(obj->scale), 2, 0);
		tmp = tmp2;
		mat_prod(&tmp2, &(obj->cleanup), &tmp);
		if (M_IJ(&(tmp2), (limit - 4), 0)
			< M_IJ(&(obj->position), (limit - 4), 0) + obj->param.limit_coeff2)
			return (1);
		return (0);
	}
	else if (M_IJ(&(ray->start), (limit - 1), 0) + ray->dist
	* M_IJ(&(ray->dir), (limit - 1), 0) < obj->param.limit_coeff2)
		return (1);
	else
		return (0);
}

int		check_limit2(t_obj *obj)
{
	return (obj->param.limit2);
}
