/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:04:47 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 13:01:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 640
# define HEIGHT 480
# define IMG_SIZE 100
# define MS 0.006
# define RS 0.003
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define N 1.5708
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "parsing.h"


void	calc_distance_hit_and_height(t_cube *cube);
void	calc_top_and_bottom(t_cube *cube);
void	clac_ray_delta(t_cube *cube);
void	calc_ray_pos_dir(t_cube *cube, int x);
void	calc_pos_of_hit_and_wall_x(t_cube *cube);
void	calc_step_and_side_dist(t_cube *cube);
void	check_gridlines_collision(t_cube *cube);
void	check_d_pressed(t_cube *cube);
void	check_s_pressed(t_cube *cube);
void	check_w_pressed(t_cube *cube);
void	get_spawn_position(t_cube *cube);
void	load_imgs(t_cube *cube);
void	render(t_cube *cube);
int		render_exit(t_cube *cube);
void	round_pos_to_int(t_cube *cube);
void	spawn_player(t_cube *cube);
void	init_mlx(t_cube *cube);
void	init_img(t_cube *cube);
void	init_no(t_cube *cube);
void	init_ea(t_cube *cube);
void	init_so(t_cube *cube);
void	init_we(t_cube *cube);
void	paint_ceiling_floor(t_cube *cube);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	raycaster(t_cube *cube);
int		handle_input(int keysym, t_cube *cube);
int		game_loop(t_cube *cube);
int		key_press(int keysym, t_cube *cube);
int		key_release(int keysym, t_cube *cube);

#endif