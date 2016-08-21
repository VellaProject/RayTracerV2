/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 02:35:06 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:09 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_preparse_precision(char const **s, t_pf_syntax *pf, va_list ap)
{
	(*s)++;
	if (**s == '*')
	{
		(*s)++;
		pf->precision = va_arg(ap, int);
	}
	else
	{
		pf->precision = 0;
		while (ft_isdigit(**s))
			pf->precision = pf->precision * 10 + *((*s)++) - '0';
	}
}

static void	ft_preparse_width(char const **s, t_pf_syntax *pf, va_list ap)
{
	int i;

	if (**s == '*')
	{
		(*s)++;
		i = va_arg(ap, int);
		if (i >= 0)
			pf->width = i;
		else if (i < 0)
		{
			pf->width = -i;
			pf->flags |= LEFT;
		}
	}
	else
	{
		pf->width = 0;
		while (ft_isdigit(**s))
			pf->width = pf->width * 10 + *((*s)++) - '0';
	}
}

static void	ft_preparse_flags(char c, t_pf_syntax *pf)
{
	if (c == '-')
		pf->flags |= LEFT;
	else if (c == '+')
		pf->flags |= PLUS;
	else if (c == ' ')
		pf->flags |= SPACE;
	else if (c == '#')
		pf->flags |= HEXPREP;
	else if (c == '0')
		pf->flags |= ZEROPAD;
}

static void	ft_preparse_qualifier(char c, t_pf_syntax *pf)
{
	if (pf->qualifier == -1)
		pf->qualifier = c;
	else if (c == 'l' || c == 'h')
		pf->qualifier ^= 0x20;
}

void		ft_preparse(char const **s, t_pf_syntax *pf, va_list ap)
{
	ft_bzero((void *)pf, sizeof(t_pf_syntax));
	pf->base = 10;
	pf->width = -1;
	pf->qualifier = -1;
	pf->precision = -1;
	while (ft_strchr("-+ #0", **s))
		ft_preparse_flags(*((*s)++), pf);
	while (ft_isdigit(**s) == true || **s == '*')
		ft_preparse_width(s, pf, ap);
	if (**s == '.')
		ft_preparse_precision(s, pf, ap);
	while (ft_strchr("hljz", **s))
		ft_preparse_qualifier(*((*s)++), pf);
}
