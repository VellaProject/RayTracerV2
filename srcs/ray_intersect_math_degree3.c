/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_math_degree3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 10:30:55 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:14:02 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_intersect_math.h"

static t_poly		ft_degree3_2(t_degree3 *t)
{
	t_poly	p;

	bzero((void *)&p, sizeof(t_poly));
	if (t->w < 0)
	{
		t->cos3a = ft_fdiv(t->q, 2 * sqrt(t->p_d3_e3));
		t->a = acos(t->cos3a) / 3;
		t->t = sqrt(t->z * 1.33333333333333);
		p.nval = 3;
		p.value[0] = t->t * cos(t->a) + t->k;
		p.value[1] = t->t * cos(t->a + DEGTORAD(120)) + t->k;
		p.value[2] = t->t * cos(t->a + DEGTORAD(240)) + t->k;
	}
	else
	{
		p.nval = 1;
		p.value[0] = (t->w == 0) ? 2 * cbrtf(t->q / 2) + t->k :
			cbrtf(t->q / 2 + sqrt(t->w)) +
			cbrtf(t->q / 2 - sqrt(t->w)) + t->k;
	}
	return (p);
}

static t_poly		ft_degree3_1(double c3, double c2, double c1, double c0)
{
	t_degree3	t;

	if (c2 != 0)
	{
		t.k = ft_fdiv(-c2, 3 * c3);
		t.z = ft_fdiv(3 * c3 * c1 - c2 * c2, -3 * c3 * c3);
		t.q = ft_fdiv(2 * CUB(c2) - 9 * c3 * c2 * c1 + 27 * SQU(c3) * c0,
				-27 * CUB(c3));
	}
	else
	{
		t.k = 0;
		t.z = ft_fdiv(-c1, c3);
		t.q = ft_fdiv(-c0, c3);
	}
	t.p_d3_e3 = t.z * t.z / 27 * t.z;
	t.w = t.q / 4 * t.q - t.p_d3_e3;
	return (ft_degree3_2(&t));
}

t_poly				ft_degree3(double c3, double c2, double c1, double c0)
{
	t_poly	quad;
	t_poly	p;
	int		i;

	bzero((void *)&p, sizeof(t_poly));
	if (c3 == 0)
		return (ft_degree2(c2, c1, c0));
	if (c2 == 0 && c1 == 0)
	{
		p.nval = 1;
		p.value[0] = cbrtf(ft_fdiv(-c0, c3));
		return (p);
	}
	if (c0 == 0)
	{
		i = 0;
		p.nval = 1;
		p.value[0] = 0;
		quad = ft_degree2(c3, c2, c1);
		while (i < quad.nval)
			p.value[p.nval++] = quad.value[i++];
		return (p);
	}
	return (ft_degree3_1(c3, c2, c1, c0));
}
