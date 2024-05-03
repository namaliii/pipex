NAME	:= 	pipex

CC		:= 	cc
CFLAGS	:= 	-Wall -Wextra -Werror -g
SRC		:= 	error_handling.c ft_calloc.c ft_split.c \
			utils.c path_utils.c pipex.c

SRC_BNS	:= 	bonus/error_handling_bonus.c bonus/libft2_bonus.c bonus/ft_split_bonus.c \
			bonus/libft_bonus.c bonus/path_utils_bonus.c bonus/pipex_bonus.c \
			bonus/gnl_bonus.c bonus/here_doc_bonus.c bonus/exec_utils_bonus.c

OBJ		:= $(SRC:.c=.o)
OBJ_BNS	:= $(SRC_BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $@

bonus: $(OBJ_BNS)
		@$(CC) $(CFLAGS) $(OBJ_BNS) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BNS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

t: $(NAME)
	./$(NAME) file1 "ls" "wc -l" file2

tb: bonus
	./$(NAME) here_doc . "cat" "grep make" "wc -l" file2

.PHONY: all clean fclean norm re