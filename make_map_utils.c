/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:59:46 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 12:59:52 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	make_map(t_cube *cube)
{
	make_map_array(cube);
	return (0);
}

int	make_map_array(t_cube *cube)
{
	find_map_end(cube);
	check_that_nothing_after_end(cube);
	copy_map(cube);
	check_invalid_char(cube);
	return (0);
}

static int	is_valid_char2(char c)
{
	if (c != '1' && c != '0'
		&& c != 'N' && c != 'E'
		&& c != 'S' && c != 'W'
		&& c != '\n' && c != ' ')
	{
		return (1);
	}
	return (0);
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
			if (is_valid_char2(cube->map[y][x]))
				pars_exit(cube, "invalid char in map");
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
