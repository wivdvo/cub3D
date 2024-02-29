/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:33:02 by fseles            #+#    #+#             */
/*   Updated: 2024/02/29 09:33:06 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"


void junk_init(t_junk *junk)
{
	junk->we = 0;
	junk->so = 0;
	junk->ea = 0;
	junk->no = 0;
	junk->f = 0;
	junk->c = 0;
}
//return 0 if there is something after space that is not space 
//return 1 if ok
int after_space_checker(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if(line[i] != ' ')
			return (0);
		i++;
	}
	return(1);
}

//return 1 and increase flag if corret
//return 0 if not correct
int flag_setter(char *line, t_junk *junk)
{
	if (strncmp(line, "WE", 2) == 0)
		return (junk->we++, 1);
	else if (strncmp(line, "SO", 2) == 0)
		return (junk->so++, 1);
	else if (strncmp(line, "NO", 2) == 0)
		return (junk->no++, 1);
	else if (strncmp(line, "EA", 2) == 0)
		return (junk->ea++, 1);
	else 
		return(0);
}

//return 1 if ok 0 if not
int is_valid_line_start(char *line, t_junk *junk)
{
	if (line[0] == '\n')
		return(1);
	if(line[0] == 'C')
	{
		junk->c++;
		return(1);
	}
	if(line[0] == 'F')
	{
		junk->f++;
		return(1);
	}
	if(line[0] == ' ')
		return (after_space_checker(line));
	return (flag_setter(line, junk));
}
//retrun 1 if junk flag is bigger than1
//return 0 if ok
int check_junk_flags(t_junk *junk)
{
	if(junk->c > 1 || junk->f > 1)
		return (1);
	if(junk->we > 1 || junk->ea > 1)
		return (1);
	if(junk->so > 1 || junk->no > 1)
		return (1);
	return (0);
}

//check if there is junk in file if so return 1
//if everthing is ok retunr 0
int junk_checker(char **full_file, int map_beggin)
{
	int i;
	t_junk junk;
	printf("map beggin at %d\n", map_beggin);

	junk_init(&junk);
	i = 0;
	if(full_file == NULL || *full_file == NULL)
		return (1);
	while(i < map_beggin)
	{
		//printf("%s\n", full_file[i]);
		if(is_valid_line_start(full_file[i], &junk) == 0)
			return (1);
		if(check_junk_flags(&junk) != 0)
			return (1);
		//isvalidstart != 1
			//return false;
		//if(flagscheck != 1
			//returnfalse
		i ++;
	}
	return (0);
}
