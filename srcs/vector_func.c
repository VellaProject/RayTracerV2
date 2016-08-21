/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:57:20 by avella            #+#    #+#             */
/*   Updated: 2016/06/26 18:46:13 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		dot_product(t_vec3d *a, t_vec3d *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

void		normalize(t_vec3d *vec)
{
	double n;

	n = 1.0 / sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	vec->x *= n;
	vec->y *= n;
	vec->z *= n;
}

double		limit(double value)
{
	if (value < 0)
		value = 0;
	if (value > 1)
		value = 1;
	return (value);
}
