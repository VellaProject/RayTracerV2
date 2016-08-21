/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:23:19 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx.h"

void	init_textures(t_env *e)
{
	t_list	*iter;
	t_obj	*obj;

	iter = e->scene->obj;
	while (iter)
	{
		obj = LST_CONTENT(iter, t_obj*);
		if (obj->param.texture_file != NULL)
			obj->param.texture = image_new_xpm(e, obj->param.texture_file);
		iter = iter->next;
	}
}

int		ft_engine(int ac, char **av)
{
	t_env		e;

	ft_bzero((void *)&e, sizeof(e));
	if (env_mlx_init(&e) >= 0)
	{
		if ((e.scene = new_scene()) != 0)
		{
			if ((e.loading = image_new_xpm(&e, "scene/loading.xpm")) != 0)
				mlx_put_image_to_window(e.mlx, e.win, e.loading->img, 0, 0);
			if (env_parse_scene(&e, ac, av) == true)
			{
				init_textures(&e);
				FLAG_SET(e.flag, MASK_RECALC);
				mlx_loop(e.mlx);
			}
		}
	}
	ft_exit(0, &e);
	return (0);
}
