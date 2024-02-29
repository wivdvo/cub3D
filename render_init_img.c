/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:51:50 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 13:51:57 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	init_img(t_cube *cube)
{
	init_no(cube);
	init_ea(cube);
	init_so(cube);
	init_we(cube);
}

void	init_no(t_cube *cube)
{
	cube->no_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->no_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->no_img)
	{
		put_error("IMG not found!");
		render_exit(cube);
	}
}

void	init_ea(t_cube *cube)
{
	cube->ea_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->ea_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->ea_img)
	{
		put_error("IMG not found!");
		render_exit(cube);
	}
}

void	init_so(t_cube *cube)
{
	cube->so_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->so_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->so_img)
	{
		put_error("IMG not found!");
		render_exit(cube);
	}
}

void	init_we(t_cube *cube)
{
	cube->we_img = mlx_xpm_file_to_image(cube->mlx_ptr, cube->we_path,
			&cube->wall_width, &cube->wall_height);
	if (!cube->we_img)
	{
		put_error("IMG not found!");
		render_exit(cube);
	}
}
