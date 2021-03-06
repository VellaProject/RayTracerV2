/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 22:20:50 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_parse_color(char const *color)
{
	char *p;

	p = 0;
	if (ft_strlen(color) == ft_strlen_func(color, &ft_isdigit))
		return (strtol(color, &p, 10));
	return (strtol(color, &p, 16));
}

int			ft_spot_parse_color(t_spot *spot, char const *line, size_t *count)
{
	char	**p;

	spot->param.color = 0;
	p = ft_strsplit_func(line, &ft_isspace);
	if (ft_tablen(p) == 5)
	{
		spot->param.color |= (uint8_t)(ft_parse_color(p[1]) & 0xFF) << 16;
		spot->param.color |= (uint8_t)(ft_parse_color(p[2]) & 0xFF) << 8;
		spot->param.color |= (uint8_t)(ft_parse_color(p[3]) & 0xFF);
		ft_tabdel(&p);
		return (P_COLOR);
	}
	if (ft_tablen(p) == 3)
	{
		spot->param.color = ft_parse_color(p[1]);
		ft_tabdel(&p);
		return (P_COLOR);
	}
	P_ERROR("COLOR", *count);
	ft_tabdel(&p);
	return (0);
}
