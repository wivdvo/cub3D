/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_file_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:02:30 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/06 15:50:41 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	make_array(t_pars *pars, char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd < 0)
		return (put_error("open failed"), -1);
	if (read_file_array(pars, fd) == -1)
		return (put_error("reading map failed"), -1);
	return (0);
}

int	realloc_file_array(t_pars *pars, char *line, int y)
{
	char **temp;
	int	i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (y + 3));
	if (!temp)
		return (-1);
	while (pars->file && pars->file[i])
	{
		temp[i] = pars->file[i];
		i++;
	}
	temp[i] = line;
	temp[++i] = 0;
	if (pars->file)
		free(pars->file);
	pars->file = temp;
	return (0);
}

int	read_file_array(t_pars *pars, int fd)
{
	int	y;
	char *line;

	y = 0;
	pars->file = (char **)malloc(sizeof(char *) * 2);
	if (!pars->file)
		return (-1);
	pars->file[0] = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (realloc_file_array(pars, line, y) == -1)
			return (-1);
		y++;
	}
	print_file_array(pars);
	return (0);
}