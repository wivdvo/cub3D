/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cased_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:58:48 by fseles            #+#    #+#             */
/*   Updated: 2024/02/08 15:00:37 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/cub3d.h"


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

//check if c is one of 0 N S E W
//if yes that means that for that character check of closed map is needed
//return 1 if char c need check
//return 0 if it doesnt
int need_check(char c)
{
	const int need_check[5] = {'0', 'N', 'S', 'E', 'W'};
	int i;

	i = 0;
	while(i < 5)
	{
		if(c == (char)need_check[i])
			return (1);
		i++;
	}
	return (0);
}

//if character is space newline or back0
//return 1
//if not retur 0;
int is_end_map_char(char c)
{
	const int end_map_char[3] = {' ', '\n', '\0'};
	int i;

	i = 0;
	while(i < 3)
	{
		if(c == (char)end_map_char[i])
			return(1);
		i++;
	}
	return (0);
}

//check if there is wall on right of player or 0
//return 1 if there is 
//return 0 if there is no wall
int right_check(char dot, int row, int column, char **map)
{
	int map_row;
	int map_column;
	int wall;

	map_row = row;
	map_column = column;
	//printf("before map row\n");
	//printf("map row is %s\n", map[map_row]);
	if(ft_strlen1(map[map_row]) - 1 <= column)
		return(0);
	map_column ++;
	wall = 0;
	while(wall == 0 && map[row][column] != '\0')
	{
		if(is_end_map_char(map[row][column])== 1)
			return(0);
		if(map[row][column] == '1')
			wall = 1;
		column++;
	}
	return(wall);

}
//check if there is wall on left of player or 0
//return 1 if there is 
//return 0 if there is no wall
int left_check(char dot, int row, int column, char **map)
{
	int map_row;
	int map_column;
	int wall;

	map_row = row;
	if(column == 0)
		return (0);
	map_column = column - 1;
	wall = 0;
	while(wall == 0 && map_column != -1)
	{
		if(is_end_map_char(map[row][map_column]) == 1)
			return (0);
		if(map[row][map_column] == '1')
			wall = 1;
		map_column--;
	}
	return (wall);
}

int down_check(char dot, int row, int column, char **map)
{
	int last_row;
	int wall;
	int map_row;
	int map_column;


	map_column = column;
	last_row = get_map_rows(map);
	if(row == last_row - 1)
		return (0);
	map_row = row + 1;
	wall = 0;
	while(map_row < last_row && wall == 0)
	{
		if(ft_strlen1(map[map_row]) - 1 <= column)
			return (0);
		if(is_end_map_char(map[map_row][map_column]) == 1)
			return (0);
		if(map[map_row][map_column] == '1')
			wall = 1;
		map_row++;
	}
	return(wall);
}

int up_check(char dot, int row, int column, char **map)
{
	int wall;
	int map_row;
	int map_column;

	map_column = column;
	wall = 0;
	if(row == 0)
		return (0);
	map_row = row - 1;
	while(map_row != -1 && wall == 0)
	{
		if(ft_strlen1(map[map_row]) -1 <= column)
			return (0);
		if(is_end_map_char(map[map_row][map_column]) == 1)
			return(0);
		if(map[map_row][map_column] == '1')
			wall = 1;
		map_row --;
	}
	return (wall);
}


int all_direction_checker(char dot, int xd, int yd, char **map)
{
	int value;

	value = 0;
	if(is_valid_char(dot) != 1)
		return (0);
	if(need_check(dot))
	{
		value = left_check(dot, xd, yd, map);
		value += right_check(dot, xd, yd, map);
		value += down_check(dot, xd, yd, map);
		value += up_check(dot,xd, yd, map);
		if(value != 4)
			return(0);
	}
	return (1);
}

//1 map is valid
//0 map is not jail and should be 
int is_map_cased(t_cube *cube)
{
	char **map;
	int row;
	int column;
	int value;

	row = 0;
	map = cube->map;
	if (map == NULL || *map == NULL)
		return (put_error("Is map case failed. Map is NULL\n"), 0);
	while (map[row] != NULL)
	{
		column = 0;
		while(map[row][column] != '\0')
		{
			value = all_direction_checker(map[row][column], row, column, map);
			if(value != 1)
				return(put_error("Map is not closed\n"), 0);
			column++;	
		}
		row++;
	}
	return (1);
}
