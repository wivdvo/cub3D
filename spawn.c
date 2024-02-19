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

static void east(t_cube *cube)
{
	cube->dir_x = 1;
	cube->dir_y = 0;
	cube->plane_x = 0;
	cube->plane_y = 0.66;
}

static void west(t_cube *cube)
{
	cube->dir_x = -1;
	cube->dir_y = 0;
	cube->plane_x = 0;
	cube->plane_y = -0.66;
}
static void south(t_cube *cube)
{
	cube->dir_x = 0;
	cube->dir_y = 1;
	cube->plane_x = -0.66;
	cube->plane_y = 0;
}

static void north(t_cube *cube)
{
	cube->dir_x = 0;
	cube->dir_y = -1;
	cube->plane_x = 0.66;
	cube->plane_y = 0;
}

void spawn_player(t_cube *cube, int spawn_direction)
{
	//get_spawn position
	cube->pos_x = 2;
	cube->pos_y = 3;
	
	if(spawn_direction == NORTH)
		north(cube);
	else if(spawn_direction == EAST)
		east(cube);
	else if(spawn_direction == SOUTH)
		south(cube);
	else if(spawn_direction == WEST)
		west(cube);
}