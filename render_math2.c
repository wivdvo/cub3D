/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:15:21 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 15:02:56 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	calc_distance_hit_and_height(t_cube *cube)
{
	if (cube->side == 0)
		cube->wall_dist = (cube->dis_to_side_x - cube->delta_x);
	else
		cube->wall_dist = (cube->dis_to_side_y - cube->delta_y);
	cube->lh = (int)((double)HEIGHT / cube->wall_dist);
}

void	calc_top_and_bottom(t_cube *cube)
{
	cube->draw_start = -cube->lh / 2 + (double)HEIGHT / 2;
	if (cube->draw_start < 0)
	{
		cube->draw_start = 0;
	}
	cube->draw_end = cube->lh / 2 + (double)HEIGHT / 2;
	if (cube->draw_end >= HEIGHT)
	{
		cube->draw_end = HEIGHT;
	}
}

void	load_imgs(t_cube *cube)
{
	if (cube->side == 0)
	{
		if (cube->map_x > cube->pos_x)
			cube->img_data = mlx_get_data_addr(cube->so_img,
					&cube->bits_per_pixel, &cube->size_line, &cube->endian);
		else
			cube->img_data = mlx_get_data_addr(cube->no_img,
					&cube->bits_per_pixel, &cube->size_line, &cube->endian);
	}
	else
	{
		if (cube->map_y > cube->pos_y)
			cube->img_data = mlx_get_data_addr(cube->ea_img,
					&cube->bits_per_pixel, &cube->size_line, &cube->endian);
		else
			cube->img_data = mlx_get_data_addr(cube->we_img,
					&cube->bits_per_pixel, &cube->size_line, &cube->endian);
	}
	if (!cube->img_data)
		render_exit(cube);
}

void	calc_pos_of_hit_and_wall_x(t_cube *cube)
{
	double	wall_x;

	if (cube->side == 0)
		wall_x = cube->pos_y + cube->wall_dist * cube->ray_dir_y;
	else
		wall_x = cube->pos_x + cube->wall_dist * cube->ray_dir_x;
	wall_x -= floor(wall_x);
	cube->tex_x = (int)(wall_x * (double)IMG_SIZE);
	if (cube->side == 0 && cube->ray_dir_x > 0)
		cube->tex_x = IMG_SIZE - cube->tex_x - 1;
	if (cube->side == 1 && cube->ray_dir_y < 0)
		cube->tex_x = IMG_SIZE - cube->tex_x - 1;
}
