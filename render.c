/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:04 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/23 13:43:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	init_mlx(t_cube *cube)
{
	cube->mlx_ptr = mlx_init();
	if (!cube->mlx_ptr)
		pars_exit(cube, "mlx init failed");
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIDTH, HEIGHT, "*****");
	if (!cube->win_ptr)
	{
		mlx_destroy_display(cube->mlx_ptr);
		free(cube->mlx_ptr);
		pars_exit(cube, "mlx new window failed");
	}
	cube->img.img = mlx_new_image(cube->mlx_ptr, WIDTH, HEIGHT);
	if (!cube->img.img)
		render_exit(cube);
	cube->img.addr = mlx_get_data_addr(cube->img.img, &cube->img.bits_per_pixel,
			&cube->img.line_length, &cube->img.endian);
	if (!cube->img.img)
		render_exit(cube);
	my_mlx_pixel_put(&cube->img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img, 0, 0);
}

void render(t_cube *cube)
{
	init_mlx(cube);
	init_img(cube);
	spawn_player(cube);
	raycaster(cube);
	mlx_hook(cube->win_ptr, 17, 0L, render_exit, cube);
	mlx_hook(cube->win_ptr, 2, (1L << 0), &key_press, cube);
	mlx_hook(cube->win_ptr, 3, (1L << 1), &key_release, cube);
	mlx_loop_hook(cube->mlx_ptr, &game_loop, cube);
	mlx_loop(cube->mlx_ptr);
}

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
		cube->draw_end = HEIGHT - 1;
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

void	calc_tex_height_step_tex_pos_and_draw(t_cube *cube, int x)
{
	int		texture_height;
	double	texture_pos;
	int		y;
	int		texture_y;
	int		color;

	texture_height = cube->size_line / (cube->bits_per_pixel / 8);
	cube->step = 1.0 * texture_height / cube->lh;
	texture_pos = (cube->draw_start - HEIGHT / 2 + cube->lh / 2) * cube->step;
	y = cube->draw_start;
	while (y < cube->draw_end)
	{
		texture_y = (int)texture_pos % texture_height;
		texture_pos += cube->step;
		color = *(int*)(cube->img_data + texture_y * cube->size_line + cube->tex_x * (cube->bits_per_pixel / 8));
		my_mlx_pixel_put(&cube->img, x, y, color);
		y++;
	}
}

void raycaster(t_cube *cube)
{
	int	x;

	x = 0;
	paint_ceiling_floor(cube);
	cube->big_nb = 1e30;
	while (x < WIDTH)
	{
		calc_ray_pos_dir(cube, x);
		round_pos_to_int(cube);
		clac_ray_delta(cube);
		calc_step_and_side_dist(cube);
		check_gridlines_collision(cube);
		calc_distance_hit_and_height(cube);
		calc_top_and_bottom(cube);
		load_imgs(cube);
		calc_pos_of_hit_and_wall_x(cube);
		calc_tex_height_step_tex_pos_and_draw(cube, x);
		x++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img, 0, 0);
}
