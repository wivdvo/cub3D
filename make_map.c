/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:26:05 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/08 18:44:36 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	make_map(t_cube *cube)
{
	make_map_array(cube);
}

int	make_map_array(t_cube *cube)
{
	find_map_end(cube);
	check_that_nothing_after_end(cube);
	copy_map(cube);
	check_invalid_char(cube);
	//check_that_encased(cube);
}

void	check_invalid_char(t_cube *cube)
{
	int	x;
	int	y;
	int	flag;

	y = 0;
	flag = 0;
	while (cube->map[y])
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (cube->map[y][x] != '1' && cube->map[y][x] != '0'
					&& cube->map[y][x] != 'N' && cube->map[y][x] != 'E'
					&& cube->map[y][x] != 'S' && cube->map[y][x] != 'W'
					&& cube->map[y][x] != '\n' && cube->map[y][x] != ' ')
			{
				pars_exit(cube, "invalid char in map");
			}
			if (cube->map[y][x] == 'N' || cube->map[y][x] == 'E'
					|| cube->map[y][x] == 'S' || cube->map[y][x] == 'W')
			{
				if (flag == 0)
					flag = 1;
				else
					pars_exit(cube, "multible player");
			}
			x++;
		}
		y++;
	}
}

void	check_that_nothing_after_end(t_cube *cube)
{
	int	i;
	int	j;

	i = cube->map_end + 1;
	while (cube->file[i])
	{
		j = 0;
		while (cube->file[i][j] && (cube->file[i][j] == ' '
			|| cube->file[i][j] == '\n'))
			j++;
		if (cube->file[i][j] != 0)
			pars_exit(cube, "there is something after map");
		i++;
	}
}

int	find_map_end(t_cube *cube)
{
	int	i;
	int	j;

	i = cube->map_begin;
	while (cube->file[i])
	{
		j = 0;
		while (cube->file[i][j] && cube->file[i][j] == ' ')
			j++;
		if (cube->file[i][j] != '1' && cube->file[i][j] != '0'
				&& cube->file[i][j] != 'N' && cube->file[i][j] != 'E'
				&& cube->file[i][j] != 'S' && cube->file[i][j] != 'W')
			break ;
		i++;
	}
	cube->map_end = --i;
}

void	print_map(t_cube *cube)
{
	int	i;

	i = 0;
	printf("----------------\n");
	while (cube->map && cube->map[i])
	{
		printf("%s", cube->map[i]);
		i++;
	}
	printf("----------------\n");
}

int	copy_map(t_cube *cube)
{
	int	i;
	int	j;

	j = 0;
	i = cube->map_begin;
	cube->map = (char **)malloc(sizeof(char *)
			* (cube->map_end - cube->map_begin + 2));
	if (!cube->map)
		pars_exit(cube, "malloc failed");
	while (cube->file[i] && i <= cube->map_end)
	{
		cube->map[j] = ft_substr(cube->file[i], 0, ft_strlen1(cube->file[i]));
		if (!cube->map[j])
			pars_exit(cube, "malloc failed");
		cube->map[j + 1] = 0;
		j++;
		i++;
	}
	print_map(cube);
}
