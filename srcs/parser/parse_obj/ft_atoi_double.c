/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <vle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:35:04 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/24 12:33:30 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_pow(float x, unsigned int power)
{
	double	result;

	result = 1;
	if (power == 0)
		return (0);
	else
	{
		while (power > 0)
		{
			result = result * x;
			power--;
		}
	}
	return (result);
}

static int		ft_isspace_limit(char c)
{
	if (c == '\t' || c == '\r' || c == '\v' || c == '\f' || c == '\n')
		return (1);
	else if (c == ' ')
		return (1);
	else
		return (0);
}

double			ft_post_point(const char *str, double nbr, int i)
{
	int		j;

	i++;
	j = 1;
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		nbr = nbr + (ft_pow(0.1f, j) * (double)(str[i] - 48));
		i++;
		j++;
	}
	return (nbr);
}

double			ft_atoi_double(const char *str)
{
	int		i;
	double	nbr;
	double	neg;

	i = 0;
	nbr = 0.0f;
	neg = 1.0f;
	while (ft_isspace_limit(str[i]) == 1)
		i++;
	if (str[i] == '-')
		neg = -1.0f;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		nbr = 0.0f;
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		nbr = nbr * 10 + (double)(str[i] - 48);
		i++;
	}
	if (str[i] == '.')
		nbr = ft_post_point(str, nbr, i);
	nbr = nbr * neg;
	return (nbr);
}
