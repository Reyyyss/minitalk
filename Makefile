NAME1 = server.a
NAME2 = client.a

SOURCES_SERVER = server.c utils.c
SOURCES_CLIENT = client.c utils.c

CLIENT_OBJ = $(SOURCES_CLIENT:.c=.o)
SERVER_OBJ = $(SOURCES_SERVER:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME1) $(NAME2)

$(NAME1): $(SERVER_OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) 

clean:

	rm -f $(OBJECTS)

fclean: clean

	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
