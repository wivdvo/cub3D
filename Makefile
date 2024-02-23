NAME = cub3D

SRCS =	main.c \
		cased_map_utils.c \
		cased_map.c \
		parsing.c \
		get_textures_utils.c \
		get_textures.c \
		get_colors.c \
		get_colors_utils.c \
		make_file_array.c \
		utils.c \
		make_map.c \
		my_mlx_pixel_put.c \
		paint_ceiling_floor.c \
		render.c \
		spawn.c

OBJS = $(SRCS:.c=.o)



CC = cc
#CFLAGS = -Wall -Werror -Wextra
CFLAGS = -g
LIBFLAGS =	-lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME):	$(OBJS)
			cd libft && $(MAKE) && $(MAKE) bonus
			$(CC) $(OBJS) -g libft/libft.a $(LIBFLAGS) -o $(NAME)

clean:
		cd libft && $(MAKE) fclean 
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.phony:		clean fclean re all