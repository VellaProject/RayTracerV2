/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 02:48:51 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:25 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>

static char const *const g_color[] =
{
	"{none}", "\033[0m",
	"{bold}", "\033[1m",
	"{black}", "\033[30m",
	"{red}", "\033[31m",
	"{green}", "\033[32m",
	"{yellow}", "\033[33m",
	"{blue}", "\033[34m",
	"{pink}", "\033[35m",
	"{magenta}", "\033[35m",
	"{cyan}", "\033[36m",
	"{bblack}", "\033[30;1m",
	"{bred}", "\033[31;1m",
	"{bgreen}", "\033[32;1m",
	"{byellow}", "\033[33;1m",
	"{bblue}", "\033[34;1m",
	"{bpink}", "\033[35;1m",
	"{bmagenta}", "\033[35;1m",
	"{bcyan}", "\033[36;1m",
	0, 0
};

void		ft_print_color(char **p, char const **format)
{
	char const	*s;
	int			i;

	i = 0;
	while (g_color[i] != 0)
	{
		if (ft_strncmp(*format, g_color[i], ft_strlen(g_color[i])) == 0)
		{
			s = g_color[i + 1];
			while (*s != 0)
				*((*p)++) = *s++;
			while (*((*format)++) != '}')
				continue ;
			return ;
		}
		i += 2;
	}
	*((*p)++) = *((*format)++);
}

static void	ft_print_roman_engine(char **p, uint16_t *n, uint16_t u,
														char const *s)
{
	char const *r;

	while (*n >= u)
	{
		r = s;
		while (*r != 0)
			*((*p)++) = *r++;
		*n = *n - u;
	}
}

void		ft_print_roman(char **p, t_pf_syntax *pf, va_list ap)
{
	uint16_t n;

	n = (uint16_t)va_arg(ap, int);
	if (pf->qualifier != 'l')
		n = (uint16_t)(uint8_t)n;
	ft_prepadd(p, 0, pf);
	if (n == 0)
	{
		*((*p)++) = '0';
		ft_postpadd(p, 0, pf);
	}
	ft_print_roman_engine(p, &n, 1000, "M");
	ft_print_roman_engine(p, &n, 900, "CM");
	ft_print_roman_engine(p, &n, 500, "D");
	ft_print_roman_engine(p, &n, 400, "CD");
	ft_print_roman_engine(p, &n, 100, "C");
	ft_print_roman_engine(p, &n, 90, "XC");
	ft_print_roman_engine(p, &n, 50, "L");
	ft_print_roman_engine(p, &n, 40, "XL");
	ft_print_roman_engine(p, &n, 10, "X");
	ft_print_roman_engine(p, &n, 9, "IX");
	ft_print_roman_engine(p, &n, 5, "V");
	ft_print_roman_engine(p, &n, 4, "IV");
	ft_print_roman_engine(p, &n, 1, "I");
	ft_postpadd(p, 0, pf);
}

void		ft_print_date(char **p, t_pf_syntax *pf, va_list ap)
{
	char	*s;
	time_t	t;
	char	c;
	size_t	n;

	t = va_arg(ap, time_t);
	s = ctime(&t);
	n = ft_strnlen(s, pf->precision);
	ft_prepadd(p, n, pf);
	if (pf->qualifier == 'l')
	{
		while ((c = *s++) != 0 && n--)
			if (!(c == '\n' || (ft_isspace(c) && ft_isspace(*s))))
				*((*p)++) = ft_toupper(c);
	}
	else
	{
		while ((c = *s++) != 0 && n--)
			if (!(c == '\n' || (ft_isspace(c) && ft_isspace(*s))))
				*((*p)++) = ft_tolower(c);
	}
	ft_postpadd(p, n, pf);
}
