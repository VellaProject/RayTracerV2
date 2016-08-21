/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalc_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 17:48:56 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:49:38 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <pthread.h>

#define WIN_X	(WIN_WIDTH / 2)
#define WIN_Y	(WIN_HEIGHT / 2)

int			give_color(t_ray *ray, t_env *e)
{
	int color;

	ray_intersect(ray, e);
	color = ray_color(ray, e);
	color = color_reflexion(ray, e, color);
	color = color_refraction_transparancy(ray, e, color);
	return (color);
}

static void	refra_refle(t_env *e)
{
	e->in_refraction = 0;
	e->nb_reflexion = 0;
}

static void	*ft_engine_thread(void *env)
{
	static int	thread_id = 0;
	int			x;
	int			y;
	t_ray		ray;
	t_env		*e;

	y = thread_id++ % 4;
	e = (t_env *)env;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (e->anti_aliasing != 0.0 && !ft_calc_aliasing(e, x++, y))
				continue ;
			ray.start = M_POINT(0, 0, 0);
			ray.dir = M_DIR(DIST_TO_PROJ, WIN_X - x++, WIN_Y - y);
			here_we_go(&ray, e);
			refra_refle(e);
			ft_draw_pix(TPIX(x, y, give_color(&ray, e)), e->screen);
		}
		y += 4;
	}
	free(env);
	return (0);
}

static int	ft_mono_thread(t_env *e)
{
	int			x;
	int			y;
	t_ray		ray;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (e->anti_aliasing != 0.0 && !ft_calc_aliasing(e, x++, y))
				continue ;
			ray.start = M_POINT(0, 0, 0);
			ray.dir = M_DIR(DIST_TO_PROJ, WIN_X - x++, WIN_Y - y);
			mat_normalize(&(ray.dir));
			ray_setup_camera(&ray, (t_cam *)e->scene->cam->content);
			e->in_refraction = 0;
			e->nb_reflexion = 0;
			ft_draw_pix(TPIX(x, y, give_color(&ray, e)), e->screen);
		}
		++y;
	}
	return (0);
}

#define DAMIER(o)	(((t_obj *)((o)->content))->param.effect == DAMIER)
#define TEXTURE(o)	(((t_obj *)((o)->content))->param.texture != 0)

int			recalc_scene(t_env *e)
{
	pthread_t	tid[4];
	t_env		*ec[4];
	t_list		*obj;
	int			i;

	obj = e->scene->obj;
	while (obj != 0)
	{
		if (DAMIER(obj) || TEXTURE(obj))
			return (ft_mono_thread(e));
		obj = obj->next;
	}
	i = 0;
	while (i < 4)
	{
		if ((ec[i] = (t_env *)ft_memalloc(sizeof(t_env))) != NULL)
			pthread_create(&(tid[i]), NULL, ft_engine_thread,
					(void *)ft_memcpy(ec[i], e, sizeof(t_env)));
		i++;
	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	return (0);
}
