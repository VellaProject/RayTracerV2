/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 11:35:23 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 02:21:15 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_struct.h"
#include <stdlib.h>

#include "rtv1.h"

t_scene		*new_scene(void)
{
	t_scene		*scene;

	if (!(scene = (t_scene*)ft_memalloc(sizeof(t_scene))))
		return (NULL);
	return (scene);
}

t_obj		*new_obj(void)
{
	t_obj		*obj;

	if (!(obj = (t_obj*)ft_memalloc(sizeof(t_obj))))
		return (NULL);
	return (obj);
}

t_spot		*new_spot(void)
{
	t_spot		*spot;

	if (!(spot = (t_spot*)ft_memalloc(sizeof(t_spot))))
		return (NULL);
	return (spot);
}
