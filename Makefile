NAME = Minishell

C_FLAGS = gcc -Wall -Werror -Wextra -lreadline

ADDI_FLAGS = -fsanitize=address -g

F_REMOVE = rm -rf

C_FILES = 	minishell.c \
			Utils/validate_var_name.c \
			Utils/free_funcs.c \
			Utils/env_dup.c \
			Utils/get_var_index.c \
			Utils/ft_putstr_fd.c \
			Utils/ft_atoi.c \
			Utils/ft_strncpy.c \
			Utils/ft_split.c \
			Utils/ft_substr.c \
			Utils/ft_strlen.c \
			Utils/ft_strstr.c \
			Utils/ft_strjoin.c \
			Utils/ft_strcmp.c \
			Utils/ft_strncmp.c \
			Utils/ft_strdup.c \
			Utils/ft_calloc.c \
			Utils/ft_strchr.c \
			Utils/ft_realloc.c \
			Utils/ft_isalpha.c \
			Utils/ft_isdigit.c \
			Parsing/get_env_variables.c \
			Parsing/input_formating.c \
			Parsing/spliting_with_spaces.c \
			Parsing/input_analyse.c \
			Parsing/input_counter.c \
			Parsing/input_types.c \
			Parsing/handling_quotes.c \
			Execution/Builtins/mcd.c \
			Execution/Builtins/mecho.c \
			Execution/Builtins/menv.c \
			Execution/Builtins/mexit.c \
			Execution/Builtins/mexport.c \
			Execution/Builtins/mpwd.c \
			Execution/Builtins/munset.c \

all: $(NAME)

$(NAME): $(C_FILES)
		$(C_FLAGS) $(ADDI_FLAGS) $(C_FILES) -o $(NAME) 

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re