/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 14:31:48 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 22:49:58 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define TITLE 					("RT")
# define WIN_WIDTH				(1000)
# define WIN_HEIGHT 			(WIN_WIDTH)
# define DIST_TO_PROJ			(WIN_WIDTH / 2)

# define FLAG_GET(F, M)			(!!(F & M))
# define FLAG_SET(F, M)			(F |= M)
# define FLAG_UNSET(F, M)		(F &= ~M)
# define FLAG_TOGGLE(F, M)		(F ^= M)
# define FLAG_PRINT(F)			ft_flag_print(&F)
# define MASK_RECALC			(1U << 0)

# define ERROR					0.000000001
# define COLOR_BACKGROUND		0x0
# define INTENSITY_MIN			0.1

# include <time.h>
# include <math.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <wchar.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft.h"
# include "rtv1_matrix.h"
# include "rtv1_struct.h"

typedef struct			s_env
{
	int					in_refraction;
	int					nb_reflexion;
	t_obj				*obj_refraction;
	int					width;
	int					height;
	char				*title;
	void				*mlx;
	void				*win;
	t_image				*loading;
	t_image				*screen;
	int					flag;
	clock_t				c_old;
	clock_t				c_new;
	t_scene				*scene;
	int					background_color;
	t_process_type		post_process_type;
	double				anti_aliasing;
}						t_env;

int						ft_engine(int ac, char **av);
t_image					*image_new_xpm(t_env *e, char const *filename);
t_image					*image_new(t_env *e, int width, int height);
int						env_mlx_init(t_env *e);

void					clean_env(t_env *e);
void					ft_exit(int i, t_env *e);

int						expose_hook(t_env *e);
int						key_hook(int keycode, t_env *e);
int						loop_hook(t_env *e);

int						ft_calc_aliasing(t_env *e, int x, int y);
void					ft_build_scene(t_env *e);
void					ft_build_bmp(t_env *e);
int						recalc_scene(t_env	*e);

void					ft_post_processing(t_env *e);
int						ft_generate_new_name(char const *file);

void					ft_apply_nearest_256(t_env *e, int x, int y);
void					ft_apply_nearest_16(t_env *e, int x, int y);
void					ft_apply_brightness(t_env *e, int x, int y);
void					ft_apply_contrast(t_env *e, int x, int y);
void					ft_apply_inverse(t_env *e, int x, int y);
void					ft_apply_shade(t_env *e, int x, int y);
void					ft_apply_sepia(t_env *e, int x, int y);
void					ft_apply_gamma(t_env *e, int x, int y);
void					ft_apply_gray(t_env *e, int x, int y);
int						ray_setup_camera(t_ray *ray, t_cam *cam);
int						ray_setup_obj(t_ray *ray, t_obj *obj);
int						ray_cleanup_obj(t_ray *ray, t_obj *obj);
int						ray_intersect(t_ray *ray, t_env *e);
int						ray_color(t_ray *ray, t_env *e);
double					solve_2_degree(double a, double b, double c);
double					solve_4_degree(double t, ...);
int						set_limit(int limit, t_ray *ray, t_obj *obj);
int						set_limit2(int limit, t_ray *ray, t_obj *obj);
int						check_limit(t_obj *obj);
int						check_limit2(t_obj *obj);
int						color_scale(int c, double intensity);
int						color_add(int a, int b);

# define P_TYPE			(0x000001)
# define P_POSITION		(0x000002)
# define P_ANGLE		(0x000004)
# define P_SCALE		(0x000008)
# define P_AMBIANT		(0x000010)
# define P_DIFFUSE		(0x000020)
# define P_SPECULAR		(0x000040)
# define P_SHININESS	(0x000080)
# define P_COLOR		(0x000100)
# define P_NEGATIF 		(0x000200)
# define P_REFLECTION 	(0x000400)
# define P_REFRACTION 	(0x000800)
# define P_TRANSPARANCY (0x001000)
# define P_RADIUS		(0x002000)
# define P_HEIGHT		(0x004000)
# define P_INTENSITY	(0x008000)
# define P_EFFECT		(0x010000)
# define P_TEXTURE		(0x020000)
# define P_BACKGROUND	(0x040000)
# define P_LIMIT		(0x080000)
# define P_LIMIT2		(0x100000)

typedef struct			s_key_value
{
	char const			*key;
	int					value;
}						t_key_value;

typedef struct			s_key_fvalue
{
	char const			*key;
	double				value;
}						t_key_fvalue;

# define PRINT_ERROR	("Line: {red}%zu{none} -> Error [{red}%s{none}]\n")
# define P_ERROR(x, y)	ft_fprintf(2, PRINT_ERROR, y, x)

int						ft_obj_parse_position(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_type(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_scale(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_angle(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_ambiant(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_diffuse(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_specular(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_shininess(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_radius(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_height(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_color(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_negatif(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_reflection(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_refraction(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_transparancy(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_limit(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_limit2(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_texture(t_obj *obj,
		char const *line, size_t *count);
int						ft_obj_parse_effect(t_obj *obj,
		char const *line, size_t *count);
bool					ft_parse_object(t_obj *obj,
		int fd, size_t *line_count);
double					ft_atoi_double(const char *str);
bool					ft_parse_compose(t_env *e, t_obj *obj,
		int fd, size_t *line_count);
void					ft_init_cylinder(t_obj *verre, t_obj *cyl);
void					ft_init_cone(t_obj *cone);
void					ft_init_sphere(t_obj *verre, t_obj *sphere);
int						ft_spot_parse_color(t_spot *spot,
		char const *line, size_t *count);
int						ft_spot_parse_position(t_spot *spot,
		char const *line, size_t *count);
int						ft_spot_parse_diffuse(t_spot *spot,
		char const *line, size_t *count);
int						ft_spot_parse_specular(t_spot *spot,
		char const *line, size_t *count);
int						ft_spot_parse_intensity(t_spot *spot,
		char const *line, size_t *count);
bool					ft_parse_spot(t_spot *spot,
		int fd, size_t *line_count);

int						ft_eye_parse_position(t_cam *spot,
		char const *line, size_t *count);
int						ft_eye_parse_angle(t_cam *spot,
		char const *line, size_t *count);
bool					ft_parse_eye(t_cam *spot,
		int fd, size_t *line_count);

int						ft_backround_parse_color(t_env *e,
		char const *line, size_t *count);

typedef struct			s_parse_obj
{
	char const			*key_pattern;
	int					(*func)(t_obj *, char const *, size_t *);
}						t_parse_obj;

typedef struct			s_parse_spot
{
	char const			*key_pattern;
	int					(*func)(t_spot *, char const *, size_t *);
}						t_parse_spot;

typedef struct			s_parse_eye
{
	char const			*key_pattern;
	int					(*func)(t_cam *, char const *, size_t *);
}						t_parse_eye;

double					ft_get_double_value(char const *s);
bool					env_parse_file(t_env *e, int fd);
bool					env_parse_scene(t_env *e, int argc, char **argv);

typedef enum			e_type
{
	BEGIN = 0,
	END,
	DOT,
	STAR,
	PLUSS,
	QUEST,
	LIST,
	CHAR,
}						t_type;

typedef struct			s_regex
{
	t_type				type;
	char				c;
	bool				not;
	char				list[100];
	size_t				i;
	struct s_regex		*next;
}						t_regex;

static char const		*g_regex_match_start;
static char const		*g_regex_match_end;

# define INLIST(c, r)	(ft_is_in_list(c, NULL, r))
# define MATCH(r, s)	(r->type == DOT || *s == r->c || INLIST(*s, r))
# define NDUP(x, y)		ft_strsub(x, 0, y)

bool					ft_regex(char const *pattern, char const *s);
t_regex					*ft_regex_compile(char const *s);
bool					ft_matchhere(t_regex *r, char const *s);

# define CLAMP(x, y, z)	(((y) < (x)) ? (x) : ((y) > (z)) ? (z) : (y))

# define LEFT			(0x01)
# define PLUS			(0x02)
# define SPACE			(0x04)
# define HEXPREP		(0x08)
# define ZEROPAD		(0x10)
# define SIGN			(0x20)
# define UPPERCASE		(0x40)
# define NEGATIV		(0x80)

# define IS_UPPER(x)	((x) >= 'A' && (x) <= 'Z')

# define LOWER_DIGIT	("0123456789abcdefghijklmnopqrstuvwxyz")
# define UPPER_DIGIT	("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")

typedef struct			s_pf_syntax
{
	int					base;
	int					flags;
	int					width;
	int					precision;
	int					qualifier;
}						t_pf_syntax;

typedef struct			s_func
{
	char				c;
	void				(*f)(char **, t_pf_syntax *, va_list);
}						t_func;

typedef struct			s_float
{
	uint32_t			low;
	uint32_t			high;
}						t_float;

typedef struct			s_parsefloat
{
	char				*fdigits;
	char				cvtbuf[80];
	int					decpt;
	int					sign;
	int					exp;
	int					pos;
	int					capexp;
	int					magnitude;
	char				*p1;
	char				*p2;
	int					count;
	double				t1;
	double				t2;
}						t_parsefloat;

char					*ft_cvt(double arg, int ndigits,
		t_parsefloat *pf, int eflag);

void					ft_parse_float(double value, char *buffer,
		char c, t_pf_syntax *pf);

void					ft_print_float(char **p, char c,
		t_pf_syntax *pf, va_list ap);
void					ft_print_unsigned(char **p, t_pf_syntax *pf,
		va_list ap);
void					ft_print_signed(char **p, t_pf_syntax *pf, va_list ap);
void					ft_print_addr(char **p, t_pf_syntax *pf, va_list ap);
void					ft_print_string(char **p, t_pf_syntax *pf, va_list ap);
void					ft_print_char(char **p, t_pf_syntax *pf, va_list ap);
void					ft_print_roman(char **p, t_pf_syntax *pf, va_list ap);
void					ft_print_date(char **p, t_pf_syntax *pf, va_list ap);
void					ft_print_color(char **p, char const **format);

void					ft_preparse(char const **s, t_pf_syntax *pf,
		va_list ap);

void					ft_prepadd(char **p, size_t n, t_pf_syntax *pf);
void					ft_postpadd(char **p, size_t n, t_pf_syntax *pf);
void					ft_pf_engine(char *p, char const *format, va_list ap);

int						ft_vsnprintf(char *buf, size_t n,
		char const *format, va_list ap);
int						ft_vsprintf(char *buf, char const *format, va_list ap);
int						ft_sprintf(char *buf, char const *format, ...);
int						ft_fprintf(int fd, char const *format, ...);
int						ft_printf(char const *format, ...);
int						give_color(t_ray *ray, t_env *e);
int						color_refraction_transparancy(t_ray *ray,
						t_env *e, int color);
int						color_reflexion(t_ray *ray, t_env *e, int color);
double					dot_product(t_vec3d *a, t_vec3d *b);
void					normalize(t_vec3d *vec);
double					limit(double value);
int						sphere_neg(t_ray *ray);
int						plane_neg(t_ray *ray);
int						cylinder_neg(t_ray *ray);
int						cone_neg(t_ray *ray);
double					solve_2_degree_neg(double a, double b,
						double c, t_ray *ray);
void					give_front_back(t_ray tmp, t_ray *ray);
void					add_neg(t_neg *tmp_lst, t_ray *ray);
t_neg					*create_lst_neg(t_ray *ray);
int						intersect_obj_neg(t_ray *ray, t_obj *obj);
t_neg					*lst_neg_returned(t_ray *ray, t_env *e);
void					give_effect(t_ray *ray);
float					ft_fnoise(float x, float y, float z);
int						color_noise(t_ray *ray, int color);
int						color_cool(t_ray *ray, int color);
double					return_solve_error(double b, double c, t_ray *ray);
double					return_solve_good(double front, double back,
double					res, t_ray *ray);
double					solved(double a, double b, double c, t_ray *ray);
int						color_nois_cool(t_ray *ray, int color);
int						color_with_effect(t_ray *ray);
t_image					*image_new_xpm(t_env *e, char const *filename);
int						neg_hyper_or_torus(t_obj *ob);
void					here_we_go(t_ray *ray, t_env *e);
#endif
