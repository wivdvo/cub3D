/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_key_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:27:03 by fseles            #+#    #+#             */
/*   Updated: 2024/03/15 15:27:19 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	utils_d(t_cube *cube, double old_dir_x, double old_plane_x)
{
	old_dir_x = cube->dir_x;
	cube->dir_x = cube->dir_x * cos(N) - cube->dir_y * sin(N);
	cube->dir_y = old_dir_x * sin(N) + cube->dir_y * cos(N);
	old_plane_x = cube->plane_x;
	cube->plane_x = cube->plane_x * cos(N) - cube->plane_y * sin(N);
	cube->plane_y = old_plane_x * sin(N) + cube->plane_y * cos(N);
}
