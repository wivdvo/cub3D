/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:13:49 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/08 15:00:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

// int	get_colors(t_cube *cube)
// {
// 	find_floor(cube);
// 	find_ceiling(cube);
// 	return (0);
// }

// int	check_number(t_cube *cube, char *res, int *value)
// {
// 	char	*itoa;

// 	*value = ft_atoi(res);
// 	itoa = ft_itoa(*value);
// 	if (!itoa)
// 	{
// 		free(res);
// 		pars_exit(cube, "malloc failed");
// 	}
// 	if (ft_strncmp(res, itoa, ft_strlen(res)) || *value > 255 || *value < 0)
// 	{
// 		free(res);
// 		free(itoa);
// 		pars_exit(cube, "2 invalid color value");
// 	}
// 	free(res);
// 	free(itoa);
// }

// void	put_color_floor(t_cube *cube, int value, int flag)
// {
// 	if (flag == 1)
// 		cube->floor_r = value;
// 	if (flag == 2)
// 		cube->floor_g = value;
// 	if (flag == 3)
// 		cube->floor_b = value;
// }

// void	put_color_ceiling(t_cube *cube, int value, int flag)
// {
// 	if (flag == 1)
// 		cube->ceiling_r = value;
// 	if (flag == 2)
// 		cube->ceiling_g = value;
// 	if (flag == 3)
// 		cube->ceiling_b = value;
// }

//flag 1 = color to extract is red
//flag 2 = color is green
//falg 4 = color is blue
int	extract_color(t_cube *cube, char *line, int flag, char floor_ceiling)
{
	char	*res;
	int		value;
	int		i;
	int		j;

	i = cube->info_start;
	j = 0;
	res = (char *)malloc(4);
	if (!res)
		pars_exit(cube, "malloc failed");
	while (i < cube->info_end && line[i])
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = 0;
	check_number(cube, res, &value);
	if (floor_ceiling == 'F')
		put_color_floor(cube, value, flag);
	if (floor_ceiling == 'C')
		put_color_ceiling(cube, value, flag);
	return (0);
}

//flag 1 = color to extract is red
//flag 2 = color is green
//falg 4 = color is blue
void	set_start_end_color(t_cube *cube, char *line, char floor_ceiling)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	reset_start_end(cube);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			cube->info_start = i;
			while (line[i] && line[i] != ','
				&& line[i] != ' ' && line[i] != '\n')
			{
				if (!ft_isdigit(line[i]))
					pars_exit(cube, "invalid color value");
				i++;
			}
			cube->info_end = i;
			extract_color(cube, line, flag++, floor_ceiling);
		}
		i++;
	}
	if (flag != 4)
		pars_exit(cube, "not 3 color values");
}

int	find_ceiling(t_cube *cube)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (cube->file[i] && i < cube->map_begin)
	{
		if (cube->file[i][0] == 'C')
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 0)
		pars_exit(cube, "ceiling color msissing or after map");
	set_start_end_color(cube, cube->file[i], 'C');
	return (0);
}

int	find_floor(t_cube *cube)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (cube->file[i] && i < cube->map_begin)
	{
		if (cube->file[i][0] == 'F')
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 0)
		pars_exit(cube, "floor color msissing or after map");
	set_start_end_color(cube, cube->file[i], 'F');
	return (0);
}
