/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/26 20:13:35 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_handle_eye(t_env *e, t_cam *cam)
{
	mat_cleanup(&(cam->setup), &(cam->position), &(cam->ang));
	ft_lstadd(&e->scene->cam, ft_lstnew(cam, sizeof(t_cam)));
}

static void	ft_handle_obj(t_env *e, t_obj *obj)
{
	if (obj->param.texture_file != 0)
		obj->param.texture = image_new_xpm(e, obj->param.texture_file);
	mat_setup(&obj->setup, &obj->position, &obj->ang, &obj->scale);
	mat_cleanup(&obj->cleanup, &obj->position, &obj->ang);
	ft_lstadd(&e->scene->obj, ft_lstnew(obj, sizeof(t_obj)));
}

static void	ft_handle_spot(t_env *e, t_spot *spot)
{
	ft_lstadd(&e->scene->spot, ft_lstnew(spot, sizeof(t_spot)));
}

static bool	ft_set_eye(t_env *e)
{
	if (e->scene->cam == 0)
	{
		ft_fprintf(2, "There is no eye\n");
		return (false);
	}
	return (true);
}

bool		env_parse_file(t_env *e, int fd)
{
	t_obj	obj;
	t_spot	spot;
	t_cam	cam;
	char	*line;
	size_t	i;

	i = 0;
	e->background_color = COLOR_BACKGROUND;
	while (get_next_line(fd, &line) > 0 && ++i)
	{
		if (ft_regex("^.*<object>.*$", line) && ft_parse_object(&obj, fd, &i))
			ft_handle_obj(e, &obj);
		if (ft_regex("^.*<spot>.*$", line) && ft_parse_spot(&spot, fd, &i))
			ft_handle_spot(e, &spot);
		if (ft_regex("^.*<eye>.*$", line) && ft_parse_eye(&cam, fd, &i))
			ft_handle_eye(e, &cam);
		if (ft_regex("^.*<compose>.*$", line))
			ft_parse_compose(e, &obj, fd, &i);
		if (ft_regex("^.*<background>.*</background>.*$", line))
			ft_backround_parse_color(e, line, &i);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (ft_set_eye(e));
}
