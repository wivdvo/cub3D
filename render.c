/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willem <willem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:04 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/14 16:30:14 by willem           ###   ########.fr       */
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
	cube->img.img = mlx_new_image(cube->mlx_ptr, WIDTH, HEIGHT);
	cube->img.addr = mlx_get_data_addr(cube->img.img, &cube->img.bits_per_pixel, &cube->img.line_length, &cube->img.endian);
	my_mlx_pixel_put(&cube->img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img,0, 0);
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
	cube->no_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->no_path, &cube->wall_width, &cube->wall_height);
	if (!cube->no_img)
		render_exit(cube);
}

void	init_ea(t_cube *cube)
{
	cube->ea_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->ea_path, &cube->wall_width, &cube->wall_height);
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
	cube->we_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->we_path, &cube->wall_width, &cube->wall_height);
	if (!cube->we_img)
		render_exit(cube);
}

void render(t_cube *cube)
{
	init_mlx(cube);
	init_img(cube);


	// cube->pos_x = 2;
	// cube->pos_y = 3;
	// cube->dir_x = 1;
	// cube->dir_y = 0;
	// cube->plane_x = 0;
	// cube->plane_y = 0.66;
	
	spawn_player(cube);

	//mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->no_img, 0, 0);
	raycaster(cube);
	//mlx_key_hook(cube->win_ptr, handle_input, cube);

	mlx_hook(cube->win_ptr, 17, 0L, render_exit, cube);

	mlx_hook(cube->win_ptr, 2, (1L<<0), &key_press, cube);
    mlx_hook(cube->win_ptr, 3, (1L<<1), &key_release, cube);


	mlx_loop_hook(cube->mlx_ptr, &game_loop, cube);
	mlx_loop(cube->mlx_ptr);
}


int	key_press(int keysym, t_cube *cube)
{
	// puts("key pressed");
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
}

int	key_release(int keysym, t_cube *cube)
{
	//puts("key released");
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

int	game_loop(t_cube *cube)
{
	if (cube->w_pressed)
	{
		if (cube->map[(int)(cube->pos_x + cube->dir_x * (1.1))][(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)][(int)(cube->pos_y + cube->dir_y * (1.1))] != '1')
			cube->pos_y += cube->dir_y * MS;
		raycaster(cube);
	}
	if (cube->d_pressed)
	{

		//rotate to right 90 degree
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-1.5708) - cube->dir_y * sin(-1.5708);
		cube->dir_y = old_dir_x * sin(-1.5708) + cube->dir_y * cos(-1.5708);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-1.5708) - cube->plane_y * sin(-1.5708);
		cube->plane_y = old_plane_x * sin(-1.5708) + cube->plane_y * cos(-1.5708);

		//move like with w
		if (cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)][(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)][(int)(cube->pos_y + cube->dir_y * 1.1)] != '1')
			cube->pos_y += cube->dir_y * MS;

		//rotate to left 90 degree
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(1.5708) - cube->dir_y * sin(1.5708);
		cube->dir_y = old_dir_x * sin(1.5708) + cube->dir_y * cos(1.5708);

		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(1.5708) - cube->plane_y * sin(1.5708);
		cube->plane_y = old_plane_x * sin(1.5708) + cube->plane_y * cos(1.5708);
		raycaster(cube);
	}
	if (cube->s_pressed)
	{
		if (cube->map[(int)(cube->pos_x - cube->dir_x * 1.1)][(int)(cube->pos_y)] != '1')
			cube->pos_x -= cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)][(int)(cube->pos_y - cube->dir_y * 1.1)] != '1')
			cube->pos_y -= cube->dir_y * MS;
		raycaster(cube);
	}
	if (cube->a_pressed)
	{
		//rotate to left 90 degree
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(1.5708) - cube->dir_y * sin(1.5708);
		cube->dir_y = old_dir_x * sin(1.5708) + cube->dir_y * cos(1.5708);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(1.5708) - cube->plane_y * sin(1.5708);
		cube->plane_y = old_plane_x * sin(1.5708) + cube->plane_y * cos(1.5708);

				//move like with w

		if (cube->map[(int)(cube->pos_x + cube->dir_x * 1.1)][(int)(cube->pos_y)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_x)][(int)(cube->pos_y + cube->dir_y * 1.1)] != '1')
			cube->pos_y += cube->dir_y * MS;
		//rotate to right 90 degree
		old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-1.5708) - cube->dir_y * sin(-1.5708);
		cube->dir_y = old_dir_x * sin(-1.5708) + cube->dir_y * cos(-1.5708);

		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-1.5708) - cube->plane_y * sin(-1.5708);
		cube->plane_y = old_plane_x * sin(-1.5708) + cube->plane_y * cos(-1.5708);

		raycaster(cube);
	}

	if (cube->right_pressed)
	{
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-RS) - cube->dir_y * sin(-RS);
		cube->dir_y = old_dir_x * sin(-RS) + cube->dir_y * cos(-RS);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-RS) - cube->plane_y * sin(-RS);
		cube->plane_y = old_plane_x * sin(-RS) + cube->plane_y * cos(-RS);
		raycaster(cube);
	}
	if (cube->left_pressed)
	{
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(RS) - cube->dir_y * sin(RS);
		cube->dir_y = old_dir_x * sin(RS) + cube->dir_y * cos(RS);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(RS) - cube->plane_y * sin(RS);
		cube->plane_y = old_plane_x * sin(RS) + cube->plane_y * cos(RS);
		raycaster(cube);
	}
}



void raycaster(t_cube *cube)
{
	int x;

	x = 0;

	paint_ceiling_floor(cube);
	// printf("pos x:%f, pos y:%f\n", cube->pos_x, cube->pos_y);
	// printf("dir x:%f, dir y:%f\n", cube->dir_x, cube->dir_y);


	//very high number ;; meant to be infity ;; if it would be division through 0 do infinity instead
	cube->big_nb = 1e30;


	while (x < WIDTH)
	{
		//calculate ray position and direction
		cube->camera_x = 2 * x / (double)WIDTH - 1; //x - coordinate in camera space
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



		//calculate step and initial sideDist
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
				cube->side = 0;
			}
			else
			{
				cube->dis_to_side_y += cube->delta_y;
				cube->map_y += cube->step_y;
				cube->side = 1;
			}
			//check for collison
			if (cube->map[cube->map_x][cube->map_y] == '1')
				cube->hit = 1;
		}
			
		//claculate distance
		if (cube->side == 0)
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
			//puts("start < 0");
			cube->draw_start = 0;
		}
		cube->draw_end = cube->line_height / 2 + (double)HEIGHT / 2;
		if (cube->draw_end >= HEIGHT)
		{
			//puts("end < 0");
			cube->draw_end = HEIGHT - 1;
		}
		
		int bits_per_pixel, size_line, endian;
		char *img_data = mlx_get_data_addr(cube->no_img, &bits_per_pixel, &size_line, &endian);

		// Calculate the height of the texture
		int texture_height = size_line / (bits_per_pixel / 8);

		// Calculate the step and the initial position on the texture
		double step = 1.0 * texture_height / cube->line_height;
		double texture_pos = (cube->draw_start - HEIGHT / 2 + cube->line_height / 2) * step;

		for (int y = cube->draw_start; y < cube->draw_end; y++)
		{
			// Get the y coordinate on the texture
			int texture_y = (int)texture_pos & (texture_height - 1);
			texture_pos += step;

			// Get the color of the pixel from the texture
			int color = *(int*)(img_data + texture_y * size_line);

			// Draw the pixel
			my_mlx_pixel_put(&cube->img, x, y, color);
		}
		// void *slicica;
		// int img_width;
		// int img_height;

		// slicica = mlx_xpm_file_to_image(cube->mlx_ptr, "wall.xpm", &img_width, &img_height);
		//drawing pixels 	
		// for (int y = cube->draw_start; y < cube->draw_end; y++)
		// {
		// 	//mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, x, y, 0xFF0000);
		// 	my_mlx_pixel_put(&cube->img, x, y, 0x00B67352);
		// }


		// for (int y = 50; y <= 200; y++)
		// {
		// 	mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, x, y, 0xFF0000);
		// }
		
		x++;
	}
	// void *slicica;
	// int img_width;
	// int img_height;
	// slicica = mlx_xpm_file_to_image(cube->mlx_ptr, "wall.xpm", &img_width, &img_height);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img,0, 0);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->no_img,0, 0);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->ea_img,100, 0);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->we_img, 200, 0);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->so_img, 300, 0);

}