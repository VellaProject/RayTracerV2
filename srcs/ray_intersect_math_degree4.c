/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_math_degree4.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 10:30:55 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:29:07 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_intersect_math.h"

static t_poly		ft_degree4_3(t_degree4 *t, double hi_root)
{
	t_poly	quart[2];
	t_poly	p;
	int		i;
	int		j;

	bzero((void *)&p, sizeof(t_poly));
	p.nval = 0;
	if ((t->a2 = hi_root * hi_root) > t->a0)
	{
		i = -1;
		t->b = sqrt(t->a2 - t->a0);
		t->m = ft_fdiv(t->a3 * hi_root - t->a1, 2 * t->b);
		quart[0] = ft_degree2(1, t->a3 / 2 + t->m, hi_root + t->b);
		quart[1] = ft_degree2(1, t->a3 / 2 - t->m, hi_root - t->b);
		while (++i < 2)
		{
			j = -1;
			while (++j < quart[i].nval)
				p.value[p.nval++] = quart[i].value[j];
		}
	}
	return (p);
}

static t_poly		ft_degree4_2(double c[5])
{
	double		hi_root;
	t_poly		tmp;
	t_degree4	t;

	t.a3 = ft_fdiv(c[3], c[4]);
	t.a2 = ft_fdiv(c[2], c[4]);
	t.a1 = ft_fdiv(c[1], c[4]);
	t.a0 = ft_fdiv(c[0], c[4]);
	tmp = ft_degree3(-8, 4 * t.a2, 8 * t.a0 - 2 * t.a1 * t.a3,
			t.a1 * t.a1 - t.a0 * (4 * t.a2 - t.a3 * t.a3));
	hi_root = tmp.value[0];
	if (tmp.nval == 2 && tmp.value[1] > hi_root)
		hi_root = tmp.value[1];
	else if (tmp.nval == 3)
	{
		if (tmp.value[1] > tmp.value[2])
		{
			if (tmp.value[1] > hi_root)
				hi_root = tmp.value[1];
		}
		else if (tmp.value[2] > hi_root)
			hi_root = tmp.value[2];
	}
	return (ft_degree4_3(&t, hi_root));
}

static t_poly		ft_degree4_1(double c[5])
{
	t_poly	quart;
	t_poly	p;
	int		i;

	bzero((void *)&p, sizeof(t_poly));
	if (c[4] == 0)
		return (ft_degree3(c[3], c[2], c[1], c[0]));
	if (c[3] == 0 && c[2] == 0 && c[1] == 0)
	{
		p.nval = 1;
		p.value[0] = SQRT4(c[4]);
		return (p);
	}
	if (c[0] == 0)
	{
		i = 0;
		p.nval = 1;
		p.value[0] = 0;
		quart = ft_degree3(c[4], c[3], c[2], c[1]);
		while (i < quart.nval)
			if (quart.value[i++] != 0)
				p.value[p.nval++] = quart.value[i - 1];
		return (p);
	}
	return (ft_degree4_2(c));
}

double				solve_4_degree(double c4, ...)
{
	t_poly	p;
	va_list	ap;
	double	c[5];
	double	s;
	int		i;

	va_start(ap, c4);
	c[4] = c4;
	c[3] = (double)va_arg(ap, double);
	c[2] = (double)va_arg(ap, double);
	c[1] = (double)va_arg(ap, double);
	c[0] = (double)va_arg(ap, double);
	p = ft_degree4_1(c);
	va_end(ap);
	s = -1;
	i = 0;
	while (i < p.nval)
	{
		if (p.value[i] > 0 && (p.value[i] < s || s < 0))
			s = p.value[i];
		i++;
	}
	return (s);
}
