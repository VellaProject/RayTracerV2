/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 22:12:50 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_key_value	g_process[] =
{
	{"gray", GRAY},
	{"gamma", GAMMA},
	{"contrast", CONTRAST},
	{"shade", SHADE},
	{"brightness", BRIGHT},
	{"inverse", INVERSE},
	{"reverse", INVERSE},
	{"nearest16", NEAREST_16},
	{"nearest256", NEAREST_256},
	{"sepia", SEPIA},
	{"all", ALL},
	{0, 0}
};

static int	ft_get_processing_type(char const *s)
{
	size_t i;

	i = 0;
	while (g_process[i].key != 0)
	{
		if (ft_strequ_nc(s, g_process[i].key) != 0)
			return (g_process[i].value);
		++i;
	}
	ft_fprintf(2, "Unknow post processing methode\n");
	return (0);
}

static bool	ft_check_access(char const *file)
{
	struct stat s;

	if (0 == file || !*file)
	{
		ft_fprintf(2, "Invalid file: {red}%s{none}\n", file);
		return (false);
	}
	if (-1 == stat(file, &s))
	{
		ft_fprintf(2, "File does not exist: {red}%s{none}\n", file);
		return (false);
	}
	if (S_ISDIR(s.st_mode))
	{
		ft_fprintf(2, "{red}%s{none} is a directory\n", file);
		return (false);
	}
	if (-1 == access(file, R_OK))
	{
		ft_fprintf(2, "Permission denied: {red}%s{none}\n");
		return (false);
	}
	return (true);
}

static void	ft_print_error(void)
{
	ft_fprintf(2, "Usage: ./rt --anti_aliasing ");
	ft_fprintf(2, "--post-process=type <scene>\n");
	ft_fprintf(2, "type:\n", 2);
	ft_fprintf(2, "\t--post-process={red}gray{none}\n");
	ft_fprintf(2, "\t--post-process={red}gamma{none}\n");
	ft_fprintf(2, "\t--post-process={red}shade{none}\n");
	ft_fprintf(2, "\t--post-process={red}sepia{none}\n");
	ft_fprintf(2, "\t--post-process={red}inverse{none}\n");
	ft_fprintf(2, "\t--post-process={red}contrast{none}\n");
	ft_fprintf(2, "\t--post-process={red}brightness{none}\n");
	ft_fprintf(2, "\t--post-process={red}nearest16{none}\n");
	ft_fprintf(2, "\t--post-process={red}nearest256{none}\n");
}

bool		env_parse_scene(t_env *e, int argc, char **argv)
{
	int fd;

	if (argc == 1 || (argc == 2 && ft_strnequ(argv[1], "--post-process=", 15)))
	{
		ft_fprintf(2, "Parse error, no file\n");
		return (false);
	}
	while (true)
	{
		if (ft_strnequ(*++argv, "--post-process=", 15) != 0)
			e->post_process_type = ft_get_processing_type(*argv + 15);
		else if (ft_strequ(*argv, "--anti-aliasing") != 0)
			e->anti_aliasing = true;
		else
			break ;
	}
	if (ft_strequ(*argv, "--help") == 0)
	{
		if (ft_check_access(*argv) == false)
			return (false);
		if ((fd = open(*argv, O_RDONLY)) > 0)
			return (env_parse_file(e, fd));
	}
	ft_print_error();
	return (false);
}
