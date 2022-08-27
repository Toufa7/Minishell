NAME = Minishell

C_FLAGS = gcc

READLINE = -lreadline -L /Users/abouchfa/brew/opt/readline/lib -I /Users/abouchfa/brew/opt/readline/include

ADDI_FLAGS = -fsanitize=address -g

F_REMOVE = rm -rf

C_FILES = 	minishell.c \
			Utils/system_calls_protection.c \
			Utils/signals.c \
			Utils/ft_itoa.c \
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
			Utils/gnl.c \
			Utils/ft_strnstr.c \
			Utils/get_var_val.c \
			Parsing/s_d_quotes.c \
			Parsing/get_env_in_herdoc.c \
			Parsing/get_env_variables.c \
			Parsing/input_formating.c \
			Parsing/spliting_with_spaces.c \
			Parsing/input_analyse.c \
			Parsing/input_counter.c \
			Parsing/get_pipe_data.c \
			Parsing/handling_quotes.c \
			Parsing/token_and_type.c \
			Parsing/check_parse_errors.c \
			Builtins/driver.c \
			Builtins/mcd.c \
			Builtins/mecho.c \
			Builtins/menv.c \
			Builtins/mexit.c \
			Builtins/mexport.c \
			Builtins/mpwd.c \
			Builtins/munset.c \
			Execution/execution.c \
			Execution/command_validation.c \
			Execution/files_preps.c \

all: $(NAME)

$(NAME): $(C_FILES)
		$(C_FLAGS) $(ADDI_FLAGS) $(READLINE) $(C_FILES) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
