/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:30:02 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/06 15:13:12 by wvan-der         ###   ########.fr       */
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
}

int	parsing(char *path)
{
	t_pars pars;
	init_pars_struct(&pars);
	if (make_array(&pars, path) == -1)
		return (-1);
	if (get_textures(&pars) != 0)
		return (-1);
	if (get_colors(&pars) != 0)
		return (-1);
	return (0);
}

int main()
{
	return parsing("file.cub");
}