/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/26 20:09:58 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_parse_obj g_parse_compose[] =
{
	{"^.*<type>.*[A-Z]?.*</type>.*$", &ft_obj_parse_type},
	{"^.*<position>.*</position>.*$", &ft_obj_parse_position},
	{"^.*<angle>.*</angle>.*$", &ft_obj_parse_angle},
	{"^.*<scale>.*</scale>.*$", &ft_obj_parse_scale},
	{"^.*<ambiant>.*</ambiant>.*$", &ft_obj_parse_ambiant},
	{"^.*<diffuse>.*</diffuse>.*$", &ft_obj_parse_diffuse},
	{"^.*<specular>.*</specular>.*$", &ft_obj_parse_specular},
	{"^.*<shininess>.*</shininess>.*$", &ft_obj_parse_shininess},
	{"^.*<radius>.*</radius>.*$", &ft_obj_parse_radius},
	{"^.*<height>.*</height>.*$", &ft_obj_parse_height},
	{"^.*<color>.*</color>.*$", &ft_obj_parse_color},
	{"^.*<negatif>.*</negatif>.*$", &ft_obj_parse_negatif},
	{"^.*<reflection>.*</reflection>.*$", &ft_obj_parse_reflection},
	{"^.*<refraction>.*</refraction>.*$", &ft_obj_parse_refraction},
	{"^.*<transparancy>.*</transparancy>.*$", &ft_obj_parse_transparancy},
	{"^.*<effect>.*</effect>.*$", &ft_obj_parse_effect},
	{"^.*<texture>.*</texture>.*$", &ft_obj_parse_texture},
	{"^.*<limit>.*</limit>.*$", &ft_obj_parse_limit},
	{"^.*<limit2>.*</limit2>.*$", &ft_obj_parse_limit2},
	{0, 0}
};

static const t_key_value g_check[] =
{
	{"TYPE", P_TYPE},
	{"POSITION", P_POSITION},
	{"ANGLE", P_ANGLE},
	{"SCALE", P_SCALE},
	{"AMBIANT", P_AMBIANT},
	{"DIFFUSE", P_DIFFUSE},
	{"SPECULAR", P_SPECULAR},
	{"SHININESS", P_SHININESS},
	{"RADIUS", P_RADIUS},
	{"HEIGHT", P_HEIGHT},
	{"COLOR", P_COLOR},
	{"NEGATIF", P_NEGATIF},
	{"REFLECTION", P_REFLECTION},
	{"REFRACTION", P_REFRACTION},
	{"TRANSPARANCY", P_TRANSPARANCY},
	{"EFFECT", P_EFFECT},
	{"TEXTURE", P_TEXTURE},
	{"LIMIT", P_LIMIT},
	{"LIMIT2", P_LIMIT2},
	{0, 0}
};

static void	ft_handle_compose(t_env *e, t_obj *obj)
{
	if (obj->param.texture_file != 0)
	{
		obj->param.texture = image_new_xpm(e, obj->param.texture_file);
		ft_strdel(&obj->param.texture_file);
	}
	mat_setup(&obj->setup, &obj->position, &obj->ang, &obj->scale);
	mat_cleanup(&obj->cleanup, &obj->position, &obj->ang);
	ft_lstadd(&e->scene->obj, ft_lstnew(obj, sizeof(t_obj)));
}

static void	ft_init_composed(t_env *e, t_obj *obj)
{
	t_obj *obj_1;
	t_obj *obj_2;
	t_obj *obj_3;

	if ((obj_1 = (t_obj*)ft_memalloc(sizeof(t_obj))) != 0)
	{
		ft_memcpy(obj_1, obj, sizeof(t_obj));
		ft_init_cylinder(obj, obj_1);
		ft_handle_compose(e, obj_1);
	}
	if ((obj_2 = (t_obj*)ft_memalloc(sizeof(t_obj))) != 0)
	{
		ft_memcpy(obj_2, obj, sizeof(t_obj));
		ft_init_cone(obj_2);
		ft_handle_compose(e, obj_2);
	}
	if ((obj_3 = (t_obj*)ft_memalloc(sizeof(t_obj))) != 0)
	{
		ft_memcpy(obj_3, obj, sizeof(t_obj));
		ft_init_sphere(obj, obj_3);
		ft_handle_compose(e, obj_3);
	}
}

static void	ft_check_compose_parsed(t_env *e, t_obj *obj, int flag)
{
	size_t i;

	i = 0;
	while (g_check[i].key != 0)
	{
		if (!FLAG_GET(flag, g_check[i].value))
			ft_fprintf(2, "Object {cyan}%d{none}: {red}%s{none} is missing\n",
				obj->n, g_check[i].key);
		++i;
	}
	ft_init_composed(e, obj);
}

bool		ft_parse_compose(t_env *e, t_obj *obj, int fd, size_t *line_count)
{
	static char	*line = 0;
	static int	n = 0;
	int			flag;
	size_t		i;

	flag = 0;
	ft_bzero(obj, sizeof(t_obj));
	obj->n = ++n;
	while (get_next_line(fd, &line) > 0 && !ft_regex("^.*</compose>.*$", line))
	{
		i = 0;
		*line_count = *line_count + 1;
		while (g_parse_compose[i].key_pattern != 0)
		{
			if (ft_regex(g_parse_compose[i].key_pattern, line) != 0)
				flag |= g_parse_compose[i].func(obj, line, line_count);
			++i;
		}
		ft_strdel(&line);
	}
	if (line != 0)
		ft_strdel(&line);
	*line_count = *line_count + 1;
	ft_check_compose_parsed(e, obj, flag);
	return (true);
}
