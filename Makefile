NAME = cub3D

SRCS = main.c

OBJS = $(SRCS:.c=.o)

CC = cc
#FLAGS = -Wall -Werror -Wextra
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