/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 17:48:56 by igomez            #+#    #+#             */
/*   Updated: 2016/06/26 19:01:59 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <pthread.h>

#define DIST_X(x, i)	((WIN_WIDTH >> 1)- ((float)(x) - (i)))
#define DIST_Y(y, j)	((WIN_HEIGHT >> 1) - ((float)(y) - (j)))
#define ALIASING		(0.5)

static int	ft_table_color(int *color, int size)
{
	int i;
	int r;
	int g;
	int b;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < size)
	{
		r += (color[i] >> 16) & 0xff;
		g += (color[i] >> 8) & 0xff;
		b += (color[i] & 0xff);
		++i;
	}
	return (((r / size) << 16) | ((g / size) << 8) | (b / size));
}

static void	ye_i_know(t_env *e)
{
	e->in_refraction = 0;
	e->nb_reflexion = 0;
}

int			ft_calc_aliasing(t_env *e, int x, int y)
{
	float	i;
	float	j;
	t_ray	ray;
	int		color[9];
	int		u;

	u = 0;
	j = -ALIASING;
	while (j <= ALIASING)
	{
		i = -ALIASING;
		while (i <= ALIASING)
		{
			ray.start = M_POINT(0, 0, 0);
			ray.dir = M_DIR(DIST_TO_PROJ, DIST_X(x, i), DIST_Y(y, j));
			mat_normalize(&(ray.dir));
			ray_setup_camera(&ray, (t_cam *)e->scene->cam->content);
			ye_i_know(e);
			color[u++] = give_color(&ray, e);
			i += ALIASING;
		}
		j += ALIASING;
	}
	ft_draw_pix(TPIX(x, y, ft_table_color(color, 9)), e->screen);
	return (0);
}
