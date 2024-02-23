/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:07:25 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 12:07:29 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	get_colors(t_cube *cube)
{
	find_floor(cube);
	find_ceiling(cube);
	return (0);
}

int	check_number(t_cube *cube, char *res, int *value)
{
	char	*itoa;

	*value = ft_atoi(res);
	itoa = ft_itoa(*value);
	if (!itoa)
	{
		free(res);
		pars_exit(cube, "malloc failed");
	}
	if (ft_strncmp(res, itoa, ft_strlen(res)) || *value > 255 || *value < 0)
	{
		free(res);
		free(itoa);
		pars_exit(cube, "2 invalid color value");
	}
	free(res);
	free(itoa);
}

void	put_color_floor(t_cube *cube, int value, int flag)
{
	if (flag == 1)
		cube->floor_r = value;
	if (flag == 2)
		cube->floor_g = value;
	if (flag == 3)
		cube->floor_b = value;
}

void	put_color_ceiling(t_cube *cube, int value, int flag)
{
	if (flag == 1)
		cube->ceiling_r = value;
	if (flag == 2)
		cube->ceiling_g = value;
	if (flag == 3)
		cube->ceiling_b = value;
}
