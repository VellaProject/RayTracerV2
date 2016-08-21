/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 03:12:00 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:36 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_decimal_point(char *p)
{
	int n;

	while (*p != 0)
	{
		if (*p == '.')
			return ;
		if (*p == 'e')
			break ;
		p++;
	}
	if (*p != 0)
	{
		n = ft_strnlen(p, 256);
		while (n > 0)
		{
			p[n + 1] = p[n];
			n--;
		}
		*p = '.';
	}
	else
	{
		*p++ = '.';
		*p = 0;
	}
}

static void	ft_cropzeros(char *p)
{
	char *stop;

	while (*p != 0 && *p != '.')
		p++;
	if (*p++ != 0)
	{
		while (*p != 0 && *p != 'e')
			p++;
		stop = p--;
		while (*p == '0')
			p--;
		if (*p == '.')
			p--;
		while (p != stop)
			*++p = 0;
	}
}

static char	ft_get_sign(t_pf_syntax *pf, double f)
{
	char sign;

	sign = 0;
	if (pf->flags & SIGN)
	{
		if (f < 0.0)
		{
			sign = '-';
			pf->width--;
		}
		else if (pf->flags & PLUS)
		{
			sign = '+';
			pf->width--;
		}
		else if (pf->flags & SPACE)
		{
			sign = ' ';
			pf->width--;
		}
	}
	if (pf->precision < 0)
		pf->precision = 6;
	return (sign);
}

static void	ft_work_float(char **p, double f, t_pf_syntax *pf, char c)
{
	char	tmp[0x100];
	char	sign;
	int		n;
	int		i;

	sign = ft_get_sign(pf, f);
	if (f < 0.0)
		f = -f;
	ft_parse_float(f, tmp, c, pf);
	if ((pf->flags & HEXPREP) && pf->precision == 0)
		ft_decimal_point(tmp);
	if (c == 'g' && !(pf->flags & HEXPREP))
		ft_cropzeros(tmp);
	n = ft_strnlen(tmp, 256);
	pf->width -= n;
	if (!(pf->flags & (ZEROPAD | LEFT)))
		while (pf->width-- > 0)
			*((*p)++) = ' ';
	if (sign)
		*((*p)++) = sign;
	ft_prepadd(p, 0, pf);
	i = 0;
	while (i < n)
		*((*p)++) = tmp[i++];
	ft_postpadd(p, 0, pf);
}

void		ft_print_float(char **p, char c, t_pf_syntax *pf, va_list ap)
{
	pf->flags |= SIGN;
	if (pf->flags & LEFT)
		pf->flags &= ~ZEROPAD;
	ft_work_float(p, va_arg(ap, double), pf, c);
}
