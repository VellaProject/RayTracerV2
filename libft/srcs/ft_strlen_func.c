/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:46:04 by igomez            #+#    #+#             */
/*   Updated: 2016/06/17 01:14:23 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen_func(char const *s, int (*f)(int))
{
	char const *p;

	p = s;
	while (*s != 0 && f(*s) != 0)
		++s;
	return (s - p);
}
