/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 08:06:45 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:14 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_parse_float2(double value, t_pf_syntax *pf,
											t_parsefloat *p, char *c)
{
	if (pf->qualifier == 'l')
		p->capexp = 1;
	if (*c == 'g')
	{
		p->fdigits = ft_cvt(value, pf->precision, p, 1);
		p->magnitude = p->decpt - 1;
		if (p->magnitude < -4 || p->magnitude > pf->precision - 1)
		{
			*c = 'e';
			pf->precision -= 1;
		}
		else
		{
			*c = 'f';
			pf->precision -= p->decpt;
		}
	}
}

static char	*ft_parse_float3(double val, char *buf, t_pf_syntax *pf,
														t_parsefloat *p)
{
	p->fdigits = ft_cvt(val, pf->precision + 1, p, 1);
	if (p->sign)
		*buf++ = '-';
	*buf++ = *p->fdigits;
	if (pf->precision > 0)
		*buf++ = '.';
	ft_strncpy(buf, p->fdigits + 1, pf->precision);
	buf += pf->precision;
	*buf++ = p->capexp ? 'E' : 'e';
	if (p->decpt == 0)
		p->exp = -(val != 0.0);
	else
		p->exp = p->decpt - 1;
	if (p->exp < 0)
	{
		*buf++ = '-';
		p->exp = -p->exp;
	}
	else
		*buf++ = '+';
	*buf++ = ((p->exp / 10) % 10) + '0';
	*buf++ = (p->exp % 10) + '0';
	buf += 2;
	return (buf);
}

static char	*ft_parse_float4(char *buffer, t_parsefloat *p)
{
	if (p->decpt <= 0)
	{
		*buffer++ = '0';
		*buffer++ = '.';
		p->pos = 0;
		while (p->pos++ < -p->decpt)
			*buffer++ = '0';
		while (*p->fdigits)
			*buffer++ = *p->fdigits++;
	}
	else
	{
		p->pos = 0;
		while (*p->fdigits)
		{
			if (p->pos++ == p->decpt)
				*buffer++ = '.';
			*buffer++ = *p->fdigits++;
		}
	}
	return (buffer);
}

void		ft_parse_float(double value, char *buffer, char c, t_pf_syntax *pf)
{
	t_parsefloat p;

	ft_bzero((void *)&p, sizeof(p));
	ft_parse_float2(value, pf, &p, &c);
	if (c == 'e')
		buffer = ft_parse_float3(value, buffer, pf, &p);
	else if (c == 'f')
	{
		p.fdigits = ft_cvt(value, pf->precision, &p, 0);
		if (p.sign)
			*buffer++ = '-';
		if (*p.fdigits)
			buffer = ft_parse_float4(buffer, &p);
		else
		{
			*buffer++ = '0';
			if (pf->precision > 0)
			{
				*buffer++ = '.';
				while (pf->precision-- != 0)
					*buffer++ = '0';
			}
		}
	}
	*buffer = 0;
}
