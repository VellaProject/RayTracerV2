/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:31:30 by igomez            #+#    #+#             */
/*   Updated: 2016/06/27 14:00:15 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdbool.h>
# include <stdint.h>
# include "get_next_line.h"

# define STR_FORMAT(F1,F2,F3,STR)	"\e["F1";"F2";"F3"m"STR"\e[0m"
# define STR_FORMAT_SET(F1,F2,F3)	ft_putstr("\e["F1";"F2";"F3"m")
# define STR_FORMAT_DEFAULT			ft_putstr("\e[0m")
# define STR_DEFAULT 				"0"
# define STR_BOLD 					"1"
# define STR_UNDERLINE				"4"
# define STR_BLACK 					"30"
# define STR_RED 					"31"
# define STR_GREEN 					"32"
# define STR_YELLOW 				"33"
# define STR_BLUE 					"34"
# define STR_MAGENTA 				"35"
# define STR_CYAN					"36"
# define STR_GREY 					"37"

# define UNUSED(X)					((void)X)
# define LST_CONTENT(X, TYPE)		((TYPE)(X->content))
# define TPIX(x, y, z)				(t_pix){x, y, z}

/*
** Functions: error
*/

typedef	struct		s_message
{
	int		id;
	char	*msg;
}					t_message;

char				*ft_strmsg(int id, t_message *msg_list);

/*
** Functions: memory
*/

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

/*
** Functions: string
*/

size_t				ft_strlen(const char *s);
size_t				ft_strlen_func(const char *s, int (*f)(int));
size_t				ft_strnlen(char const *s, size_t max);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s,
						char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit_func(char const *s, int (*f)(int));
int					ft_strequ_nc(char const *s1, char const *s2);
char				**ft_strsplit_space(char const *s);
char				*ft_str_cleanpath(char *s);

/*
** Functions: print
*/

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putaddr(void *str);
void				ft_putaddr_fd(void *str, int fd);
void				ft_putnl(void);
void				ft_putnl_fd(int fd);

/*
** Functions: list
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstadd_back(t_list **alst, t_list *n);
size_t				ft_lstlen(t_list *lst);
void				ft_lstsort_merge(t_list **lst, int (*cmp)(void *, void *));
void				ft_lstrev(t_list **lspt_ptr);
void				ft_putlst(t_list *lst, void (*print)(void *));

/*
** Functions: flag
*/

int					ft_flag_get(int *flag, int mask);
int					ft_flag_set(int *flag, int mask);
int					ft_flag_unset(int *flag, int mask);
int					ft_flag_toggle(int *flag, int mask);
int					ft_flag_print(int *flag);

/*
** Functions: tab
*/

size_t				ft_tablen(char **tab);
char				**ft_tabnew(size_t size);
void				ft_tabdel(char ***tab_ptr);
char				**ft_tabdup(char **tab);
char				**ft_tabcpy(char **dst, char **src);
char				**ft_tabcat(char **dst, char **src);
int					ft_puttab(char **tab);

/*
** Functions: misc
*/

char				*ft_itoa(int n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isdigit_only(char *str);
int					ft_isspace(int c);
int					ft_intlen(int n);
int					ft_bitshift_r(int n, unsigned int size);
int					ft_bitshift_l(int n, unsigned int size);
int					ft_bitshift(int n, int n_bit, unsigned int size);
int					ft_iabs(int n);
int					ft_imin(int a, int b);
int					ft_imax(int a, int b);

/*
** Functions: Mini LibX
*/

typedef struct		s_image
{
	void			*img;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				bypp;
	int				size_line;
	int				endian;
}					t_image;

typedef struct		s_pix
{
	int				x;
	int				y;
	int				c;
}					t_pix;

t_pix				ft_pixnew(int x, int y, int c);
int					ft_draw_pix(t_pix p, t_image *image);
int					ft_draw_square(t_pix pos, t_pix delta, t_image *img);
int					ft_draw_img(t_pix p, t_image *src, t_image *dst);
int					ft_draw_getc(int x, int y, int *buf, t_image *img);
int					ft_draw_getp(double x, double y, t_pix *buf, t_image *img);

#endif
