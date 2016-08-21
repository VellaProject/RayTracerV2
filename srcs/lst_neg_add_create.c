/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_neg_add_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 17:28:48 by avella            #+#    #+#             */
/*   Updated: 2016/06/27 22:38:19 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		(*g_intersect_neg[OBJ_NUMBER])(t_ray *) =
{
	&sphere_neg,
	&plane_neg,
	&cylinder_neg,
	&cone_neg
};

int		intersect_obj_neg(t_ray *ray, t_obj *obj)
{
	if ((uint32_t)obj->param.type > OBJ_NUMBER)
		return (0);
	return (g_intersect_neg[obj->param.type](ray));
}

t_neg	*create_lst_neg(t_ray *ray)
{
	t_neg *lst_neg;

	lst_neg = malloc(sizeof(t_neg));
	lst_neg->front = ray->front;
	lst_neg->back = ray->back;
	lst_neg->next = NULL;
	return (lst_neg);
}

void	add_neg(t_neg *tmp_lst, t_ray *ray)
{
	t_neg *new;

	while (tmp_lst->next)
		tmp_lst = tmp_lst->next;
	new = malloc(sizeof(t_neg));
	new->front = ray->front;
	new->back = ray->back;
	new->next = NULL;
	tmp_lst->next = new;
}

void	give_front_back(t_ray tmp, t_ray *ray)
{
	ray_setup_obj(&tmp, ray->lst_obj->content);
	intersect_obj_neg(&tmp, ray->lst_obj->content);
	ray->front = tmp.front;
	ray->back = tmp.back;
}

t_neg	*lst_neg_returned(t_ray *ray, t_env *e)
{
	t_neg	*lst_neg;
	t_obj	*ob;
	t_ray	tmp;
	t_neg	*tmp_lst;

	lst_neg = NULL;
	ray->lst_obj = e->scene->obj;
	while (ray->lst_obj)
	{
		tmp = *ray;
		ob = ray->lst_obj->content;
		if (ob)
			if (ob->param.negatif == true && neg_hyper_or_torus(ob) == 1)
			{
				give_front_back(tmp, ray);
				tmp_lst = lst_neg;
				if (!tmp_lst)
					lst_neg = create_lst_neg(ray);
				else
					add_neg(tmp_lst, ray);
			}
		ray->lst_obj = ray->lst_obj->next;
	}
	ray_cleanup_obj(ray, ray->obj);
	return (lst_neg);
}
