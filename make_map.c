/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:26:05 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/08 14:48:02 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	make_map(t_pars *pars)
{
	make_map_array(pars);
}

int make_map_array(t_pars *pars)
{
	find_map_end(pars);
	check_that_nothing_after_end(pars);
	copy_map(pars);
	check_invalid_char(pars);
	//check_that_encased(pars);
}

void	check_invalid_char(t_pars *pars)
{
	int x;
	int y;
	int	flag;

	y = 0;
	flag = 0;
	while (pars->map[y])
	{
		x = 0;
		while (pars->map[y][x])
		{
			if (pars->map[y][x] != '1' && pars->map[y][x] != '0'
					&& pars->map[y][x] != 'N' && pars->map[y][x] != 'E'
					&& pars->map[y][x] != 'S' && pars->map[y][x] != 'W'
					&& pars->map[y][x] != '\n' && pars->map[y][x] != ' ')
			{
				pars_exit(pars, "invalid char in map");
			}
			if (pars->map[y][x] == 'N' || pars->map[y][x] == 'E'
					|| pars->map[y][x] == 'S' || pars->map[y][x] == 'W')
			{
				if (flag == 0)
					flag = 1;
				else
					pars_exit(pars, "multible player");
			}

			x++;
		}
		y++;
	}
}

void	check_that_nothing_after_end(t_pars *pars)
{
	int i;
	int j;

	i = pars->map_end + 1;
	while (pars->file[i])
	{
		j = 0;
		while (pars->file[i][j] && (pars->file[i][j] == ' ' || pars->file[i][j] == '\n'))
			j++;
		if (pars->file[i][j] != 0)
			pars_exit(pars, "there is something after map");
		i++;
	}
}

int find_map_end(t_pars *pars)
{
	int i;
	int j;

	i = pars->map_begin;
	while (pars->file[i])
	{
		j = 0;
		while (pars->file[i][j] && pars->file[i][j] == ' ')
			j++;
		if (pars->file[i][j] != '1' && pars->file[i][j] != '0'
				&& pars->file[i][j] != 'N' && pars->file[i][j] != 'E'
				&& pars->file[i][j] != 'S' && pars->file[i][j] != 'W')
			break;
		i++;
	}
	pars->map_end = --i;
	//printf("end%s", pars->file[pars->map_end]);
}

void	print_map(t_pars *pars)
{
	int i;

	i = 0;
	while (pars->map && pars->map[i])
	{
		printf("%s", pars->map[i]);
		i++;
	}
}

int copy_map(t_pars *pars)
{
	int i;
	int j;

	j = 0;
	i = pars->map_begin;
	pars->map = (char **)malloc(sizeof(char *) *
			(pars->map_end - pars->map_begin + 2));
	if (!pars->map)
		pars_exit(pars, "malloc failed");
	while (pars->file[i] && i <= pars->map_end)
	{
		pars->map[j] = ft_substr(pars->file[i], 0, ft_strlen1(pars->file[i]));
		if (!pars->map[j])
			pars_exit(pars, "malloc failed");
		pars->map[j + 1] = 0;
		j++;
		i++;
	}
	print_map(pars);
}
