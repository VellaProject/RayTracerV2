/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_math_degree2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 10:30:55 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:00:47 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_intersect_math.h"

static int	ft_sign(double x)
{
	if (!x)
		return (0);
	return (x < 0 ? -1 : 1);
}

double		ft_fdiv(double a, double b)
{
	if (a == 0)
		return (0);
	if (b == 0)
		return (LARGE_VAL * ft_sign(a));
	if ((a + b) == a)
		return (LARGE_VAL * ft_sign(a) * ft_sign(b));
	return (a / b);
}

t_poly		ft_degree1(double c1, double c0)
{
	t_poly p;

	bzero((void *)&p, sizeof(t_poly));
	if (c1 == 0)
		p.nval = 0;
	else
	{
		p.nval = 1;
		p.value[0] = ft_fdiv(-c0, c1);
	}
	return (p);
}

t_poly		ft_degree2(double c2, double c1, double c0)
{
	t_poly	p;
	double	d;

	bzero((void *)&p, sizeof(t_poly));
	if (c2 == 0)
		return (ft_degree1(c1, c0));
	d = c1 * c1 - 4 * c2 * c0;
	if (d == 0)
	{
		p.nval = 1;
		p.value[0] = ft_fdiv(-c1, 2 * c2);
	}
	else
	{
		if (d < 0)
			p.nval = 0;
		else
		{
			p.nval = 2;
			p.value[0] = ft_fdiv(-c1 - sqrt(d), 2 * c2);
			p.value[1] = ft_fdiv(-c1 + sqrt(d), 2 * c2);
		}
	}
	return (p);
}

double		solve_2_degree(double a, double b, double c)
{
	double		tmp;
	double		res;

	if (fabs(a) < ERROR)
	{
		if (fabs(b) < ERROR)
			return (-1);
		res = -c / b;
	}
	else
	{
		tmp = b * b - 4 * a * c;
		if (tmp < 0)
			return (-1);
		tmp = sqrt(tmp);
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}
