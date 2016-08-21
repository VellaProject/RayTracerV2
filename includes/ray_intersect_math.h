/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_math.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 19:05:07 by arthur            #+#    #+#             */
/*   Updated: 2016/06/27 22:55:25 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INTERSECT_MATH_H
# define RAY_INTERSECT_MATH_H

# include <math.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include "rtv1.h"
# define ERROR 0.000000001

typedef struct	s_poly
{
	int			nval;
	double		value[5];
}				t_poly;

typedef struct	s_degree3
{
	double		k;
	double		z;
	double		q;
	double		w;
	double		cos3a;
	double		t;
	double		p_d3_e3;
	double		a;
}				t_degree3;

typedef	struct	s_degree4
{
	double		m;
	double		b;
	double		a3;
	double		a2;
	double		a1;
	double		a0;
}				t_degree4;

# define LARGE_VAL (1e10)
# define SQRT4(x) (pow((x), 1.0 / 4.0))
# define CUB(x) ((x) * (x) * (x))
# define SQU(x) ((x) * (x))
# define MATH_PI (3.141592653589793238462643383279)
# define DEGTORAD(x) ((double)(x) * MATH_PI / 180.f)

double			ft_fdiv(double a, double b);
t_poly			ft_degree1(double c1, double c0);
t_poly			ft_degree2(double c2, double c1, double c0);
t_poly			ft_degree3(double c3, double c2, double c1, double c0);

#endif
