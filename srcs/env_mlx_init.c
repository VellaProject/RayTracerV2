/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mlx_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:38:09 by igomez            #+#    #+#             */
/*   Updated: 2015/03/18 14:36:29 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx.h"
#include <stdlib.h>

t_image				*image_new(t_env *e, int width, int height)
{
	t_image		*new;

	if (!(new = (t_image *)ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(new->img = mlx_new_image(e->mlx, width, height)))
		return (NULL);
	if (!(new->data = mlx_get_data_addr(new->img, &(new->bpp),
		&(new->size_line), &(new->endian))))
		return (NULL);
	new->width = width;
	new->height = height;
	new->bypp = new->bpp / 8;
	return (new);
}

t_image				*image_new_xpm(t_env *e, char const *filename)
{
	t_image *new;

	if ((new = (t_image *)ft_memalloc(sizeof(t_image))) == 0)
		return (0);
	new->img = mlx_xpm_file_to_image(e->mlx, (char *)filename,
					&(new->width), &(new->height));
	if (new->img == 0)
		return (0);
	if (!(new->data = mlx_get_data_addr(new->img, &(new->bpp),
		&(new->size_line), &(new->endian))))
		return (0);
	new->bypp = new->bpp / 8;
	return (new);
}

static int			env_mlx_init_hook(t_env *e)
{
	mlx_hook(e->win, 12, 1L << 15, expose_hook, e);
	mlx_hook(e->win, 2, 1L << 0, key_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	return (0);
}

int					env_mlx_init(t_env *e)
{
	e->width = WIN_WIDTH;
	e->height = WIN_HEIGHT;
	if (!(e->title = ft_strdup(TITLE)))
		return (-1);
	if (!(e->mlx = mlx_init()))
		return (-1);
	if (!(e->win = mlx_new_window(e->mlx, e->width, e->height, e->title)))
		return (-1);
	if (!(e->screen = image_new(e, e->width, e->height)))
		return (-1);
	env_mlx_init_hook(e);
	return (0);
}
