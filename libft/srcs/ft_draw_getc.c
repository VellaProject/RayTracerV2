/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_getc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 11:00:07 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 14:01:04 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_draw_getc(int x, int y, int *buf, t_image *img)
{
	x %= img->width;
	y %= img->height;
	if (x < 0)
		x += img->width;
	if (y < 0)
		y += img->height;
	ft_memcpy(buf, img->data + img->bypp * (y * img->width + x), img->bypp);
	return (0);
}
