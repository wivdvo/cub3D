#include "libft/libft.h"

int main()
{
	char *line;
	ft_printf("hello i am filip \n");
	line = get_next_line(0);
	ft_printf("%s", line);
	free(line);
	return(0);
}