NAME = cub3D

SRCS =	main.c \
		cased_map.c \
		parsing.c \
		get_textures.c \
		get_colors.c \
		make_file_array.c \
		utils.c \
		make_map.c \
		my_mlx_pixel_put.c \
		render.c

%.o: %.c
	$(CC) -I/usr/include -g -Imlx_linux -O3 -c $< -o $@
OBJS = $(SRCS:.c=.o)



CC = cc
#CFLAGS = -Wall -Werror -Wextra
CFLAGS = -g
LIBFLAGS =	-lmlx -lXext -lX11

all: $(NAME)

$(NAME):	$(OBJS)
			cd libft && $(MAKE) && $(MAKE) bonus
			$(CC) $(OBJS) -g libft/libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
		cd libft && $(MAKE) fclean 
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.phony:		clean fclean re all