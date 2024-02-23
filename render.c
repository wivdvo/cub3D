/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:04 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/23 13:05:06 by wvan-der         ###   ########.fr       */
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

void	init_img(t_cube *cube)
{
	init_no(cube);
	init_ea(cube);
	init_so(cube);
	init_we(cube);
}

void	init_no(t_cube *cube)
{
	cube->no_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->no_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->no_img)
		render_exit(cube);
}

void	init_ea(t_cube *cube)
{
	cube->ea_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->ea_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->ea_img)
		render_exit(cube);
}

void	init_so(t_cube *cube)
{
	cube->so_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->so_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->so_img)
		render_exit(cube);
}

void	init_we(t_cube *cube)
{
	cube->we_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->we_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->we_img)
		render_exit(cube);
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

int	key_press(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
		cube->w_pressed = 1;
	else if (keysym == XK_s)
		cube->s_pressed = 1;
	else if (keysym == XK_a)
		cube->a_pressed = 1;
	else if (keysym == XK_d)
		cube->d_pressed = 1;
	else if (keysym == XK_Left)
		cube->left_pressed = 1;
	else if (keysym == XK_Right)
		cube->right_pressed = 1;
	else if (keysym == XK_Escape)
		cube->esc_pressed = 1;
}

int	key_release(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
		cube->w_pressed = 0;
	else if (keysym == XK_s)
		cube->s_pressed = 0;
	else if (keysym == XK_a)
		cube->a_pressed = 0;
	else if (keysym == XK_d)
		cube->d_pressed = 0;
	else if (keysym == XK_Left)
		cube->left_pressed = 0;
	else if (keysym == XK_Right)
		cube->right_pressed = 0;
}

void	check_w_pressed(t_cube *cube)
{
	if (cube->w_pressed)
	{
		if (cube->map[(int)(cube->pos_x + cube->dir_x * (1.1))]
				[(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y + cube->dir_y * (1.1))] != '1')
			cube->pos_y += cube->dir_y * MS;
		raycaster(cube);
	}
}

void	check_d_pressed(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cube->d_pressed)
	{
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-1.5708) - cube->dir_y * sin(-1.5708);
		cube->dir_y = old_dir_x * sin(-1.5708) + cube->dir_y * cos(-1.5708);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-1.5708) - cube->plane_y * sin(-1.5708);
		cube->plane_y = old_plane_x * sin(-1.5708) + cube->plane_y * cos(-1.5708);
		if (cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)][(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)][(int)(cube->pos_y + cube->dir_y * 1.1)] != '1')
			cube->pos_y += cube->dir_y * MS;
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(1.5708) - cube->dir_y * sin(1.5708);
		cube->dir_y = old_dir_x * sin(1.5708) + cube->dir_y * cos(1.5708);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(1.5708) - cube->plane_y * sin(1.5708);
		cube->plane_y = old_plane_x * sin(1.5708) + cube->plane_y * cos(1.5708);
		raycaster(cube);
	}
}
void	check_s_pressed(t_cube *cube)
{
	if (cube->s_pressed)
	{
		if (cube->map[(int)(cube->pos_x - cube->dir_x * 1.1)]
				[(int)(cube->pos_y)] != '1')
			cube->pos_x -= cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y - cube->dir_y * 1.1)] != '1')
			cube->pos_y -= cube->dir_y * MS;
		raycaster(cube);
	}
}

void	check_a_pressed(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cube->a_pressed)
	{
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(N) - cube->dir_y * sin(N);
		cube->dir_y = old_dir_x * sin(N) + cube->dir_y * cos(N);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(N) - cube->plane_y * sin(N);
		cube->plane_y = old_plane_x * sin(N) + cube->plane_y * cos(N);
		if (cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)]
				[(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y + cube->dir_y * 1.1)] != '1')
			cube->pos_y += cube->dir_y * MS;
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-N) - cube->dir_y * sin(-N);
		cube->dir_y = old_dir_x * sin(-N) + cube->dir_y * cos(-N);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-N) - cube->plane_y * sin(-N);
		cube->plane_y = old_plane_x * sin(-N) + cube->plane_y * cos(-N);
		raycaster(cube);
	}
}

void	check_right_pressed(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cube->right_pressed)
	{
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-RS) - cube->dir_y * sin(-RS);
		cube->dir_y = old_dir_x * sin(-RS) + cube->dir_y * cos(-RS);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-RS) - cube->plane_y * sin(-RS);
		cube->plane_y = old_plane_x * sin(-RS) + cube->plane_y * cos(-RS);
		raycaster(cube);
	}
}

void	check_left_pressed(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cube->left_pressed)
	{
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(RS) - cube->dir_y * sin(RS);
		cube->dir_y = old_dir_x * sin(RS) + cube->dir_y * cos(RS);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(RS) - cube->plane_y * sin(RS);
		cube->plane_y = old_plane_x * sin(RS) + cube->plane_y * cos(RS);
		raycaster(cube);
	}
}

int	game_loop(t_cube *cube)
{
	if (cube->esc_pressed)
		render_exit(cube);
	check_w_pressed(cube);
	check_d_pressed(cube);
	check_s_pressed(cube);
	check_a_pressed(cube);
	check_right_pressed(cube);
	check_left_pressed(cube);
}

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
