/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:54 by fseles            #+#    #+#             */
/*   Updated: 2024/03/12 15:25:48 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

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
	return (0);
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
	return (0);
}

void	check_w_pressed(t_cube *cube)
{
	if (cube->w_pressed)
	{
		if (cube->map[(int)(cube->pos_x + cube->dir_x * (1.1))] && cube->map[(int)(cube->pos_x + cube->dir_x * (1.1))]
				[(int)(cube->pos_y)] == '0')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)] && cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y + cube->dir_y * (1.1))] == '0')
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
		cube->dir_x = cube->dir_x * cos(-N) - cube->dir_y * sin(-N);
		cube->dir_y = old_dir_x * sin(-N) + cube->dir_y * cos(-N);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-N) - cube->plane_y * sin(-N);
		cube->plane_y = old_plane_x * sin(-N) + cube->plane_y * cos(-N);
		if (cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)] && cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)]
				[(int)(cube->pos_y)] == '0')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)] && cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y + cube->dir_y * 1.1)] == '0')
			cube->pos_y += cube->dir_y * MS;
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(N) - cube->dir_y * sin(N);
		cube->dir_y = old_dir_x * sin(N) + cube->dir_y * cos(N);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(N) - cube->plane_y * sin(N);
		cube->plane_y = old_plane_x * sin(N) + cube->plane_y * cos(N);
		raycaster(cube);
	}
}

void	check_s_pressed(t_cube *cube)
{
	if (cube->s_pressed)
	{
		if (cube->map[(int)(cube->pos_x - cube->dir_x * 1.1)] && cube->map[(int)(cube->pos_x - cube->dir_x * 1.1)]
				[(int)(cube->pos_y)] == '0')
			cube->pos_x -= cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)] && cube->map[(int)(cube->pos_x)]
				[(int)(cube->pos_y - cube->dir_y * 1.1)] == '0')
			cube->pos_y -= cube->dir_y * MS;
		raycaster(cube);
	}
}
