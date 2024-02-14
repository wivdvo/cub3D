/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willem <willem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:04 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/14 19:30:03 by willem           ###   ########.fr       */
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
	init_img(cube);

	if (!cube->ea_img)
		puts("its not hree");


	cube->pos_x = 2;
	cube->pos_y = 2;
	cube->dir_x = 1;
	cube->dir_y = 0;
	cube->plane_x = 0;
	cube->plane_y = 0.66;


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
	puts("key pressed");
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
	puts("key released");
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
		if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x + cube->dir_x * MS)] != '1')
			cube->pos_x += cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_y + cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
			cube->pos_y += cube->dir_y * MS;
		raycaster(cube);
	}
	// if (cube->a_pressed)
	// {
	// 	cube->pos_x = cube->pos_x + (cube->dir_x - 1) * MS;
	// 	cube->pos_y = cube->pos_y + (cube->dir_y - 1) * MS;
	// }
	if (cube->s_pressed)
	{
		if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x - cube->dir_x * MS)] != '1')
			cube->pos_x -= cube->dir_x * MS;
		if (cube->map[(int)(cube->pos_y - cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
			cube->pos_y -= cube->dir_y * MS;
		raycaster(cube);
	}
	// if (cube->d_pressed)
	// {
	// 	cube->pos_x = cube->pos_x + (cube->dir_x - 1) * MS;
	// 	cube->pos_y = cube->pos_y + (cube->dir_y + 1) * MS;
	// }

	if (cube->left_pressed)
	{
		double old_dir_x = cube->dir_x;
		cube->dir_x = cube->dir_x * cos(-RS) - cube->dir_y * sin(-RS);
		cube->dir_y = old_dir_x * sin(-RS) + cube->dir_y * cos(-RS);

		double old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-RS) - cube->plane_y * sin(-RS);
		cube->plane_y = old_plane_x * sin(-RS) + cube->plane_y * cos(-RS);
		raycaster(cube);
	}
	if (cube->right_pressed)
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




// int	handle_input(int keysym, t_cube *cube)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		render_exit(cube);
// 	}

// 	paint_ceiling_floor(cube);


// 	if (keysym == XK_Left)
// 	{
// 		double old_dir_x = cube->dir_x;
// 		cube->dir_x = cube->dir_x * cos(-RS) - cube->dir_y * sin(-RS);
// 		cube->dir_y = old_dir_x * sin(-RS) + cube->dir_y * cos(-RS);

// 		double old_plane_x = cube->plane_x;
// 		cube->plane_x = cube->plane_x * cos(-RS) - cube->plane_y * sin(-RS);
// 		cube->plane_y = old_plane_x * sin(-RS) + cube->plane_y * cos(-RS);
// 	}
// 	if (keysym == XK_Right)
// 	{
// 		double old_dir_x = cube->dir_x;
// 		cube->dir_x = cube->dir_x * cos(RS) - cube->dir_y * sin(RS);
// 		cube->dir_y = old_dir_x * sin(RS) + cube->dir_y * cos(RS);

// 		double old_plane_x = cube->plane_x;
// 		cube->plane_x = cube->plane_x * cos(RS) - cube->plane_y * sin(RS);
// 		cube->plane_y = old_plane_x * sin(RS) + cube->plane_y * cos(RS);
// 	}
	

	

// 	if (keysym == XK_w)
// 	{
// 		if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x + cube->dir_x * MS)] != '1')
// 			cube->pos_x += cube->dir_x * MS;
// 		if (cube->map[(int)(cube->pos_y + cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
// 			cube->pos_y += cube->dir_y * MS;
// 	}
// 	if (keysym == XK_s)
// 	{
// 		if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x - cube->dir_x * MS)] != '1')
// 			cube->pos_x -= cube->dir_x * MS;
// 		if (cube->map[(int)(cube->pos_y - cube->dir_y * MS)][(int)(cube->pos_x)] != '1')
// 			cube->pos_y -= cube->dir_y * MS;
// 	}


// 	// if (keysym == XK_d)
// 	// {
// 	// 	if (cube->map[(int)(cube->pos_y)][(int)(cube->pos_x + (cube->dir_x - 1) * MS)] != '1')
// 	// 		cube->pos_x = cube->pos_x + (cube->dir_x - 1) * MS;
// 	// 	if (cube->map[(int)(cube->pos_y + (cube->dir_y + 1) * MS)][(int)(cube->pos_x)] != '1')
// 	// 		cube->pos_y = cube->pos_y + (cube->dir_y + 1) * MS;
// 	// }

// 	// if (keysym == XK_a)
// 	// {
// 	// 	cube->pos_x = cube->pos_x + (cube->dir_x - 1) * MS;
// 	// 	cube->pos_y = cube->pos_y + (cube->dir_y - 1) * MS;
// 	// }

// 	raycaster(cube);
// }

void raycaster(t_cube *cube)
{
	int x;

	x = 0;

	paint_ceiling_floor(cube);
	printf("pos x:%f, pos y:%f\n", cube->pos_x, cube->pos_y);
	printf("dir x:%f, dir y:%f\n", cube->dir_x, cube->dir_y);


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
		

		//calculate x coordinate of wall
		if (cube->side == 1)
		{
			cube->wall_x = cube->pos_y + cube->wall_dist * cube->dir_y;
		}
		else
		{
			cube->wall_x = cube->pos_x + cube->wall_dist * cube->dir_x;
		}
		cube->wall_x -= floor((cube->wall_x));

		//calcutle x corrdiante of img
		cube->img_x = (int)(cube->wall_x * (double)IMG_W);
		if (cube->side == 1 && cube->dir_x > 0)
		{
			cube->img_x = IMG_W - cube->img_x - 1;
		}
		if (cube->side == 2 && cube->dir_y < 0)
		{
			cube->img_x = IMG_W - cube->img_x - 1;
		}

		cube->step = 1.0 * IMG_H / IMG_W;

		//getting pixels
		double img_pos;
		int		img_y;
		int			color;

		cube->img.addr = mlx_get_data_addr(cube->no_img, &cube->img.bits_per_pixel, &cube->img.line_length, &cube->img.endian);

		img_pos = (cube->draw_start - HEIGHT / 2 + cube->line_height / 2) * cube->step;
		for (int y = cube->draw_start; y < cube->draw_end; y++)
		{
			img_y = (int)cube->pos_x & (IMG_H - 1);
			img_pos += cube->step;
			

			

			color = *(int*)(cube->img.addr + (img_y * cube->img.line_length + cube->img_x * (cube->img.bits_per_pixel / 8)));

			//printf("color:%x\n", color);

			if(cube->draw_end != 0 && cube->draw_start != 0 )
				my_mlx_pixel_put(&cube->img, x, y, color);
			else
				puts("this problem");
		}



















		// for (int y = cube->draw_start; y <= cube->draw_end; y++)
		// {
		// 	//mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, x, y, 0xFF0000);
		// 	if(cube->draw_end != 0 && cube->draw_start != 0 )
		// 		my_mlx_pixel_put(&cube->img, x, y, 0x00FF0000);
		// }


		
		x++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img,0, 0);

}