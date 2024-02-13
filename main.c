#include "headers/cub3d.h"


typedef struct s_data{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_dot{
	int x;
	int y;
} t_dot;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void draw_line(int start_x, int start_y, int end_x, t_data *data)
{
	t_dot begin;
	t_dot end;

	begin.x = start_x;
	end.x = end_x;
	if(begin.x > end.x)
	{
		begin.x = end_x;
		end.x = start_x;
	}
	while(begin.x < end.x)
	{
		my_mlx_pixel_put(data, begin.x, start_y, 0x00FF0000);
		begin.x++;
	}
}
int main()
{
	t_cube cube;
	init_pars_struct(&cube);
	parsing(&cube, "file.cub");
	render(&cube);

	pars_exit(&cube, NULL);
	return (0);
}