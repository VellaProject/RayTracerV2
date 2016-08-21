/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 06:32:34 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_apply_shade(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;
	float		factor;
	t_ucolor	uc;
	int			gray;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	uc.b = (image->data + offset)[0];
	uc.g = (image->data + offset)[1];
	uc.r = (image->data + offset)[2];
	factor = 255.f / 20.331f;
	gray = (int)((((uc.r + uc.b + uc.g) / 3) / factor) + 0.5) * factor;
	(image->data + offset)[0] = gray;
	(image->data + offset)[1] = gray;
	(image->data + offset)[2] = gray;
}
