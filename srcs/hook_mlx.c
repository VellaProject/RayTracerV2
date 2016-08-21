/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:43:26 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx_encoding.h"
#include "mlx.h"

int			expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->screen->img, 0, 0);
	return (0);
}

int			loop_hook(t_env *e)
{
	if (FLAG_GET(e->flag, MASK_RECALC))
	{
		if (e->loading != 0)
		{
			mlx_destroy_image(e->mlx, e->loading);
			e->loading = 0;
		}
		recalc_scene(e);
		if (e->post_process_type != 0)
			ft_post_processing(e);
		FLAG_UNSET(e->flag, MASK_RECALC);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->screen->img, 0, 0);
	return (0);
}

static void	hook_norme(int k, t_env *e, t_cam *cam)
{
	if (k == KEYCODE_N)
		++M_IJ(&(cam->position), 0, 0);
	if (k == KEYCODE_M)
		--M_IJ(&(cam->position), 0, 0);
	if (k == KEYCODE_TAB)
		ft_build_scene(e);
}

static void	ft_hook(int k, t_env *e, t_cam *cam)
{
	if (k != KEYCODE_UP && k != KEYCODE_DOWN && k != KEYCODE_RIGHT
			&& k != KEYCODE_LEFT && k != KEYCODE_D && k != KEYCODE_S
			&& k != KEYCODE_W && k != KEYCODE_N && k != KEYCODE_M
			&& k != KEYCODE_A && k != KEYCODE_TAB)
		return ;
	if (k == KEYCODE_UP)
		++M_IJ(&(cam->position), 2, 0);
	if (k == KEYCODE_DOWN)
		--M_IJ(&(cam->position), 2, 0);
	if (k == KEYCODE_LEFT)
		++M_IJ(&(cam->position), 1, 0);
	if (k == KEYCODE_RIGHT)
		--M_IJ(&(cam->position), 1, 0);
	if (k == KEYCODE_W)
		M_IJ(&(cam->ang), 1, 0) -= 0.1;
	if (k == KEYCODE_S)
		M_IJ(&(cam->ang), 1, 0) += 0.1;
	if (k == KEYCODE_A)
		M_IJ(&(cam->ang), 2, 0) += 0.1;
	if (k == KEYCODE_D)
		M_IJ(&(cam->ang), 2, 0) -= 0.1;
	hook_norme(k, e, cam);
	mat_cleanup(&(cam->setup), &(cam->position), &(cam->ang));
	e->flag = MASK_RECALC;
}

int			key_hook(int k, t_env *e)
{
	if (k == KEYCODE_ESCAPE)
		ft_exit(0, e);
	if (k == KEYCODE_DELETE)
		ft_build_bmp(e);
	ft_hook(k, e, (t_cam *)e->scene->cam->content);
	return (0);
}
