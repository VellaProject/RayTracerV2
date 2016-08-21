/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 22:21:50 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_parse_spot g_parse_spot[] =
{
	{"^.*<position>.*</position>.*$", &ft_spot_parse_position},
	{"^.*<diffuse>.*</diffuse>.*$", &ft_spot_parse_diffuse},
	{"^.*<specular>.*</specular>.*$", &ft_spot_parse_specular},
	{"^.*<color>.*</color>.*$", &ft_spot_parse_color},
	{"^.*<intensity>.*</intensity>.*$", &ft_spot_parse_intensity},
	{0, 0}
};

static void	ft_check_spot_parsed(t_spot *spot, int flag)
{
	if (!FLAG_GET(flag, P_POSITION))
		ft_fprintf(2, "Spot %d ==>> position is missing\n", spot->n);
	if (!FLAG_GET(flag, P_DIFFUSE))
		ft_fprintf(2, "Spot %d ==>> diffuse is missing\n", spot->n);
	if (!FLAG_GET(flag, P_SPECULAR))
		ft_fprintf(2, "Spot %d ==>> specular is missing\n", spot->n);
	if (!FLAG_GET(flag, P_COLOR))
		ft_fprintf(2, "Spot %d ==>> color is missing\n", spot->n);
	if (!FLAG_GET(flag, P_INTENSITY))
		ft_fprintf(2, "Spot %d ==>> intensity is missing\n", spot->n);
}

bool		ft_parse_spot(t_spot *spot, int fd, size_t *line_count)
{
	static char	*line = 0;
	static int	n = 0;
	int			flag;
	size_t		i;

	flag = 0;
	ft_bzero(spot, sizeof(t_spot));
	spot->n = ++n;
	while (get_next_line(fd, &line) > 0 && !ft_regex("^.*</spot>.*$", line))
	{
		i = 0;
		*line_count = *line_count + 1;
		while (g_parse_spot[i].key_pattern != 0)
		{
			if (ft_regex(g_parse_spot[i].key_pattern, line) != 0)
				flag |= g_parse_spot[i].func(spot, line, line_count);
			++i;
		}
		ft_strdel(&line);
	}
	if (line != 0)
		ft_strdel(&line);
	*line_count = *line_count + 1;
	ft_check_spot_parsed(spot, flag);
	return (true);
}
