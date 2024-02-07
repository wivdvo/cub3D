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
	if(need_check(dot))
	{
		int value;
		value = right_check(dot, xd, yd, map);
		if(value == 0)
			return(0);
		//printf("karakter %c need check\n", dot);
		//checkleft
		//chekkright
		//checkdown
		//checkup
	}
	else 
		//printf("karakter %c do not need check\n", dot);
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
			//printf("map is close = %d\n", value);
			if(value != 1)
			{
				printf("nije zatvoren\n");
				return(0);
			}
			column++;	
		}
		row++;
	}
	printf("zatvorena mapa\n");

	return (0);
}
