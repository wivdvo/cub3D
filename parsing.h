#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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

#endif