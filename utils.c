/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:45:17 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/22 15:11:59 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	put_error(char *str)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	while (str && str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	if (str)
		write(2, "\n", 1);
}

void	print_file_array(t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->file[i])
	{
		printf("%s", cube->file[i]);
		i++;
	}
	puts("");
}

void	free_array(char ***array)
{
	char	**arr;
	int		i;

	i = 0;
	arr = *array;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	pars_exit(t_cube *cube, char *msg)
{
	if (msg)
		put_error(msg);
	if (cube->map)
		free_array(&cube->map);
	if (cube->file)
		free_array(&cube->file);
	if (cube->no_path)
		free(cube->no_path);
	if (cube->we_path)
		free(cube->we_path);
	if (cube->ea_path)
		free(cube->ea_path);
	if (cube->so_path)
		free(cube->so_path);
	close(cube->fd);
	exit(1);
}

int	render_exit(t_cube *cube)
{
	if (cube->no_img)
		mlx_destroy_image(cube->mlx_ptr, cube->no_img);
	if (cube->ea_img)
		mlx_destroy_image(cube->mlx_ptr, cube->ea_img);
	if (cube->we_img)
		mlx_destroy_image(cube->mlx_ptr, cube->we_img);
	if (cube->so_img)
		mlx_destroy_image(cube->mlx_ptr, cube->so_img);
	if (cube->img.img)
		mlx_destroy_image(cube->mlx_ptr, cube->img.img);
	if (cube->win_ptr)
		mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	if (cube->mlx_ptr)
		mlx_destroy_display(cube->mlx_ptr);
	free(cube->mlx_ptr);
	pars_exit(cube, NULL);
	return (0);
}
