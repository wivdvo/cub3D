/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_ceiling_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:25:36 by fseles            #+#    #+#             */
/*   Updated: 2024/02/22 17:25:41 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static unsigned int	rgb_to_hex(int red, int green, int blue)
{
	unsigned int	hex;

	hex = 0;
	hex += (red << 16);
	hex += (green << 8);
	hex += blue;
	return (hex);
}

void	paint_ceiling_floor(t_cube *cube)
{
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	int				x;
	int				y;

	x = 0;
	y = 0;
	floor_color = rgb_to_hex(cube->floor_r, cube->floor_g, cube->floor_b);
	ceiling_color = rgb_to_hex(cube->ceiling_r,
			cube->ceiling_g, cube->ceiling_b);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < (HEIGHT / 2))
				my_mlx_pixel_put(&cube->img, x, y, ceiling_color);
			else
				my_mlx_pixel_put(&cube->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}
