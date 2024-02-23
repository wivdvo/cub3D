/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:53:14 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 13:03:42 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cube
{
	t_data	img;
	char	**map;
	char	**file;
	int		max_x;
	int		max_y;
	int		info_start;
	int		info_end;
	char	*no_path;
	char	*we_path;
	char	*ea_path;
	char	*so_path;
	int		no_flag;
	int		we_flag;
	int		ea_flag;
	int		so_flag;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	int		map_begin;
	int		map_end;
	int		x;
	int		y;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*no_img;
	void	*ea_img;
	void	*we_img;
	void	*so_img;
	int		wall_width;
	int		wall_height;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	dis_to_side_x;
	double	dis_to_side_y;
	double	delta_x;
	double	delta_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		hit; //flag if wall was hit
	int		side; //1 = NS wall ;; 2 = EW wall
	double	big_nb;
	int		lh;
	int		draw_start;
	int		draw_end;
	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		d_pressed;
	int		left_pressed;
	int		right_pressed;
	int		spawn_direction;
	int		esc_pressed;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*img_data;
	int		tex_x;
	double	step;
	int		fd;
}	t_cube;

int		all_direction_checker(char dot, int xd, int yd, char **map);
int		copy_map(t_cube *cube);
int		check_number(t_cube *cube, char *res, int *value);
int		find_ceiling(t_cube *cube);
int		find_floor(t_cube *cube);
void	put_color_ceiling(t_cube *cube, int value, int flag);
void	put_color_floor(t_cube *cube, int value, int flag);
void	print_map(t_cube *cube);
int		is_map_cased(t_cube *cube);
int		is_end_map_char(char c);
int		is_valid_char(char c);
void	put_error(char *str);
void	print_file_array(t_cube *cube);
void	init_pars_struct(t_cube *cube);
int		get_textures(t_cube *cube);
int		get_map_rows(char **map);
int		set_start_end(t_cube *cube, char *line);
void	reset_start_end(t_cube *cube);
int		extract_info(t_cube *cube, char *line, char flag);
int		find(t_cube *cube, char *dir);
int		check_flags(t_cube *cube);
int		make_array(t_cube *cube, char *path);
int		need_check(char c);
int		realloc_file_array(t_cube *cube, char **line, int y);
int		read_file_array(t_cube *cube, int fd);
int		parsing(t_cube *cube, char *path);
void	pars_exit(t_cube *cube, char *msg);
int		make_map(t_cube *cube);
int		make_map_array(t_cube *cube);
int		find_map_end(t_cube *cube);
int		get_colors(t_cube *cube);
void	check_that_nothing_after_end(t_cube *cube);
void	check_invalid_char(t_cube *cube);

#endif
