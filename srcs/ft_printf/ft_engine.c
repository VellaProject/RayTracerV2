/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 02:35:02 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:00 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_func	g_func[] =
{
	{'s', &ft_print_string},
	{'c', &ft_print_char},
	{'r', &ft_print_roman},
	{'k', &ft_print_date},
	{'d', &ft_print_signed},
	{'i', &ft_print_signed},
	{'a', &ft_print_addr},
	{'p', &ft_print_unsigned},
	{'x', &ft_print_unsigned},
	{'o', &ft_print_unsigned},
	{'u', &ft_print_unsigned},
	{'b', &ft_print_unsigned},
	{0, 0}
};

static int	ft_getbase(char c)
{
	if (c == 'x' || c == 'p')
		return (16);
	if (c == 'o')
		return (8);
	if (c == 'b')
		return (2);
	return (10);
}

static void	ft_work(char **p, char c, t_pf_syntax *pf, va_list ap)
{
	int i;

	if (IS_UPPER(c))
	{
		pf->flags |= UPPERCASE;
		c ^= 0x20;
	}
	pf->base = ft_getbase(c);
	if (c == 'p')
	{
		pf->flags |= HEXPREP;
		pf->qualifier = 'l';
	}
	else if (c == 'g' || c == 'f' || c == 'e')
		return (ft_print_float(p, c, pf, ap));
	i = -1;
	while (g_func[++i].f != 0)
		if (c == g_func[i].c)
			return (g_func[i].f(p, pf, ap));
}

void		ft_prepadd(char **p, size_t n, t_pf_syntax *pf)
{
	uint8_t c;

	if (pf->flags & ZEROPAD)
		c = '0';
	else
		c = ' ';
	if (!(pf->flags & LEFT))
		while ((int)n < pf->width--)
			*((*p)++) = c;
}

void		ft_postpadd(char **p, size_t n, t_pf_syntax *pf)
{
	uint8_t c;

	if (pf->flags & ZEROPAD)
		c = '0';
	else
		c = ' ';
	while ((int)n < pf->width--)
		*((*p)++) = c;
}

void		ft_pf_engine(char *p, char const *format, va_list ap)
{
	t_pf_syntax pf;

	while (*format != 0)
	{
		if (*format != '%')
		{
			if (*format == '{')
				ft_print_color(&p, &format);
			else
				*p++ = *format++;
			continue;
		}
		format++;
		ft_preparse(&format, &pf, ap);
		if (ft_strchr("pkrdiobucsxXafgeG", *format))
			ft_work(&p, *format++, &pf, ap);
		else if (ft_strchr("KRDIOBUCSAFE", *format))
		{
			pf.qualifier = 'l';
			ft_work(&p, *format++ ^ 0x20, &pf, ap);
		}
		else
			*p++ = *format++;
	}
}
