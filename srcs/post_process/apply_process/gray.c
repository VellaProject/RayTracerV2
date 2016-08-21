/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 03:18:16 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_apply_gray(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;
	t_ucolor	uc;
	int			gray;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	uc.b = (image->data + offset)[0];
	uc.g = (image->data + offset)[1];
	uc.r = (image->data + offset)[2];
	gray = (uc.r * 0.299 + uc.g * 0.587 + uc.b * 0.114);
	(image->data + offset)[0] = gray;
	(image->data + offset)[1] = gray;
	(image->data + offset)[2] = gray;
}
