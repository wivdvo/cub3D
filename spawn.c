/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:57:13 by fseles            #+#    #+#             */
/*   Updated: 2024/02/19 12:57:19 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void north(t_cube *cube)
{
	cube->dir_x = -1;
	cube->dir_y = 0;
	cube->plane_x = 0;
	cube->plane_y = 0.66;
}

static void west(t_cube *cube)
{
	cube->dir_x = 0;
	cube->dir_y = -1;
	cube->plane_x = -0.66;
	cube->plane_y = 0;
}
static void south(t_cube *cube)
{
	cube->dir_x = 1;
	cube->dir_y = 0;
	cube->plane_x = 0;
	cube->plane_y = -0.66;
}

static void east(t_cube *cube)
{
	cube->dir_x = 0;
	cube->dir_y = 1;
	cube->plane_x = 0.66;
	cube->plane_y = 0;
}

int is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void set_spawn_direction(char c, t_cube *cube)
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

void get_spawn_position(t_cube *cube)
{
	char **map;
	map = cube->map;
	int i;
	i = 0;
	int j;
	j = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if(is_player(map[i][j]) == 1)
			{
				//printf("Player position is %d and %d", i, j);
				set_spawn_direction(map[i][j], cube);
				cube->pos_x = i;
				cube->pos_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void spawn_player(t_cube *cube)
{
	get_spawn_position(cube);
	//cube->pos_x = 2;
	//cube->pos_y = 3;
	
	if(cube->spawn_direction == NORTH)
		north(cube);
	else if(cube->spawn_direction == EAST)
		east(cube);
	else if(cube->spawn_direction == SOUTH)
		south(cube);
	else if(cube->spawn_direction == WEST)
		west(cube);
}