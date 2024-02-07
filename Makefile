NAME = cube3d

SRCS =	parsing.c \
		get_textures.c \
		get_colors.c \
		make_file_array.c \
		utils.c \
		make_map.c

OBJS = $(SRCS:.c=.o)

CC = cc
#CFLAGS = -Wall -Werror -Wextra
CFLAGS = -g
LIBFLAGS =	-lmlx -lXext -lX11

all: $(NAME)

$(NAME):	$(OBJS)
			cd libft && $(MAKE) && $(MAKE) bonus
				$(CC) $(OBJS) $(CFLAGS) $(LIBFLAGS) ./libft/libft.a -o $(NAME)

clean:
		cd libft && $(MAKE) fclean 
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.phony:		clean fclean re all