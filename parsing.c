/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:30:02 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/07 14:36:31 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_pars_struct(t_pars *pars)
{
	pars->file = NULL;
	pars->map = NULL;
	pars->max_x = 0;
	pars->max_y = 0;
	pars->info_start = 0;
	pars->info_end = 0;
	pars->no_path = NULL;
	pars->ea_path = NULL;
	pars->we_path = NULL;
	pars->so_path = NULL;
	pars->no_flag = 0;
	pars->ea_flag = 0;
	pars->we_flag = 0;
	pars->so_flag = 0;
	pars->floor_r = 0;
	pars->floor_g = 0;
	pars->floor_b = 0;
	pars->ceiling_r = 0;
	pars->ceiling_g = 0;
	pars->ceiling_b = 0;
	pars->map_begin = 0;
	pars->map_end = 0;
	pars->x = 0;
	pars->y = 0;
}

int	find_map_begin(t_pars *pars)
{
	int i;
	int j;

	i = 0;
	while (pars->file[i])
	{
		j = 0;
		while (pars->file[i][j] && pars->file[i][j] == ' ')
		{
			j++;
		}
		if (pars->file[i][j] == '1' || pars->file[i][j] == '0')
			break;
		if (pars->file[i][j] == 'N' && pars->file[i][j + 1] != 'O')
			break;
		if (pars->file[i][j] == 'E' && pars->file[i][j + 1] != 'A')
			break;
		if (pars->file[i][j] == 'S' && pars->file[i][j + 1] != 'O')
			break;
		if (pars->file[i][j] == 'W' && pars->file[i][j + 1] != 'E')
			break;
		i++;
	}
	pars->map_begin = i;
	//printf("begin%s", pars->file[i]);
}

int	parsing(char *path)
{
	t_pars pars;
	init_pars_struct(&pars);
	if (make_array(&pars, path) == -1)
		return (-1);
	find_map_begin(&pars);
	if (get_textures(&pars) != 0)
		return (-1);
	if (get_colors(&pars) != 0)
		return (-1);
	make_map(&pars);
	

	// printf("floor r%d\n", pars.floor_r);
	// printf("floor g%d\n", pars.floor_g);
	// printf("floor b%d\n", pars.floor_b);

	// printf("ceiling r%d\n", pars.ceiling_r);
	// printf("ceiling g%d\n", pars.ceiling_g);
	// printf("ceiling b%d\n", pars.ceiling_b);


	pars_exit(&pars, "end");
	return (0);
}

int main()
{
	return parsing("file.cub");
	
}