NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address
LIBFT = ./libft/libft.a
LIB = pipex.h
#LIB_BONUS = 
#SRC_PATH = ./src/
#SRC_PATH_BONUS = ./src_bonus/

SRCS =	main.c\
		path.c

#SRC_BONUS =	

#SRCS = $(addprefix $(SRC_PATH), $(SRC))
#SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS))

OBJS = $(SRCS:.c=.o)
#OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: make_libft $(NAME)

#bonus: make_libft $(NAME_BONUS)

make_libft:
	@make all -C ./libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(LIB) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -C ./libft

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus