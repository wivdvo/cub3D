/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willem <willem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:04 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/13 18:02:36 by willem           ###   ########.fr       */
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
		pars_exit(cube, "mlx new window failed");
}

void	init_img(t_cube *cube)
{
	init_no(cube);
}

void	init_no(t_cube *cube)
{
	cube->no_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->so_path, &cube->wall_width, &cube->wall_height);
	if (!cube->no_img)
		render_exit(cube);
}

void	init_ea(t_cube *cube)
{
	cube->ea_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->so_path, &cube->wall_width, &cube->wall_height);
	if (!cube->ea_img)
		render_exit(cube);
}

void	init_so(t_cube *cube)
{
	cube->so_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->so_path, &cube->wall_width, &cube->wall_height);
	if (!cube->so_img)
		render_exit(cube);
}

void	init_we(t_cube *cube)
{
	cube->we_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->so_path, &cube->wall_width, &cube->wall_height);
	if (!cube->we_img)
		render_exit(cube);
}

void render(t_cube *cube)
{
	init_mlx(cube);
	// init_img(cube);


	cube->pos_x = 5;
	cube->pos_y = 5;
	cube->dir_x = 1;
	cube->dir_y = 0;
	cube->plane_x = 0;
	cube->plane_y = 0.66;


	//mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->no_img, 0, 0);
	raycaster(cube);
	mlx_key_hook(cube->win_ptr, handle_input, cube);
	mlx_hook(cube->win_ptr, 17, 0L, render_exit, cube);
	mlx_loop(cube->mlx_ptr);
}

int	handle_input(int keysym, t_cube *cube)
{
	if (keysym == XK_Escape)
	{
		render_exit(cube);
	}

	if (keysym == XK_Right)
	{
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-RS) - cube->dir_y * sin(-RS);
		cube->dir_y = old_dir_x * sin(-RS) + cube->dir_y * cos(-RS);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-RS) - cube->plane_y * sin(-RS);
		cube->plane_y = old_plane_x * sin(-RS) + cube->plane_y * cos(-RS);
	}
	if (keysym == XK_Left)
	{
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(RS) - cube->dir_y * sin(RS);
		cube->dir_y = old_dir_x * sin(RS) + cube->dir_y * cos(RS);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(RS) - cube->plane_y * sin(RS);
		cube->plane_y = old_plane_x * sin(RS) + cube->plane_y * cos(RS);
	}
	

	

	if (keysym == XK_w)
	{
		if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x + cube->dir_x * MS)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_y + cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
			cube->pos_y += cube->dir_y * MS;
	}
	if (keysym == XK_a)
	{
		if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x - cube->dir_x * MS)] != '1')
			cube->pos_x -= cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_y - cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
			cube->pos_y -= cube->dir_y * MS;
	}


	// if (keysym == XK_d)
	// {
	// 	if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x + cube->dir_x * MS)] != '1')
	// 		cube->pos_x += cube->dir_x * MS;
	// 	if (cube->map[(int)(cube->pos_y + cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
	// 		cube->pos_y += cube->dir_y * MS;
	// }
	// if (keysym == XK_a)
	// {
	// 	if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x - cube->dir_x * MS)] != '1')
	// 		cube->pos_x -= cube->dir_x * MS;
	// 	if (cube->map[(int)(cube->pos_y - cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
	// 		cube->pos_y -= cube->dir_y * MS;
	// }

	raycaster(cube);
}

void raycaster(t_cube *cube)
{
	int x;

	x = 0;


	printf("pos x:%f, pos y:%f\n", cube->pos_x, cube->pos_y);


	//very high number ;; meant to be infity ;; if it would be division through 0 do infinity instead
	cube->big_nb = 1e30;


	while (x < WIDTH)
	{
		//ray pos and dir
		cube->camera_x = 2 * x / (double)WIDTH - 1;
		cube->ray_dir_x = cube->dir_x + cube->plane_x * cube->camera_x;
		cube->ray_dir_y = cube->dir_y + cube->plane_y * cube->camera_x; 



		//round pos to int to know in which box you are
		cube->map_x = (int)cube->pos_x;
		cube->map_y = (int)cube->pos_y;

		//len of ray form one side to next
		if (cube->ray_dir_x == 0)
			cube->delta_x = cube->big_nb;
		else
			cube->delta_x = fabs(1 / cube->ray_dir_x);

		if (cube->ray_dir_y == 0)
			cube->delta_y = cube->big_nb;
		else
			cube->delta_y = fabs(1 / cube->ray_dir_y);



		//idk man
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

		cube->hit = 0;
		//do DDD (check every grid line for collision)
		while (cube->hit == 0)
		{
			//go to next grid line
			if (cube->dis_to_side_x < cube->dis_to_side_y)
			{
				cube->dis_to_side_x += cube->delta_x;
				cube->map_x +=	cube->step_x;
				cube->side = 1;
			}
			else
			{
				cube->dis_to_side_y += cube->delta_y;
				cube->map_y += cube->step_y;
				cube->side = 2;
			}
			//check for collison
			if (cube->map[cube->map_y][cube->map_x] == '1')
				cube->hit = 1;
		}
			
		//claculate distance
		if (cube->side == 1)
			cube->wall_dist = (cube->dis_to_side_x - cube->delta_x);
		else
			cube->wall_dist = (cube->dis_to_side_y - cube->delta_y);


		//claculate height
		//printf("wall dist%f\n", cube->wall_dist);
		cube->line_height = (int)((double)HEIGHT / cube->wall_dist);
		//printf("line len%d\n", cube->line_height);

		//calc top and bottom pos
		cube->draw_start = -cube->line_height / 2 + (double)HEIGHT / 2;
		if (cube->draw_start < 0)
		{
			puts("start < 0");
			cube->draw_start = 0;
		}
		cube->draw_end = cube->line_height / 2 + (double)HEIGHT / 2;
		if (cube->draw_end < 0)
		{
			puts("end < 0");
			cube->draw_end = 0;
		}
		
			
		for (int y = cube->draw_start; y <= cube->draw_end; y++)
		{
			mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, x, y, 0xFF0000);
		}

		// for (int y = 50; y <= 200; y++)
		// {
		// 	mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, x, y, 0xFF0000);
		// }
		
		x++;
	}
}