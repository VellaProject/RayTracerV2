/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamma.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 03:16:54 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

void	ft_apply_gamma(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;
	t_ucolor	uc;
	t_fcolor	fc;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	uc.b = (image->data + offset)[0];
	uc.g = (image->data + offset)[1];
	uc.r = (image->data + offset)[2];
	fc.r = (float)uc.r / 255.0;
	fc.b = (float)uc.b / 255.0;
	fc.g = (float)uc.g / 255.0;
	(image->data + offset)[0] = powf(fc.b, 2.2) * 255.0;
	(image->data + offset)[1] = powf(fc.g, 2.2) * 255.0;
	(image->data + offset)[2] = powf(fc.r, 2.2) * 255.0;
	(void)e;
}
