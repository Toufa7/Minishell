NAME = Minishell

CFLAGS = gcc -Wall -Werror -Wextra -lreadline

ADDI_FLAGS = -fsanitize=address

F_REMOVE = rm -rf

CFILE = minishell.c \
		Utils/env_dup.c \
		Utils/ft_putstr_fd.c \
		Utils/ft_split.c \
		Utils/ft_substr.c \
		Utils/ft_strlen.c \
		Utils/ft_strstr.c \
		Utils/ft_strjoin.c \
		Utils/ft_strcmp.c \
		Utils/ft_strdup.c \
		Utils/ft_calloc.c \
		Parsing/get_env_variables.c \
		Parsing/input_formating.c \
		Parsing/spliting_with_spaces.c \
		Parsing/input_analyse.c \
		Parsing/input_counter.c \
		Parsing/input_types.c \
		Execution/Builtins/cd.c \
		Execution/Builtins/echo.c \
		Execution/Builtins/env.c \
		Execution/Builtins/exit.c \
		Execution/Builtins/export.c \
		Execution/Builtins/pwd.c \
		Execution/Builtins/unset.c \

all: $(NAME)

$(NAME): $(CFILE)
		$(CFLAGS) $(CFILE) -o $(NAME) 

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
