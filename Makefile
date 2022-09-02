sig = `stty -echoctl`
NAME = Minishell

C_FLAGS = gcc

C_READLINE = -lreadline -L /Users/otoufah/goinfre/homebrew/opt/readline/lib -I /Users/otoufah/goinfre/homebrew/opt/readline/include

F_REMOVE = rm -rf

C_FILES = 	minishell.c \
			Shared/count_pipe_tokens.c \
			Shared/init_funcs.c \
			Shared/print_perror.c \
			Shared/memmory_utils.c \
			Shared/system_calls_protection.c \
			Shared/signals.c \
			Shared/ft_itoa.c \
			Shared/validate_var_name.c \
			Shared/free_funcs.c \
			Shared/env_dup.c \
			Shared/get_var_index.c \
			Shared/ft_putstr_fd.c \
			Shared/ft_atoi.c \
			Shared/ft_strncpy.c \
			Shared/ft_split.c \
			Shared/ft_substr.c \
			Shared/ft_strlen.c \
			Shared/ft_strstr.c \
			Shared/ft_strjoin.c \
			Shared/ft_strcmp.c \
			Shared/ft_strncmp.c \
			Shared/ft_strdup.c \
			Shared/ft_calloc.c \
			Shared/ft_lstclear.c \
			Shared/ft_strchr.c \
			Shared/ft_realloc.c \
			Shared/ft_isalpha.c \
			Shared/ft_isdigit.c \
			Shared/ft_isalnum.c \
			Shared/ft_strnstr.c \
			Shared/get_var_val.c \
			Shared/prevent_tabs.c \
			Parsing/remove_quotes.c \
			Parsing/token_and_type.c \
			Parsing/get_env_in_herdoc.c \
			Parsing/get_env_variables.c \
			Parsing/get_env_utils.c	\
			Parsing/get_env_utils_2.c	\
			Parsing/input_formating.c \
			Parsing/input_formating_utils.c \
			Parsing/input_analyse.c \
			Parsing/fill_tokens.c \
			Parsing/handling_quotes.c \
			Parsing/check_parse_errors.c \
			Builtins/driver.c \
			Builtins/mcd.c \
			Builtins/mecho.c \
			Builtins/menv.c \
			Builtins/mexit.c \
			Builtins/mexport.c \
			Builtins/mexport_utils.c \
			Builtins/mpwd.c \
			Builtins/munset.c \
			Execution/execution.c \
			Execution/command_validation.c \
			Execution/files_redirections.c \
			Execution/exec_utils.c \

all: $(NAME)

$(NAME): $(C_FILES)
		@$(sig)
		@$(C_FLAGS) $(C_FILES) $(C_READLINE) $(ADDI_FLAGS) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

