/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 14:11:14 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 14:20:21 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "libft.h"
# include "rtv1_matrix.h"
# include <stdint.h>

# define OBJ_NUMBER		(6)

typedef enum		e_obj_type
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE,
	HYPERBOLOID,
	TORUS,
	VERRE
}					t_obj_type;

# define EFFECT_NB		(5)

typedef enum		e_effect
{
	EFFNONE = 0,
	NOISE,
	DAMIER,
	SINUS,
	COOL,
}					t_effect;

# define PROCESS_NB		(9)

typedef enum		e_process_type
{
	NONE = 0,
	GRAY,
	SHADE,
	GAMMA,
	CONTRAST,
	BRIGHT,
	INVERSE,
	NEAREST_256,
	NEAREST_16,
	SEPIA,
	ALL,
}					t_process_type;

typedef struct		s_obj_param
{
	t_obj_type		type;
	int				color;
	double			ambiant;
	double			diffuse;
	double			specular;
	double			shininess;
	double			radius;
	double			height;
	int				limit;
	int				limit2;
	double			limit_coeff;
	double			limit_coeff2;
	bool			negatif;
	double			reflection;
	double			refraction;
	double			transparancy;
	t_effect		effect;
	char			*texture_file;
	t_image			*texture;
	t_matrix		text_mod;
}					t_obj_param;

typedef struct		s_obj
{
	int				n;
	t_matrix		position;
	t_matrix		ang;
	t_matrix		scale;
	t_matrix		setup;
	t_matrix		cleanup;
	t_obj_param		param;
}					t_obj;

typedef struct		s_cam
{
	int				n;
	t_matrix		position;
	t_matrix		ang;
	t_matrix		setup;
}					t_cam;

typedef struct		s_spot_param
{
	double			diffuse;
	double			specular;
	int				color;
	double			intensity;
}					t_spot_param;

typedef struct		s_spot
{
	int				n;
	t_matrix		position;
	t_spot_param	param;
}					t_spot;

typedef struct		s_scene
{
	t_list			*cam;
	t_list			*obj;
	t_list			*spot;
}					t_scene;

t_scene				*new_scene(void);
t_obj				*new_obj(void);
t_spot				*new_spot(void);

typedef struct		s_neg
{
	double			front;
	double			back;
	struct s_neg	*next;
}					t_neg;

typedef struct		s_ray
{
	t_matrix		start;
	t_matrix		dir;
	t_obj			*obj;
	double			dist;
	t_matrix		intersection;
	t_matrix		normal;
	double			front;
	double			back;
	t_neg			*neg;
	t_list			*lst_obj;
}					t_ray;

typedef struct		s_vec3d
{
	double x;
	double y;
	double z;
}					t_vec3d;

typedef struct		s_perl
{
	int				x;
	int				y;
	int				z;
	double			u;
	double			v;
	double			w;
	int				a;
	int				aa;
	int				ab;
	int				b;
	int				ba;
	int				bb;
}					t_perl;

int					ray_intersect_sphere(t_ray *ray, t_obj *obj);
int					ray_intersect_plane(t_ray *ray, t_obj *obj);
int					ray_intersect_cone(t_ray *ray, t_obj *obj);
int					ray_intersect_cylinder(t_ray *ray, t_obj *obj);
int					ray_intersect_hyperboloid(t_ray *ray, t_obj *obj);
int					ray_intersect_torus(t_ray *ray, t_obj *obj);

typedef struct		s_ucolor
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_ucolor;

typedef struct		s_fcolor
{
	float			r;
	float			g;
	float			b;
}					t_fcolor;

#endif
