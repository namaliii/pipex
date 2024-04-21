NAME	:= 	pipex

CC		:= 	CC
CFLAGS	:= 	-Wall -Wextra -Werror -g
SRC		:= 	ft_split.c pipex.c utils.c error_handling.c
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