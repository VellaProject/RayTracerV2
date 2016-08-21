/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 07:30:35 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define N_ABS(x)	(((x) < 0) ? -(x) : (x))

static const int g_data1[] =
{
	0x000000, 0x800000, 0x008000, 0x808000,
	0x000080, 0x800080, 0x008080, 0x808080,
	0xFF0000, 0x00FF00, 0xFFFF00, 0x0000FF,
	0xFF00FF, 0x00FFFF, 0xC0C0C0, 0xFFFF00
};

static int	ft_find_nearest_16(uint8_t r, uint8_t g, uint8_t b)
{
	int dist;
	int new_dist;
	int i;
	int c[3];
	int nearest;

	nearest = 0;
	dist = 255 * 255 + 255 * 255 + 255 * 255 + 1;
	i = 0;
	while (i < 16)
	{
		c[0] = N_ABS(r - (uint8_t)((g_data1[i] >> 16) & 0xff));
		c[1] = N_ABS(g - (uint8_t)((g_data1[i] >> 8) & 0xff));
		c[2] = N_ABS(b - (uint8_t)((g_data1[i]) & 0xff));
		new_dist = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
		if (new_dist < dist)
		{
			dist = new_dist;
			nearest = g_data1[i];
		}
		++i;
	}
	return (nearest);
}

void		ft_apply_nearest_16(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;
	t_ucolor	uc;
	int			new;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	uc.b = (image->data + offset)[0];
	uc.g = (image->data + offset)[1];
	uc.r = (image->data + offset)[2];
	new = ft_find_nearest_16(uc.r, uc.g, uc.b);
	(image->data + offset)[0] = (uint8_t)((new) & 0xff);
	(image->data + offset)[1] = (uint8_t)((new >> 8) & 0xff);
	(image->data + offset)[2] = (uint8_t)((new >> 16) & 0xff);
}
