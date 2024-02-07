#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_pars
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
} t_pars;

void	put_error(char *str);
void	print_file_array(t_pars *pars);
void	init_pars_struct(t_pars *pars);
int	get_textures(t_pars *pars);
int	set_start_end(t_pars *pars, char *line);
void reset_start_end(t_pars *pars);
int	extract_info(t_pars *pars, char *line, char flag);
int	find(t_pars *pars, char *dir);
int check_flags(t_pars *pars);
int	make_array(t_pars *pars, char *path);
int	realloc_file_array(t_pars *pars, char *line, int y);
int	read_file_array(t_pars *pars, int fd);
void	pars_exit(t_pars *pars, char *msg);
int	make_map(t_pars *pars);
int make_map_array(t_pars *pars);
int find_map_end(t_pars *pars);
int	get_colors(t_pars *pars);
void	check_that_nothing_after_end(t_pars *pars);

#endif