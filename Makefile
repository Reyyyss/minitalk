NAME1 = server.a
NAME2 = client.a

SOURCES = ft_printf.c ft_prtptr.c ft_putchar.c ft_putnbr_base.c \
			ft_putstr.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) 
$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:

	rm -f $(OBJECTS)

fclean: clean

	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
