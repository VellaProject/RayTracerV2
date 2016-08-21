/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 22:19:26 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	(*g_process[PROCESS_NB])(t_env *, int, int) =
{
	&ft_apply_gray,
	&ft_apply_shade,
	&ft_apply_gamma,
	&ft_apply_contrast,
	&ft_apply_brightness,
	&ft_apply_inverse,
	&ft_apply_nearest_256,
	&ft_apply_nearest_16,
	&ft_apply_sepia
};

static int	ft_get_value(t_env *e, int x)
{
	int	i;
	int	p;

	i = 0;
	p = e->screen->width / PROCESS_NB;
	while (i < PROCESS_NB - 1)
	{
		if (x < (p * (i + 1)))
			return (i);
		++i;
	}
	return (PROCESS_NB - 1);
}

void		ft_post_processing(t_env *e)
{
	int x;
	int y;

	if (e->post_process_type == 0 || e->post_process_type > PROCESS_NB + 1)
		return ;
	x = 0;
	while (x < e->screen->width)
	{
		y = 0;
		while (y < e->screen->height)
		{
			if (e->post_process_type == PROCESS_NB + 1)
				g_process[ft_get_value(e, x)](e, x, y);
			else
				g_process[e->post_process_type - 1](e, x, y);
			y++;
		}
		++x;
	}
}
