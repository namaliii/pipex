NAME	:= 	pipex

CC		:= 	CC
CFLAGS	:= 	-Wall -Wextra -Werror
SRC		:= 	ft_split.c pipex.c utils.c
OBJ		:= 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

t:
	./$(NAME) file1 "ls" "wc" file2

.PHONY: all clean fclean norm re 