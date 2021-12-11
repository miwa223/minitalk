NAME = minitalk
CLIENT_NAME = client
SERVER_NAME = server

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

CLIENT_OBJS = $(CLIENT_SRCS:%.c=%.o)
SERVER_OBJS = $(SERVER_SRCS:%.c=%.o)

FT_PRINTF_DIR = ft_printf/
FT_PRINTF_LIB = libftprintf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

all: $(NAME)


$(NAME):
	make -C $(FT_PRINTF_DIR)
	make $(CLIENT_NAME)
	make $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) minitalk.h client.h
	$(CC) $(CFLAGS) -o $@ $< -L. $(FT_PRINTF_DIR)$(FT_PRINTF_LIB)

$(SERVER_NAME): $(SERVER_OBJS) minitalk.h
	$(CC) $(CFLAGS) -o $@ $< -L. $(FT_PRINTF_DIR)$(FT_PRINTF_LIB)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	cd $(FT_PRINTF_DIR) && make clean
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
fclean: clean
	cd $(FT_PRINTF_DIR) && make fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

bonus: $(NAME)
re: fclean all
.PHONY: all clean fclean re bonus
