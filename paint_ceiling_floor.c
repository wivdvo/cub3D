
#include "headers/cub3d.h"

void paint_ceiling_floor(t_cube *cube)
{
	int floor_color = 0x00FFFFFF;
	int ceiling_color = 0x00AB88BB88;
	int x = 0;
	int y = 0;


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