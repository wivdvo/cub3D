/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:13:49 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/06 17:34:59 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_colors(t_pars *pars)
{
	find_floor(pars);
	find_ceiling(pars);
}

int	check_number(t_pars *pars, char *res, int *value)
{
	char *itoa;

	*value = ft_atoi(res);
	itoa = ft_itoa(*value);
	//printf("res%s\n", res);
	//printf("itoa%s\n", itoa);
	if (!itoa)
		pars_exit(pars, "malloc failed");
	if (ft_strncmp(res, itoa, ft_strlen(res)) || *value > 255 || *value < 0)
		pars_exit(pars, "2 invalid color value");
}

void	put_color_floor(t_pars *pars, int value, int flag)
{
	if (flag == 1)
		pars->floor_r = value;
	if (flag == 2)
		pars->floor_g = value;
	if (flag == 3)
		pars->floor_b = value;
}

void	put_color_ceiling(t_pars *pars, int value, int flag)
{
	if (flag == 1)
		pars->ceiling_r = value;
	if (flag == 2)
		pars->ceiling_g = value;
	if (flag == 3)
		pars->ceiling_b = value;
}



//flag 1 = color to extract is red
//flag 2 = color is green
//falg 4 = color is blue
int	extract_color(t_pars *pars, char *line, int flag, char floor_ceiling)
{
	char *res;
	int	value;
	int i;
	int j;

	i = pars->info_start;
	j = 0;
	res = (char *)malloc(4);
	if (!res)
		return (-1);
	while (i < pars->info_end && line[i])
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = 0;
	check_number(pars, res, &value);
	if (floor_ceiling == 'F')
		put_color_floor(pars, value, flag);
	if (floor_ceiling == 'C')
		put_color_ceiling(pars, value, flag);
}

//flag 1 = color to extract is red
//flag 2 = color is green
//falg 4 = color is blue
int	set_start_end_color(t_pars *pars, char *line, char floor_ceiling)
{
	int i;
	int flag;

	i = 0;
	flag = 1;
	reset_start_end(pars);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			pars->info_start = i;
			while (line[i] && line[i] != ',' && line[i] != ' ' && line[i] != '\n')
			{
				//printf("c:%c\n", line[i]);
				if (!ft_isdigit(line[i]))
					pars_exit(pars, "1 invalid color value");
				i++;
			}
			pars->info_end = i;
			extract_color(pars, line, flag++, floor_ceiling);
		}
		i++;
	}
	if (flag != 4)
		pars_exit(pars, "not 3 color values");
}

int find_ceiling(t_pars *pars)
{
	int	i;
	int	found;
	
	i = 0;
	found = 0;
	while (pars->file[i] && i < pars->map_begin)
	{
		if (pars->file[i][0] == 'C')
		{
			found = 1;
			break;
		}
		i++;
	}
	if (found == 0)
		pars_exit(pars, "ceiling color msissing or after map");
	set_start_end_color(pars, pars->file[i], 'C');
}

int find_floor(t_pars *pars)
{
	int	i;
	int	found;
	
	i = 0;
	found = 0;
	while (pars->file[i] && i < pars->map_begin)
	{
		if (pars->file[i][0] == 'F')
		{
			found = 1;
			break;
		}
		i++;
	}
	if (found == 0)
		pars_exit(pars, "floor color msissing or after map");
	set_start_end_color(pars, pars->file[i], 'F');

}
