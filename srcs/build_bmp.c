/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/24 16:34:59 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <fcntl.h>
#include <errno.h>

static uint8_t	g_header_file[14] =
{
	'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 40 + 14, 0, 0, 0
};

static uint8_t	g_header_info[40] =
{
	40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0x13, 0x0B, 0, 0, 0x13, 0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static uint8_t	g_pad[3] =
{
	0, 0, 0
};

int			ft_generate_new_name(char const *file)
{
	static char	name[0x10];
	size_t		i;
	int			fd;

	i = 0;
	ft_bzero((void *)name, 0x10);
	while (i != 10)
		name[i++] = '0' + rand() % 10;
	ft_sprintf(name + 10, file);
	if ((fd = open(name, O_WRONLY | O_CREAT, 0777)) <= 0)
		ft_fprintf(2, "Error while generating new name: %s\n", name);
	else
		ft_fprintf(1, "Generating %s... ", name);
	return (fd);
}

static void	ft_print_header(t_env *e, int fd)
{
	int pad_size;
	int data_size;
	int all_size;

	pad_size = (4 - (e->width * 3) % 4) % 4;
	data_size = e->width * e->height * 3 | e->height * pad_size;
	all_size = data_size + sizeof(g_header_info) + sizeof(g_header_file);
	g_header_file[2] = (uint8_t)(all_size);
	g_header_file[3] = (uint8_t)(all_size >> 8);
	g_header_file[4] = (uint8_t)(all_size >> 16);
	g_header_file[5] = (uint8_t)(all_size >> 24);
	g_header_info[4] = (uint8_t)(e->width);
	g_header_info[5] = (uint8_t)(e->width >> 8);
	g_header_info[6] = (uint8_t)(e->width >> 16);
	g_header_info[7] = (uint8_t)(e->width >> 24);
	g_header_info[8] = (uint8_t)(e->height);
	g_header_info[9] = (uint8_t)(e->height >> 8);
	g_header_info[10] = (uint8_t)(e->height >> 16);
	g_header_info[11] = (uint8_t)(e->height >> 24);
	g_header_info[20] = (uint8_t)(data_size);
	g_header_info[21] = (uint8_t)(data_size >> 8);
	g_header_info[22] = (uint8_t)(data_size >> 16);
	g_header_info[23] = (uint8_t)(data_size >> 24);
	write(fd, &g_header_file, sizeof(g_header_file));
	write(fd, &g_header_info, sizeof(g_header_info));
}

void		ft_build_bmp(t_env *e)
{
	int offset;
	int pad;
	int fd;
	int x;
	int y;

	if ((fd = ft_generate_new_name(".bmp")) <= 0)
		return ;
	ft_print_header(e, fd);
	y = e->screen->height - 1;
	pad = (4 - (e->width * 3) % 4) % 4;
	while (y >= 0)
	{
		x = 0;
		while (x < e->screen->width)
		{
			offset = (y * e->screen->width + x++) * e->screen->bypp;
			write(fd, e->screen->data + offset, 3);
		}
		write(fd, &g_pad, pad);
		--y;
	}
	close(fd);
	ft_printf("done.\n");
}
