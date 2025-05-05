NAME1 = server
NAME2 = client

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./libft -lft

SOURCES_SERVER = server.c utils.c
SOURCES_CLIENT = client.c utils.c

CLIENT_OBJ = $(SOURCES_CLIENT:.c=.o)
SERVER_OBJ = $(SOURCES_SERVER:.c=.o)


all: $(NAME1) $(NAME2)

server.o: server.c
	$(CC) $(CFLAGS) -c $< -o $@

client.o: client.c
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME1): $(SERVER_OBJ) | libft
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $@ $(LDFLAGS)

$(NAME2): $(CLIENT_OBJ) | libft
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $@ $(LDFLAGS)

libft :
	$(MAKE) -C ./libft

clean:
	make clean -C ./libft -s
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	make fclean -C ./libft -s
	rm -f $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
