/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:02:30 by wvan-der          #+#    #+#             */
/*   Updated: 2024/03/06 11:50:46 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

//handels findign paths
//ret -1 malloc fail
//ret 0 good
//ret 1 not all textures found
int	get_textures(t_cube *cube)
{
	int	ret;

	ret = find(cube, "NO ");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		cube->no_flag = 1;
	ret = find(cube, "EA ");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		cube->ea_flag = 1;
	ret = find(cube, "SO ");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		cube->so_flag = 1;
	ret = find(cube, "WE ");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		cube->we_flag = 1;
	return (check_flags(cube));
}

int	set_start_end(t_cube *cube, char *line)
{
	int	i;

	i = 2;
	
	while (line[i] && (line[i] == ' ' || line[i] == '.'))
	{
		if (line[i] == '.' && line[i + 1] == '/')
		{
			cube->info_start = i;
			while (line[i] && line[i] != '\n')
				i++;
			cube->info_end = i;
			return (0);
		}
		i++;
	}
	return (0);
}

// void	reset_start_end(t_cube *cube)
// {
// 	cube->info_end = 0;
// 	cube->info_start = 0;
// }

int	extract_info(t_cube *cube, char *line, char flag)
{
	char	*info;
	int		i;
	int		j;

	i = 0;
	j = cube->info_start;
	info = (char *)malloc(cube->info_end - cube->info_start + 2);
	if (!info)
		pars_exit(cube, "malloc failed");
	while (j < cube->info_end)
	{
		info[i] = line[j];
		i++;
		j++;
	}
	info[i] = 0;
	if (flag == 'N')
		cube->no_path = info;
	if (flag == 'E')
		cube->ea_path = info;
	if (flag == 'S')
		cube->so_path = info;
	if (flag == 'W')
		cube->we_path = info;
	return (0);
}

//finds path to texture
//ret 0 good; ret -1 malloc fail; ret 1 not found
int	find(t_cube *cube, char *dir)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	reset_start_end(cube);
	while (cube->file[i] && i < cube->map_begin)
	{
		if (cube->file[i][0] == dir[0] && cube->file[i][1] == dir[1]
			&& cube->file[i][2] == dir[2])
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 0)
		return (1);
	set_start_end(cube, cube->file[i]);
	if (extract_info(cube, cube->file[i], dir[0]) == -1)
		return (-1);
	return (0);
}

int	check_flags(t_cube *cube)
{
	if (cube->no_flag != 1)
		return (pars_exit(cube, "north texture not sperated, missing or after map"), 1);
	if (cube->so_flag != 1)
		return (pars_exit(cube, "south texture not sperated, missing or after map"), 1);
	if (cube->ea_flag != 1)
		return (pars_exit(cube, "east texture not sperated, missing or after map"), 1);
	if (cube->we_flag != 1)
		return (pars_exit(cube, "west texture not sperated, missing or after map"), 1);
	return (0);
}
