NAME = cube3d

SRCS = main.c

OBJS = $(SRCS:.c=.o)

CC = cc
#FLAGS = -Wall -Werror -Wextra
LIBFLAGS =	-lmlx -lXext -lX11

all: $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(OBJS) $(CFLAGS) $(LIBFLAGS)  -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.phony:		clean fclean re all