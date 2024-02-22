#include "headers/cub3d.h"


int main()
{
	t_cube cube;
	init_pars_struct(&cube);
	parsing(&cube, "file.cub");
	render(&cube);

	pars_exit(&cube, NULL);
	return (0);
}