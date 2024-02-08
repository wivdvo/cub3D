/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:02:30 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/07 12:14:27 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

//handels findign paths
//ret -1 malloc fail
//ret 0 good
//ret 1 not all textures found
int	get_textures(t_pars *pars)
{
	int	ret;

	ret = find(pars, "NO");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		pars->no_flag = 1;
	ret = find(pars, "EA");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		pars->ea_flag = 1;
	ret = find(pars, "SO");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		pars->so_flag = 1;
	ret = find(pars, "WE");
	if (ret == -1)
		return (-1);
	if (ret == 0)
		pars->we_flag = 1;
	return (check_flags(pars));
}

int	set_start_end(t_pars *pars, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '.' && line[i + 1] == '/')
		{
			pars->info_start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\n')
				i++;
			pars->info_end = i;
			return (0);
		}
		i++;
	}
	return (0);
}

void reset_start_end(t_pars *pars)
{
	pars->info_end = 0;
	pars->info_start = 0;
}

int	extract_info(t_pars *pars, char *line, char flag)
{
	char *info;
	int	i;
	int j;

	i = 0;
	j = pars->info_start;
	info = (char *)malloc(pars->info_end - pars->info_start + 2);
	if (!info)
		pars_exit(pars, "malloc failed");
	while (j < pars->info_end)
	{
		info[i] = line[j];
		i++;
		j++;
	}
	info[i] = 0;
	if (flag == 'N')
		pars->no_path = info;
	if (flag == 'E')
		pars->ea_path = info;
	if (flag == 'S')
		pars->so_path = info;
	if (flag == 'W')
		pars->we_path = info;
	return (0);
}
//finds path to texture
//ret 0 good; ret -1 malloc fail; ret 1 not found
int	find(t_pars *pars, char *dir)
{
	int i;
	int found;

	i = 0;
	found = 0;
	reset_start_end(pars);
	while (pars->file[i] && i < pars->map_begin)
	{
		if (pars->file[i][0] == dir[0] && pars->file[i][1] == dir[1])
		{
			found = 1;
			break;
		}
		i++;
	}
	if (found == 0)
		return (1);
	set_start_end(pars, pars->file[i]);
	if (extract_info(pars, pars->file[i], dir[0]) == -1)
		return (-1);
	return (0);
}

int check_flags(t_pars *pars)
{
	if (pars->no_flag != 1)
		return (put_error("north texture missing or after map"), 1);
	if (pars->so_flag != 1)
		return (put_error("south texture missing or after map"), 1);
	if (pars->ea_flag != 1)
		return (put_error("east texture missing or after map"), 1);
	if (pars->we_flag != 1)
		return (put_error("west texture missing or after map"), 1);
	return (0);
}