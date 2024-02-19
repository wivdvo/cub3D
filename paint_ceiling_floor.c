
#include "headers/cub3d.h"

static unsigned int rgb_to_hex(int red, int green, int blue)
{
	unsigned int hex;

	hex = 0;
	hex += (red << 16);
	hex += (green << 8);
	hex += blue;
	return (hex);
}

void paint_ceiling_floor(t_cube *cube)
{
	unsigned int ceiling_color;// = rgb_to_hex(0x26,0x50,0x73);//0x00FFFFFF;
	unsigned int floor_color;//= rgb_to_hex(0xF1,0xFA,0xDA); //0x00AB88BB88;
	int x = 0;
	int y = 0;

	floor_color = rgb_to_hex(cube->floor_r,cube->floor_g, cube->floor_b); //0x00AB88BB88;
	ceiling_color = rgb_to_hex(cube->ceiling_r,cube->ceiling_g, cube->ceiling_b);//0x00FFFFFF;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if(y < (HEIGHT/ 2))
				my_mlx_pixel_put(&cube->img, x, y, ceiling_color);
			else
				my_mlx_pixel_put(&cube->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}
