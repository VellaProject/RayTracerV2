/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_eye.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 02:39:45 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_parse_eye g_parse_eye[] =
{
	{"^.*<position>.*</position>.*$", &ft_eye_parse_position},
	{"^.*<angle>.*</angle>.*$", &ft_eye_parse_angle},
	{0, 0}
};

static void	ft_check_eye_parsed(t_cam *cam, int flag)
{
	if (!FLAG_GET(flag, P_POSITION))
		ft_fprintf(2, "Eye %d ==>> position is missing\n", cam->n);
	if (!FLAG_GET(flag, P_ANGLE))
		ft_fprintf(2, "Eye %d ==>> angle is missing\n", cam->n);
}

bool		ft_parse_eye(t_cam *cam, int fd, size_t *line_count)
{
	static char	*line = 0;
	static int	n = 0;
	int			flag;
	size_t		i;

	flag = 0;
	ft_bzero(cam, sizeof(t_cam));
	cam->n = ++n;
	while (get_next_line(fd, &line) > 0 && !ft_regex("^.*</eye>.*$", line))
	{
		i = 0;
		*line_count = *line_count + 1;
		while (g_parse_eye[i].key_pattern != 0)
		{
			if (ft_regex(g_parse_eye[i].key_pattern, line) != 0)
				flag |= g_parse_eye[i].func(cam, line, line_count);
			++i;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	*line_count = *line_count + 1;
	cam->setup = M_NEW(4, 4);
	ft_check_eye_parsed(cam, flag);
	return (true);
}
