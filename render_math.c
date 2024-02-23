/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:09:19 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 14:09:22 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	calc_ray_pos_dir(t_cube *cube, int x)
{
	cube->camera_x = 2 * x / (double)WIDTH - 1;
	cube->ray_dir_x = cube->dir_x + cube->plane_x * cube->camera_x;
	cube->ray_dir_y = cube->dir_y + cube->plane_y * cube->camera_x;
}

void	round_pos_to_int(t_cube *cube)
{
	cube->map_x = (int)cube->pos_x;
	cube->map_y = (int)cube->pos_y;
}

void	clac_ray_delta(t_cube *cube)
{
	if (cube->ray_dir_x == 0)
		cube->delta_x = cube->big_nb;
	else
		cube->delta_x = fabs(1 / cube->ray_dir_x);
	if (cube->ray_dir_y == 0)
		cube->delta_y = cube->big_nb;
	else
		cube->delta_y = fabs(1 / cube->ray_dir_y);
}

void	calc_step_and_side_dist(t_cube *cube)
{
	if (cube->ray_dir_x < 0)
	{
		cube->step_x = -1;
		cube->dis_to_side_x = (cube->pos_x - cube->map_x) * cube->delta_x;
	}
	else
	{
		cube->step_x = 1;
		cube->dis_to_side_x = (cube->map_x + 1.0 - cube->pos_x) * cube->delta_x;
	}
	if (cube->ray_dir_y < 0)
	{
		cube->step_y = -1;
		cube->dis_to_side_y = (cube->pos_y - cube->map_y) * cube->delta_y;
	}
	else
	{
		cube->step_y = 1;
		cube->dis_to_side_y = (cube->map_y + 1.0 - cube->pos_y) * cube->delta_y;
	}
}

void	check_gridlines_collision(t_cube *cube)
{
	cube->hit = 0;
	while (cube->hit == 0)
	{
		if (cube->dis_to_side_x < cube->dis_to_side_y)
		{
			cube->dis_to_side_x += cube->delta_x;
			cube->map_x += cube->step_x;
			cube->side = 0;
		}
		else
		{
			cube->dis_to_side_y += cube->delta_y;
			cube->map_y += cube->step_y;
			cube->side = 1;
		}
		if (cube->map[cube->map_x][cube->map_y] == '1')
			cube->hit = 1;
	}
}
