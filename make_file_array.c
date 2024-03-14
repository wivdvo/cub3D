/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_file_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:02:30 by wvan-der          #+#    #+#             */
/*   Updated: 2024/03/14 16:09:44 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	make_array(t_cube *cube, char *path)
{
	cube->fd = open(path, O_RDWR);
	if (cube->fd < 0)
		return (pars_exit(cube, "open failed"), -1);
	if (read_file_array(cube, cube->fd) == -1)
		return (pars_exit(cube, "reading map failed"), -1);
	return (0);
}

int	realloc_file_array(t_cube *cube, char **line, int y)
{
	char	**temp;
	int		i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (y + 3));
	if (!temp)
	{
		free(*line);
		pars_exit(cube, "malloc11 failed");
	}
	while (cube->file && cube->file[i])
	{
		temp[i] = cube->file[i];
		i++;
	}
	temp[i] = *line;
	temp[++i] = 0;
	if (cube->file)
		free(cube->file);
	cube->file = temp;
	return (0);
}

void	check_char_count(char *line, t_cube *cube, size_t *char_count)
{
	*char_count += ft_strlen1(line);
	if (*char_count > 100000)
		pars_exit(cube, "file containes more than 100k chars!");
}

int	read_file_array(t_cube *cube, int fd)
{
	char	*line;
	int		ret;
	size_t	char_count;

	line = NULL;
	char_count = 0;
	cube->file = (char **)malloc(sizeof(char *) * 2);
	if (!cube->file)
		pars_exit(cube, "malloc failed");
	cube->file[0] = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 1)
			break ;
		if (ret == -1)
			pars_exit(cube, "gnl failed");
		if (realloc_file_array(cube, &line, cube->file_line_count) == -1)
			return (-1);
		check_char_count(line, cube, &char_count);
		cube->file_line_count++;
	}
	return (free(line), 0);
}
