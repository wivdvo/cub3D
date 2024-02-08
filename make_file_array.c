/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_file_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:02:30 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/08 15:00:55 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	make_array(t_cube *cube, char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd < 0)
		return (put_error("open failed"), -1);
	if (read_file_array(cube, fd) == -1)
		return (put_error("reading map failed"), -1);
	return (0);
}

int	realloc_file_array(t_cube *cube, char *line, int y)
{
	char **temp;
	int	i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (y + 3));
	if (!temp)
	{
		free(line);
		pars_exit(cube, "malloc failed");
	}
	while (cube->file && cube->file[i])
	{
		temp[i] = cube->file[i];
		i++;
	}
	temp[i] = line;
	temp[++i] = 0;
	if (cube->file)
		free(cube->file);
	cube->file = temp;
	return (0);
}

int	read_file_array(t_cube *cube, int fd)
{
	int	y;
	char *line;

	y = 0;
	cube->file = (char **)malloc(sizeof(char *) * 2);
	if (!cube->file)
		pars_exit(cube, "malloc failed");
	cube->file[0] = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (realloc_file_array(cube, line, y) == -1)
			return (-1);
		y++;
	}
	print_file_array(cube);
	return (0);
}