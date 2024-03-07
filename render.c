/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:04 by wvan-der          #+#    #+#             */
/*   Updated: 2024/03/07 12:38:37 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	render_msg(char *str, t_cube *cube)
{
	put_error(str);
	render_exit(cube);
}

void	init_mlx(t_cube *cube)
{
	cube->mlx_ptr = mlx_init();
	if (!cube->mlx_ptr)
		pars_exit(cube, "mlx init failed");
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIDTH, HEIGHT,
			"Koraljka   POV");
	if (!cube->win_ptr)
	{
		mlx_destroy_display(cube->mlx_ptr);
		free(cube->mlx_ptr);
		pars_exit(cube, "mlx new window failed");
	}
	cube->img.img = mlx_new_image(cube->mlx_ptr, WIDTH, HEIGHT);
	if (!cube->img.img)
		render_msg("mlx failed", cube);
	cube->img.addr = mlx_get_data_addr(cube->img.img, &cube->img.bits_per_pixel,
			&cube->img.line_length, &cube->img.endian);
	if (!cube->img.img)
		render_msg("mlx failed", cube);
	my_mlx_pixel_put(&cube->img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img, 0, 0);
}

void	render(t_cube *cube)
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
		color = *(int *)(cube->img_data + texture_y * cube->size_line
				+ cube->tex_x * (cube->bits_per_pixel / 8));
		my_mlx_pixel_put(&cube->img, x, y, color);
		y++;
	}
}

void	raycaster(t_cube *cube)
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
