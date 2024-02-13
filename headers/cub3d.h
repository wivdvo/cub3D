/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willem <willem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:04:47 by fseles            #+#    #+#             */
/*   Updated: 2024/02/13 18:35:37 by willem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080
# define MS 1
# define RS 0.2
# include <fcntl.h>
# include <math.h>
//# include <mlx.h>
#include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "parsing.h"


void render(t_cube *cube);
int	render_exit(t_cube *cube);
void	init_mlx(t_cube *cube);
void	init_img(t_cube *cube);
void	init_no(t_cube *cube);
void	init_ea(t_cube *cube);
void	init_so(t_cube *cube);
void	init_we(t_cube *cube);
void raycaster(t_cube *cube);
int	handle_input(int keysym, t_cube *cube);


#endif

