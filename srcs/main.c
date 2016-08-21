/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/19 01:43:56 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int			main(int ac, char **av)
{
	char	*line;
	char	**p;
	pid_t	pid;

	srand(time(0));
	if (ac != 1)
		return (ft_engine(ac, av));
	line = 0;
	signal(SIGCHLD, SIG_IGN);
	while ((line = readline("\033[36mRaytracer\033[0m> ")) != 0)
	{
		if (ft_strlen(line) != ft_strlen_func(line, &ft_isspace))
			add_history(line);
		p = ft_strsplit_func(line, &ft_isspace);
		if (ft_strequ(*p, "load"))
		{
			if ((pid = fork()) == 0)
				ft_engine(ft_tablen(p), p);
			sleep(1);
		}
		ft_strdel(&line);
		ft_tabdel(&p);
	}
	return (0);
}
