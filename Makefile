NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address
LIBFT = ./libft/libft.a
LIB = src/pipex.h
LIB_BONUS = src/pipe_bonus.h
SRC_PATH = ./src/
SRC_PATH_BONUS = ./src_bonus/

SRC =	main.c\
		path.c\
		utils.c

SRC_BONUS =	main_bonus.c\
			path_bonus.c\
			utils_bonus.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: make_libft $(NAME)

bonus: make_libft $(NAME_BONUS)

make_libft:
	@make all -C ./libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -I $(LIB) $(LIBFT) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -I $(LIB_BONUS) $(LIBFT) -o $(NAME_BONUS)


clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C ./libft
	@rm -rf $(OBJS_PATH)


fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -C ./libft
	@rm -rf $(OBJS_PATH)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus
