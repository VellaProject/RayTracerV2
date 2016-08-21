/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <avella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:33:26 by avella            #+#    #+#             */
/*   Updated: 2016/06/26 18:36:12 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		return_solve_error(double b, double c, t_ray *ray)
{
	t_neg	*neg;
	double	res;

	if (fabs(b) < ERROR)
		return (-1);
	res = -c / b;
	neg = ray->neg;
	while (neg)
	{
		ray->front = neg->front;
		ray->back = neg->back;
		if (res >= ray->front && res <= ray->back)
			return (-1);
		neg = neg->next;
	}
	return (res);
}

double		return_solve_good(double front, double back,
		double res, t_ray *ray)
{
	t_neg	*neg;

	neg = ray->neg;
	while (neg)
	{
		ray->front = neg->front;
		ray->back = neg->back;
		if (front >= ray->front && front <= ray->back)
		{
			if (back >= ray->front && back <= ray->back)
				return (-1);
			return (back);
		}
		if (front < 0)
			if (back >= ray->front && back < ray->back)
				return (-1);
		neg = neg->next;
	}
	return (res);
}

double		solve_2_degree_neg(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;
	double		front;
	double		back;

	if (fabs(a) < ERROR)
		return (return_solve_error(b, c, ray));
	else
	{
		tmp = b * b - 4 * a * c;
		if (tmp < 0)
			return (-1);
		tmp = sqrt(tmp);
		front = (-b - tmp) / (2 * a);
		back = (-b + tmp) / (2 * a);
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
		return (return_solve_good(front, back, res, ray));
	}
}

double		solved(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;

	ray->front = 10000;
	ray->back = 10000;
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
		ray->front = (-b - tmp) / (2 * a);
		ray->back = (-b + tmp) / (2 * a);
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}
