NAME = Minishell

CFLAGS = gcc -Wall -Werror -Wextra -lreadline

ADDI_FLAGS = -fsanitize=address

F_REMOVE = rm -rf

CFILE = minishell.c \
		utils/ft_putstr_fd.c \
		utils/ft_split.c \
		utils/ft_substr.c \
		utils/ft_strlen.c \
		utils/ft_strstr.c \
		utils/ft_strjoin.c \
		utils/ft_strcmp.c \
		utils/ft_strdup.c \
		utils/ft_calloc.c \
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
		$(CFLAGS) $(CFILE) $(ADDI_FLAGS) -o $(NAME) 

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re