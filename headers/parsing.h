#ifndef PARSING_H
#define PARSING_H

typedef struct s_cube
{
	char **map;
	char **file;
	int	max_x;
	int max_y;
	int	info_start;
	int info_end;
	char *no_path;
	char *we_path;
	char *ea_path;
	char *so_path;
	int	no_flag;
	int we_flag;
	int ea_flag;
	int so_flag;
	int	floor_r;
	int floor_g;
	int floor_b;
	int ceiling_r;
	int ceiling_g;
	int ceiling_b;
	int	map_begin;
	int	map_end;
	int	x;
	int y;
	void *mlx_ptr;
	void *win_ptr;
	void *no_img;
	void *ea_img;
	void *we_img;
	void *so_img;
	int	wall_width;
	int wall_height;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int map_x;
	int map_y;
	double	dis_to_side_x;
	double	dis_to_side_y;
	double	delta_x;
	double	delta_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		hit; //flag if wall was hit
	int		side; //1 = NS wall ;; 2 = EW wall
	double		big_nb;
	int		line_height;
	int		draw_start;
	int		draw_end;

	
} t_cube;


void	print_map(t_cube *cube);
int is_map_cased(t_cube *cube);
void	put_error(char *str);
void	print_file_array(t_cube *cube);
void	init_pars_struct(t_cube *cube);
int	get_textures(t_cube *cube);
int	set_start_end(t_cube *cube, char *line);
void reset_start_end(t_cube *cube);
int	extract_info(t_cube *cube, char *line, char flag);
int	find(t_cube *cube, char *dir);
int check_flags(t_cube *cube);
int	make_array(t_cube *cube, char *path);
int	realloc_file_array(t_cube *cube, char *line, int y);
int	read_file_array(t_cube *cube, int fd);
int	parsing(t_cube *cube, char *path);
void	pars_exit(t_cube *cube, char *msg);
int	make_map(t_cube *cube);
int make_map_array(t_cube *cube);
int find_map_end(t_cube *cube);
int	get_colors(t_cube *cube);
void	check_that_nothing_after_end(t_cube *cube);
void	check_invalid_char(t_cube *cube);

#endif