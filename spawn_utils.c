/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:27:20 by fseles            #+#    #+#             */
/*   Updated: 2024/03/15 17:35:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	set_spawn_direction(char c, t_cube *cube)
{
	if (c == 'N')
		cube->spawn_direction = NORTH;
	else if (c == 'E')
		cube->spawn_direction = EAST;
	else if (c == 'S')
		cube->spawn_direction = SOUTH;
	else if (c == 'W')
		cube->spawn_direction = WEST;
}

void	get_spawn_position(t_cube *cube)
{
	char	**map;
	int		i;
	int		j;

	map = cube->map;
	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (is_player(map[i][j]) == 1)
			{
				set_spawn_direction(map[i][j], cube);
				cube->map[i][j] = '0';
				cube->pos_x = i + 0.5;
				cube->pos_y = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}
