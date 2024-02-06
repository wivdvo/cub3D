/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:45:17 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/06 16:41:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	put_error(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	if (str)
		write(2, "\n", 1);
}

void	print_file_array(t_pars *pars)
{
	int i;

	i = 0;
	while (pars->file[i])
	{
		printf("%s", pars->file[i]);
		i++;
	}
	puts("");
}

void	free_array(char ***array)
{
	char **arr;
	int i;

	i = 0;
	arr = *array;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	pars_exit(t_pars *pars, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (pars->map)
		free_array(&pars->map);
	if (pars->file)
		free_array(&pars->file);
	if (pars->no_path)
		free(pars->no_path);
	if (pars->we_path)
		free(pars->we_path);
	if (pars->ea_path)
		free(pars->ea_path);
	if (pars->so_path)
		free(pars->so_path);
	exit(1);
}