NAME	:= 	pipex

CC		:= 	cc
CFLAGS	:= 	-Wall -Wextra -Werror -g
SRC		:= 	error_handling.c ft_calloc.c ft_split.c \
			utils.c path_utils.c pipex.c
OBJ		:= 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

t: $(NAME)
	./$(NAME) file1 "ls" "wc -l" file2

.PHONY: all clean fclean norm re