/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 03:00:55 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:41 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_insert_sign(char **p, t_pf_syntax *pf, char sign, char *s)
{
	if (!(pf->flags & (ZEROPAD | LEFT)))
	{
		if (pf->flags & HEXPREP)
		{
			if (pf->base == 8)
				pf->width--;
			else if (pf->base == 16)
				pf->width -= 2;
		}
		while (pf->width-- > 0)
			*((*p)++) = ' ';
	}
	if (sign != 0)
		*((*p)++) = sign;
	if (!(pf->flags & HEXPREP))
		return ;
	if (pf->base == 8 || pf->base == 16)
	{
		pf->width--;
		*((*p)++) = '0';
	}
	if (pf->base != 16)
		return ;
	pf->width--;
	*((*p)++) = s[33];
}

static char	ft_insert_routine(char **p, uint64_t m, t_pf_syntax *pf, char *dgt)
{
	char sign;

	sign = 0;
	if (pf->flags & SIGN)
	{
		if (pf->flags & (NEGATIV | PLUS | SPACE))
			pf->width--;
		if (pf->flags & NEGATIV)
			sign = '-';
		else if (pf->flags & PLUS)
			sign = '+';
		else if (pf->flags & SPACE)
			sign = ' ';
	}
	if (m != 0)
	{
		while (m != 0)
		{
			*((*p)++) = dgt[m % pf->base];
			m /= pf->base;
		}
	}
	else
		*((*p)++) = '0';
	return (sign);
}

static void	ft_print_int(char **p, t_pf_syntax *pf, uint64_t n)
{
	char		tmp[100];
	char		*digit;
	char		sign;
	char		*s;
	int			i;

	if (pf->flags & UPPERCASE)
		digit = UPPER_DIGIT;
	else
		digit = LOWER_DIGIT;
	s = tmp;
	sign = ft_insert_routine(&s, (uint64_t)n, pf, digit);
	i = s - tmp;
	if (i > pf->precision)
		pf->precision = i;
	pf->width -= pf->precision;
	ft_insert_sign(p, pf, sign, digit);
	ft_prepadd(p, 0, pf);
	while (i < pf->precision--)
		*((*p)++) = '0';
	while (i-- > 0)
		*((*p)++) = tmp[i];
	ft_postpadd(p, 0, pf);
}

void		ft_print_unsigned(char **p, t_pf_syntax *pf, va_list ap)
{
	uint64_t n;

	if (pf->qualifier == 'H')
		n = (uint64_t)(uint8_t)va_arg(ap, int);
	else if (pf->qualifier == 'h')
		n = (uint64_t)(uint16_t)va_arg(ap, int);
	else if (pf->qualifier == 'L' || pf->qualifier == 'l')
		n = (uint64_t)(uint64_t)va_arg(ap, uint64_t);
	else if (pf->qualifier == 'z')
		n = (uint64_t)(size_t)va_arg(ap, uint64_t);
	else if (pf->qualifier == 'j')
		n = (uint64_t)(uintmax_t)va_arg(ap, uint64_t);
	else
		n = (uint64_t)(uint32_t)va_arg(ap, int);
	if (pf->flags & LEFT)
		pf->flags &= ~ZEROPAD;
	if (pf->base >= 2 || pf->base <= 36)
		ft_print_int(p, pf, n);
}

void		ft_print_signed(char **p, t_pf_syntax *pf, va_list ap)
{
	int64_t n;

	if (pf->qualifier == 'H')
		n = (int64_t)(int8_t)va_arg(ap, int);
	else if (pf->qualifier == 'h')
		n = (int64_t)(int16_t)va_arg(ap, int);
	else if (pf->qualifier == 'L' || pf->qualifier == 'l')
		n = (int64_t)va_arg(ap, int64_t);
	else if (pf->qualifier == 'z')
		n = (int64_t)(size_t)va_arg(ap, int64_t);
	else if (pf->qualifier == 'j')
		n = (int64_t)(intmax_t)va_arg(ap, int64_t);
	else
		n = (int64_t)(int32_t)va_arg(ap, int);
	pf->flags |= SIGN;
	if (n < 0)
	{
		n = -n;
		pf->flags |= NEGATIV;
	}
	if (pf->flags & LEFT)
		pf->flags &= ~ZEROPAD;
	if (pf->base >= 2 || pf->base <= 36)
		ft_print_int(p, pf, n);
}
