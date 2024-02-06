NAME = cube3d

SRCS =	get_next_line_utils.c \
		get_next_line.c \
		parsing.c \
		get_textures.c \
		make_file_array.c \
		utils.c \

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