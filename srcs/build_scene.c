/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:43:26 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define P_BOOL(x)	(((x) == true) ? "true" : "false")

static const char	*g_type[] =
{
	"SPHERE", "PLANE", "CYLINDER", "CONE", "HYPERBOLOID", "TORUS", 0
};

static const char	*g_effect[] =
{
	"none", "noise", "damier", "sinus", "cool", 0
};

static void	ft_print_obj_3(int fd, t_obj *s)
{
	ft_fprintf(fd, "\t\t<radius> %.2f </radius>\n",
		s->param.radius);
	ft_fprintf(fd, "\t\t<height> %.2f </height>\n",
		s->param.height);
	ft_fprintf(fd, "\t\t<limit> %d </limit>\n",
		s->param.limit);
	ft_fprintf(fd, "\t\t<limit2> %d </limit2>\n",
		s->param.limit2);
	ft_fprintf(fd, "\t\t<negatif> %s </negatif>\n",
		P_BOOL(s->param.negatif));
	ft_fprintf(fd, "\t\t<reflection> %.2f </reflection>\n",
		s->param.reflection);
	ft_fprintf(fd, "\t\t<refraction> %.2f </refraction>\n",
		s->param.refraction);
	ft_fprintf(fd, "\t\t<transparancy> %.2f </transparancy>\n",
		s->param.transparancy);
	if (s->param.texture != 0)
		ft_fprintf(fd, "\t\t<texture> %s %f %f %f %f </texture>\n",
			s->param.texture_file,
			M_IJ(&(s->param.text_mod), 0, 0),
			M_IJ(&(s->param.text_mod), 0, 1),
			M_IJ(&(s->param.text_mod), 1, 0),
			M_IJ(&(s->param.text_mod), 1, 1));
	ft_fprintf(fd, "\t\t<color> %#x </color>\n",
		s->param.color);
}

static void	ft_print_obj_2(int fd, t_obj *s)
{
	ft_fprintf(fd, "\t\t<type> %s </type>\n",
		g_type[s->param.type]);
	ft_fprintf(fd, "\t\t<position> %.2f %.2f %.2f </position>\n",
		M_IJ(&(s->position), 0, 0),
		M_IJ(&(s->position), 1, 0),
		M_IJ(&(s->position), 2, 0));
	ft_fprintf(fd, "\t\t<angle> %.2f %.2f %.2f </angle>\n",
		M_IJ(&(s->ang), 0, 0),
		M_IJ(&(s->ang), 1, 0),
		M_IJ(&(s->ang), 2, 0));
	ft_fprintf(fd, "\t\t<scale> %.2f %.2f %.2f </scale>\n",
		M_IJ(&(s->scale), 0, 0),
		M_IJ(&(s->scale), 1, 0),
		M_IJ(&(s->scale), 2, 0));
	ft_fprintf(fd, "\t\t<effect> %s </effect>\n",
		g_effect[s->param.effect]);
	ft_fprintf(fd, "\t\t<diffuse> %.2f </diffuse>\n",
		s->param.diffuse);
	ft_fprintf(fd, "\t\t<ambiant> %.2f </ambiant>\n",
		s->param.ambiant);
	ft_fprintf(fd, "\t\t<specular> %.2f </specular>\n",
		s->param.specular);
	ft_fprintf(fd, "\t\t<shininess> %.2f </shininess>\n",
		s->param.shininess);
}

static void	ft_print_obj(int fd, t_list *obj)
{
	t_list	*item;
	t_obj	*s;

	item = obj;
	while (item != 0)
	{
		ft_fprintf(fd, "\t<object>\n");
		s = (t_obj *)item->content;
		ft_print_obj_2(fd, s);
		ft_print_obj_3(fd, s);
		ft_fprintf(fd, "\t</object>\n");
		item = item->next;
	}
}

static void	ft_print_spot(int fd, t_list *spot)
{
	t_list *item;
	t_spot *s;

	item = spot;
	while (item != 0)
	{
		ft_fprintf(fd, "\t<spot>\n");
		s = (t_spot *)item->content;
		ft_fprintf(fd, "\t\t<position> %.2f %.2f %.2f </position>\n",
			M_IJ(&(s->position), 0, 0),
			M_IJ(&(s->position), 1, 0),
			M_IJ(&(s->position), 2, 0));
		ft_fprintf(fd, "\t\t<diffuse> %.2f </diffuse>\n",
			s->param.diffuse);
		ft_fprintf(fd, "\t\t<specular> %.2f </specular>\n",
			s->param.specular);
		ft_fprintf(fd, "\t\t<color> %#x </color>\n",
			s->param.color);
		ft_fprintf(fd, "\t\t<intensity> %.2f </intensity>\n",
			s->param.intensity);
		ft_fprintf(fd, "\t</spot>\n");
		item = item->next;
	}
}

void		ft_build_scene(t_env *e)
{
	int		fd;
	t_cam	*cam;

	cam = (t_cam *)e->scene->cam->content;
	fd = ft_generate_new_name(".generated_scene");
	ft_fprintf(fd, "<scene>\n");
	ft_fprintf(fd, "\t<background> %#x </background>\n", e->background_color);
	ft_fprintf(fd, "\t<eye>\n");
	ft_fprintf(fd, "\t\t<position> %.2f %.2f %.2f </position>\n",
		M_IJ(&(cam->position), 0, 0),
		M_IJ(&(cam->position), 1, 0),
		M_IJ(&(cam->position), 2, 0));
	ft_fprintf(fd, "\t\t<angle> %.2f %.2f %.2f </angle>\n",
		M_IJ(&(cam->ang), 0, 0),
		M_IJ(&(cam->ang), 1, 0),
		M_IJ(&(cam->ang), 2, 0));
	ft_fprintf(fd, "\t</eye>\n");
	ft_print_spot(fd, e->scene->spot);
	ft_print_obj(fd, e->scene->obj);
	ft_fprintf(fd, "</scene>\n");
	ft_printf("Done.\n");
	close(fd);
}
