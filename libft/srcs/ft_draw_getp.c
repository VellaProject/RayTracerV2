/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_getp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 11:00:07 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 14:03:08 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_draw_getp(double x, double y, t_pix *buf, t_image *img)
{
	buf->x = (int)(x * img->width);
	buf->y = (int)(y * img->height);
	ft_draw_getc(buf->x, buf->y, &(buf->c), img);
	return (0);
}
