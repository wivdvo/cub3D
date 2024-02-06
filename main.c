#include "headers/cub3d.h"

int main()
{
	void *mlx; 
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Prozor stare majke");
	mlx_loop(mlx);
	
	return (EXIT_FAILURE);
}