/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 06:33:22 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_apply_inverse(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	(image->data + offset)[0] = 255 - (uint8_t)(image->data + offset)[0];
	(image->data + offset)[1] = 255 - (uint8_t)(image->data + offset)[1];
	(image->data + offset)[2] = 255 - (uint8_t)(image->data + offset)[2];
}
