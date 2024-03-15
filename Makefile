NAME = cub3D

HEADERS = headers/cub3d.h \
		headers/parsing.h 

SRCS =	main.c \
		cased_map_utils.c \
		cased_map.c \
		parsing.c \
		get_textures_utils.c \
		get_textures.c \
		junk_checker.c \
		junk_init.c \
		get_colors.c \
		get_colors_utils.c \
		make_file_array.c \
		utils.c \
		make_map_utils.c \
		make_map.c \
		my_mlx_pixel_put.c \
		paint_ceiling_floor.c \
		render_init_img.c \
		render_key_d.c \
		render_key_press.c \
		render_key_press2.c \
		render_math.c \
		render_math2.c \
		render.c \
		spawn_utils.c \
		spawn.c

OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADERS)
	$(CC) -g $(CFLAGS) -c $< -o $@

CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFLAGS =	-lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			cd libft && $(MAKE) && $(MAKE) bonus
			$(CC) $(OBJS) -g libft/libft.a $(LIBFLAGS) -o $(NAME)

clean:
		cd libft && $(MAKE) fclean 
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.phony:		clean fclean re all