NAME = libftprintf.a
CC = gcc
SRCS = ft_printf.c ft_printf_utils.c ft_printf_int.c ft_printf_unsigned_int.c \
 ft_printf_char.c ft_convert_base.c ft_prep_tags.c ft_flag.c
BONUS_SRCS = ft_printf_bonus.c ft_printf_utils_bonus.c ft_printf_int_bonus.c \
 ft_printf_unsigned_int_bonus.c ft_printf_char_bonus.c ft_convert_base_bonus.c \
 ft_prep_tags_bonus.c ft_flag_bonus.c
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

LIBFT_DIR = libft/
LIBFT_LIB = libft.a

CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = -crs

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT_LIB) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

out :
	$(CC) $(CFLAGS) $(SRCS) -o a.out -L. -lftprintf

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): ft_printf.h

clean:
	cd $(LIBFT_DIR) && make clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT_DIR)$(LIBFT_LIB)

re: fclean all

bonus: $(BONUS_OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT_LIB) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS)

$(BONUS_OBJS): ft_printf_bonus.h

.PHONY: all out clean fclean re bonus
