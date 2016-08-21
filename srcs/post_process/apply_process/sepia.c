/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 21:50:43 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define IN_CLAMP(x)	(((x) < 0) ? 0 : ((x) > 255) ? 255 : (x))

void	ft_apply_sepia(t_env *e, int x, int y)
{
	int			offset;
	t_image		*image;
	t_ucolor	fc;
	t_fcolor	uc;

	image = e->screen;
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	offset = (y * image->width + x) * image->bypp;
	uc.b = (float)(image->data + offset)[0];
	uc.g = (float)(image->data + offset)[1];
	uc.r = (float)(image->data + offset)[2];
	fc.b = (uint8_t)(0.272 * uc.r + 0.534 * uc.g + 0.131 * uc.b);
	fc.g = (uint8_t)(0.349 * uc.r + 0.686 * uc.g + 0.168 * uc.b);
	fc.r = (uint8_t)(0.393 * uc.r + 0.769 * uc.g + 0.189 * uc.b);
	(image->data + offset)[0] = IN_CLAMP(fc.b);
	(image->data + offset)[1] = IN_CLAMP(fc.g);
	(image->data + offset)[2] = IN_CLAMP(fc.r);
}
