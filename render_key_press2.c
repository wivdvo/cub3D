/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_key_press2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:04:06 by fseles            #+#    #+#             */
/*   Updated: 2024/03/12 15:25:52 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	a_utils(t_cube *cube, double old_dir_x, double old_plane_x)
{
	old_dir_x = cube->dir_x;
	cube->dir_x = cube->dir_x * cos(-N) - cube->dir_y * sin(-N);
	cube->dir_y = old_dir_x * sin(-N) + cube->dir_y * cos(-N);
	old_plane_x = cube->plane_x;
	cube->plane_x = cube->plane_x * cos(-N) - cube->plane_y * sin(-N);
	cube->plane_y = old_plane_x * sin(-N) + cube->plane_y * cos(-N);
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
			&& cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)]
			[(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)] && cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y + cube->dir_y * 1.1)] != '1')
			cube->pos_y += cube->dir_y * MS;
		a_utils(cube, old_dir_x, old_plane_x);
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
	return (0);
}
