/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:00:28 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:14:34 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	(*g_intersect[OBJ_NUMBER])(t_ray *, t_obj *) =
{
	&ray_intersect_sphere,
	&ray_intersect_plane,
	&ray_intersect_cylinder,
	&ray_intersect_cone,
	&ray_intersect_hyperboloid,
	&ray_intersect_torus
};

static int	ray_iscloser(t_ray *ray_old, t_ray *ray_new)
{
	if (!ray_old->obj)
		return (1);
	if (ray_new->dist > 0 && ray_new->dist < ray_old->dist)
		return (1);
	return (0);
}

static int	ray_intersect_obj(t_ray *ray, t_obj *obj)
{
	if ((uint32_t)obj->param.type > OBJ_NUMBER)
		return (0);
	return (g_intersect[obj->param.type](ray, obj));
}

void		give_value_ray(t_ray *ray, t_ray tmp)
{
	ray->obj = tmp.obj;
	ray->dist = tmp.dist;
	ray->intersection = tmp.intersection;
	ray->normal = tmp.normal;
}

void		limit_or_no(t_env *e, t_ray *ray, t_ray tmp, t_list *lst)
{
	if (set_limit(check_limit(lst->content), &tmp, lst->content) == 0
			&& set_limit2(check_limit2(lst->content), &tmp, lst->content) == 0)
		if (tmp.obj && ray_iscloser(ray, &tmp))
		{
			if (e->in_refraction <= 0 || e->obj_refraction != tmp.obj)
				give_value_ray(ray, tmp);
		}
}

int			ray_intersect(t_ray *ray, t_env *e)
{
	t_list	*lst;
	t_ray	tmp;
	t_obj	*obj;

	lst = e->scene->obj;
	ray->neg = lst_neg_returned(ray, e);
	while (lst)
	{
		tmp = *ray;
		obj = lst->content;
		if (obj)
			if (obj->param.negatif == false || obj->param.type == HYPERBOLOID
			|| obj->param.type == TORUS)
			{
				ray_setup_obj(&tmp, lst->content);
				ray_intersect_obj(&tmp, lst->content);
				limit_or_no(e, ray, tmp, lst);
			}
		lst = lst->next;
	}
	ray_cleanup_obj(ray, ray->obj);
	return (0);
}
