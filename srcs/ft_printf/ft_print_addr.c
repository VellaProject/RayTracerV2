/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 02:27:32 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:18 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_print_v6addr(char **p, uint8_t *addr, t_pf_syntax *pf)
{
	char	tmp[24];
	char	*digit;
	int		i;
	int		n;

	if (pf->flags & UPPERCASE)
		digit = UPPER_DIGIT;
	else
		digit = LOWER_DIGIT;
	n = 0;
	i = 0;
	while (i < 6)
	{
		if (i != 0)
			tmp[n++] = ':';
		tmp[n++] = digit[addr[i] >> 0x04];
		tmp[n++] = digit[addr[i++] & 0xf];
	}
	ft_prepadd(p, n, pf);
	i = 0;
	while (i < n)
		*((*p)++) = tmp[i++];
	ft_postpadd(p, n, pf);
}

static void	ft_fill_v4addr(char **p, uint8_t *addr)
{
	char	*digit;
	int		i;
	int		n;

	i = 0;
	digit = LOWER_DIGIT;
	while (i < 4)
	{
		if (i != 0)
			*((*p)++) = '.';
		n = addr[i++];
		if (n >= 100)
		{
			*((*p)++) = digit[n / 100];
			n %= 100;
		}
		if (n >= 10)
		{
			*((*p)++) = digit[n / 10];
			n %= 10;
		}
		*((*p)++) = digit[n];
	}
}

static void	ft_print_v4addr(char **p, uint8_t *addr, t_pf_syntax *pf)
{
	char	tmp[24];
	char	*s;
	int		i;

	s = tmp;
	ft_fill_v4addr(&s, addr);
	ft_prepadd(p, s - tmp, pf);
	i = 0;
	while (i < (s - tmp))
		*((*p)++) = tmp[i++];
	ft_postpadd(p, s - tmp, pf);
}

void		ft_print_addr(char **p, t_pf_syntax *pf, va_list ap)
{
	uint8_t *s;

	s = va_arg(ap, uint8_t *);
	if (pf->qualifier == 'l')
		ft_print_v6addr(p, s, pf);
	else
		ft_print_v4addr(p, s, pf);
}
