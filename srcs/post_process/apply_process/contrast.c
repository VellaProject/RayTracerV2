/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contrast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 06:19:52 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define IN_CLAMP(x)	(((x) < 0) ? 0 : ((x) > 127) ? 127 : (x))

void	ft_apply_contrast(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;
	float		factor;
	t_ucolor	uc;
	int			contrast;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	uc.b = (image->data + offset)[0];
	uc.g = (image->data + offset)[1];
	uc.r = (image->data + offset)[2];
	contrast = 1;
	factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
	(image->data + offset)[0] = IN_CLAMP(factor * (uc.b - 128) + 128);
	(image->data + offset)[1] = IN_CLAMP(factor * (uc.g - 128) + 128);
	(image->data + offset)[2] = IN_CLAMP(factor * (uc.r - 128) + 128);
}
