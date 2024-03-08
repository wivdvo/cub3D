/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:26:46 by fseles            #+#    #+#             */
/*   Updated: 2024/03/08 14:15:40 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	reset_start_end(t_cube *cube)
{
	cube->info_end = 0;
	cube->info_start = 0;
}

void	check_after_color(t_cube *cube, int i, char *line)
{
	if (line[i] != ',' && line[i] != '\n')
		pars_exit(cube, "not 3 color values or garbage");
}
