/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:42:09 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/23 14:42:32 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static int	check_file_type(char *name)
{
	int	file_len;

	if (name == NULL)
		return (0);
	file_len = ft_strlen(name);
	if (file_len < 5)
		return (0);
	file_len--;
	if (name[file_len] == 'b' && name[file_len - 1] == 'u'
		&& name[file_len - 2] == 'c' && name [file_len - 3] == '.')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	if (argc != 2)
	{
		put_error("expected only a map in format *.cub");
		return (1);
	}
	if (check_file_type(argv[1]) != 1)
	{
		put_error("Invalid file name/type");
		return (1);
	}
	init_pars_struct(&cube);
	parsing(&cube, argv[1]);
	if(junk_checker(cube.file, cube.map_begin) == 1)
	{
		put_error("There is junk or duplicate keyword in file");
		pars_exit(&cube, NULL);
	}
	render(&cube);
	pars_exit(&cube, NULL);
	return (0);
}
