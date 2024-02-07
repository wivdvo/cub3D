/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cased_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:58:48 by fseles            #+#    #+#             */
/*   Updated: 2024/02/07 14:58:51 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

//Map must be composed of only 6 possible characters
//0 for empty space 1 for wall
//NSEW for player start position
//return 1 if checked character is valid, 0 if it is not
int	is_valid_char(char c)
{
	const int	valid_char[9] = {'1','0' ,'N' ,'S' ,'E', 'W',' ', '\n', '\0'};
	int			i;

	i = 0;
	while(i < 9)
	{
		if (c == (char)valid_char[i])
			return (1);
		i++;
	}
	return (0);
}

//return number of rows of map
int get_map_rows(char **map)
{
	int i;

	i = 0;
	if(map == NULL || *map==NULL)
		return (0);
	while(map[i] != NULL)
		i++;
	return(i);
}

int all_direction_checker(char dot, int xd, int yd, char **map)
{
	int map_rows;

	map_rows = get_map_rows(map);
	//printf("map rows is %d\n", map_rows);
	if(is_valid_char(dot) != 1)
		return(0);
	return (1);
}

//1 map is valid
//0 map "leaks" or invalid character
int is_map_cased(t_pars *pars)
{
	char **map;
	int map_rows;
	int row;
	int column;

	
	row = 0;
	map = pars->map;
	if (map == NULL || *map == NULL)
	{
		put_error("Is map case failed. Map is NULL\n");
		return(0);
	}
	map_rows = get_map_rows(map);
	while(map[row] != NULL)
	{
		column = 0;
		while(map[row][column] != '\0')
		{
			int value;
			value = all_direction_checker(map[row][column], row, column, map);
			printf("map is close = %d\n", value);
			if(value != 1)
				return(0);
			column++;	
		}
		row++;
	}

	return (0);
}
