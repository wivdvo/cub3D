/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:45:17 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/06 15:06:54 by wvan-der         ###   ########.fr       */
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