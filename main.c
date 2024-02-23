/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:42:09 by wvan-der          #+#    #+#             */
/*   Updated: 2024/02/23 14:42:32 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	main(void)
{
	t_cube	cube;

	init_pars_struct(&cube);
	parsing(&cube, "file.cub");
	render(&cube);
	pars_exit(&cube, NULL);
	return (0);
}
