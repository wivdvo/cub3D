/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cased_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:12:36 by fseles            #+#    #+#             */
/*   Updated: 2024/02/23 12:12:41 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

//check if there is wall on right of player or 0
//return 1 if there is 
//return 0 if there is no wall
int	right_check(char dot, int row, int column, char **map)
{
	int	map_row;
	int	map_column;
	int	wall;

	(void) dot;
	map_row = row;
	map_column = column;
	if (ft_strlen1(map[map_row]) - 1 <= (unsigned long) column)
		return (0);
	map_column ++;
	wall = 0;
	while (wall == 0 && map[row][column] != '\0')
	{
		if (is_end_map_char(map[row][column]) == 1)
			return (0);
		if (map[row][column] == '1')
			wall = 1;
		column++;
	}
	return (wall);
}

//check if there is wall on left of player or 0
//return 1 if there is 
//return 0 if there is no wall
int	left_check(char dot, int row, int column, char **map)
{
	int	map_row;
	int	map_column;
	int	wall;

	(void) dot;
	map_row = row;
	if (column == 0)
		return (0);
	map_column = column - 1;
	wall = 0;
	while (wall == 0 && map_column != -1)
	{
		if (is_end_map_char(map[row][map_column]) == 1)
			return (0);
		if (map[row][map_column] == '1')
			wall = 1;
		map_column--;
	}
	return (wall);
}

int	down_check(char dot, int row, int column, char **map)
{
	int	last_row;
	int	wall;
	int	map_row;
	int	map_column;

	(void) dot;
	map_column = column;
	last_row = get_map_rows(map);
	if (row == last_row - 1)
		return (0);
	map_row = row + 1;
	wall = 0;
	while (map_row < last_row && wall == 0)
	{
		if (ft_strlen1(map[map_row]) <= (unsigned long) column)
			return (0);
		if (is_end_map_char(map[map_row][map_column]) == 1)
			return (0);
		if (map[map_row][map_column] == '1')
			wall = 1;
		map_row++;
	}
	return (wall);
}

int	up_check(char dot, int row, int column, char **map)
{
	int	wall;
	int	map_row;
	int	map_column;

	(void) dot;
	map_column = column;
	wall = 0;
	if (row == 0)
		return (0);
	map_row = row - 1;
	while (map_row != -1 && wall == 0)
	{
		if (ft_strlen1(map[map_row]) - 1 <= (unsigned long) column)
			return (0);
		if (is_end_map_char(map[map_row][map_column]) == 1)
			return (0);
		if (map[map_row][map_column] == '1')
			wall = 1;
		map_row --;
	}
	return (wall);
}

int	all_direction_checker(char dot, int xd, int yd, char **map)
{
	int	value;

	value = 0;
	if (is_valid_char(dot) != 1)
		return (0);
	if (need_check(dot))
	{
		value = left_check(dot, xd, yd, map);
		value += right_check(dot, xd, yd, map);
		value += down_check(dot, xd, yd, map);
		value += up_check(dot, xd, yd, map);
		if (value != 4)
			return (0);
	}
	return (1);
}
