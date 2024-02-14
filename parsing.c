/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willem <willem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:30:02 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/14 18:20:57 by willem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	init_pars_struct(t_cube *cube)
{
	cube->file = NULL;
	cube->map = NULL;
	cube->max_x = 0;
	cube->max_y = 0;
	cube->info_start = 0;
	cube->info_end = 0;
	cube->no_path = NULL;
	cube->ea_path = NULL;
	cube->we_path = NULL;
	cube->so_path = NULL;
	cube->no_flag = 0;
	cube->ea_flag = 0;
	cube->we_flag = 0;
	cube->so_flag = 0;
	cube->floor_r = 0;
	cube->floor_g = 0;
	cube->floor_b = 0;
	cube->ceiling_r = 0;
	cube->ceiling_g = 0;
	cube->ceiling_b = 0;
	cube->map_begin = 0;
	cube->map_end = 0;
	cube->x = 0;
	cube->y = 0;
	cube->mlx_ptr = NULL;
	cube->win_ptr = NULL;
	cube->no_img = NULL;
	cube->ea_img = NULL;
	cube->we_img = NULL;
	cube->so_img= NULL;
	cube->w_pressed = 0;
	cube->a_pressed = 0;
	cube->s_pressed = 0;
	cube->d_pressed = 0;
	cube->left_pressed = 0;
	cube->right_pressed = 0;
	cube->wall_x = 0;
	cube->img_x = 0;
	cube->step = 0;
}

int	find_map_begin(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (cube->file[i])
	{
		j = 0;
		while (cube->file[i][j] && cube->file[i][j] == ' ')
		{
			j++;
		}
		if (cube->file[i][j] == '1' || cube->file[i][j] == '0')
			break;
		if (cube->file[i][j] == 'N' && cube->file[i][j + 1] != 'O')
			break;
		if (cube->file[i][j] == 'E' && cube->file[i][j + 1] != 'A')
			break;
		if (cube->file[i][j] == 'S' && cube->file[i][j + 1] != 'O')
			break;
		if (cube->file[i][j] == 'W' && cube->file[i][j + 1] != 'E')
			break;
		i++;
	}
	cube->map_begin = i;
	//printf("begin%s", cube->file[i]);
}

int	parsing(t_cube *cube, char *path)
{
	if (make_array(cube, path) == -1)
		return (-1);
	find_map_begin(cube);
	if (get_textures(cube) != 0)
		return (-1);
	if (get_colors(cube) != 0)
		return (-1);
	make_map(cube);

	if(is_map_cased(cube) != 1)
	{
		printf("\nmap is not cased\n");
		pars_exit(cube, NULL);
	}
	else 
	{
		printf("\nmap is cased\n");
	}

	printf("floor r%d\n", cube->floor_r);
	printf("floor g%d\n", cube->floor_g);
	printf("floor b%d\n", cube->floor_b);

	printf("ceiling r%d\n", cube->ceiling_r);
	printf("ceiling g%d\n", cube->ceiling_g);
	printf("ceiling b%d\n", cube->ceiling_b);


	return (0);
}

// int main()
// {
// 	return parsing("file.cub");
	
// }