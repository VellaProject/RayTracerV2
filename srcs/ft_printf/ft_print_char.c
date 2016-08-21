/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 02:53:57 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:27:14 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_add_wchar(char **p, wchar_t wc)
{
	if (wc < 0x80)
		*((*p)++) = ((wc >> 0x00) & 0x7f) | 0x00;
	else if (wc < 0x0800)
	{
		*((*p)++) = ((wc >> 0x06) & 0x1f) | 0xc0;
		*((*p)++) = ((wc >> 0x00) & 0x3f) | 0x80;
	}
	else if (wc < 0x010000)
	{
		*((*p)++) = ((wc >> 0x0c) & 0x0f) | 0xe0;
		*((*p)++) = ((wc >> 0x06) & 0x3f) | 0x80;
		*((*p)++) = ((wc >> 0x00) & 0x3f) | 0x80;
	}
	else if (wc < 0x110000)
	{
		*((*p)++) = ((wc >> 0x12) & 0x07) | 0xf0;
		*((*p)++) = ((wc >> 0x0c) & 0x3f) | 0x80;
		*((*p)++) = ((wc >> 0x06) & 0x3f) | 0x80;
		*((*p)++) = ((wc >> 0x00) & 0x3f) | 0x80;
	}
}

static size_t	ft_wcsnlen(wchar_t const *s, size_t max)
{
	wchar_t const *p;

	p = s;
	while (*p && max-- > 0)
		++p;
	return ((size_t)(p - s));
}

void			ft_print_string(char **p, t_pf_syntax *pf, va_list ap)
{
	char	*s1;
	wchar_t	*s2;
	size_t	n;
	size_t	i;

	i = 0;
	if (pf->qualifier == 'l')
	{
		if ((s2 = (void *)va_arg(ap, wchar_t *)) == 0)
			s2 = L"(null)";
		n = ft_wcsnlen(s2, pf->precision);
		ft_prepadd(p, n, pf);
		while (i++ < n)
			ft_add_wchar(p, *s2++);
	}
	else
	{
		if ((s1 = (void *)va_arg(ap, char *)) == 0)
			s1 = "(null)";
		n = ft_strnlen(s1, pf->precision);
		ft_prepadd(p, n, pf);
		while (i++ < n)
			*((*p)++) = *s1++;
	}
	ft_postpadd(p, n, pf);
}

void			ft_print_char(char **p, t_pf_syntax *pf, va_list ap)
{
	ft_prepadd(p, 1, pf);
	if (pf->qualifier == 'l')
		ft_add_wchar(p, (wchar_t)va_arg(ap, wchar_t));
	else
		*((*p)++) = (uint8_t)va_arg(ap, int);
	ft_postpadd(p, 1, pf);
}
