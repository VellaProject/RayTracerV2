/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/27 02:22:54 by Zoellingam        #+#    #+#             */
/*   Updated: 2016/06/17 23:21:46 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_vsnprintf(char *buf, size_t n, char const *format, va_list ap)
{
	size_t r;

	ft_pf_engine(buf, format, ap);
	r = ft_strlen(buf);
	if (r > n)
		ft_bzero(buf + n, r - n);
	return (r);
}

int		ft_vsprintf(char *buf, char const *format, va_list ap)
{
	return (ft_vsnprintf(buf, 0x7fffffff, format, ap));
}

int		ft_sprintf(char *buf, char const *format, ...)
{
	va_list		ap;
	int			n;

	va_start(ap, format);
	n = ft_vsprintf(buf, format, ap);
	va_end(ap);
	return (n);
}

int		ft_fprintf(int fd, char const *format, ...)
{
	char		buf[0x1000];
	char		*p;
	va_list		ap;
	int			n;
	int			r;

	p = buf;
	ft_bzero((void *)buf, 0x1000);
	va_start(ap, format);
	n = ft_vsprintf(p, format, ap);
	va_end(ap);
	r = write(fd, p, ft_strlen(p));
	if (r != n)
		return (-1);
	return (n);
}

int		ft_printf(char const *format, ...)
{
	char		buf[0x1000];
	char		*p;
	va_list		ap;
	int			n;
	int			r;

	p = buf;
	ft_bzero((void *)buf, 0x1000);
	va_start(ap, format);
	n = ft_vsprintf(p, format, ap);
	va_end(ap);
	r = write(1, p, ft_strlen(p));
	if (r != n)
		return (-1);
	return (n);
}
