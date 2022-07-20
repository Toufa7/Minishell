NAME		= Minishell

FLAGS		= -Wall -Werror -Wextra -lreadline

ADDI_FLAGS	= -fsanitize=address

COMPILING	= gcc

F_REMOVE	= rm -rf

FUNCTIONS	=	Libft/ft_split.c\
				Libft/ft_substr.c\
				Libft/ft_strlen.c\
				Libft/ft_strstr.c\
				Libft/ft_strjoin.c\
				Libft/ft_strcmp.c\
				Libft/ft_strdup.c\
				Libft/ft_calloc.c\
				get_env_variables.c\
				input_formating.c\
				spliting_with_spaces.c\
				input_analyse.c\
				input_counter.c\
				input_types.c\

OBJECTS 	= $(FUNCTIONS:.c=.o)


all 	: $(NAME)

$(NAME) : $(OBJECTS)
		$(COMPILING) $(ADDI_FLAGS) $(FLAGS) $(OBJECTS) main.c -o $(NAME) 

clean   :
		$(F_REMOVE) $(OBJECTS)
			
fclean  : clean
		$(F_REMOVE) $(OBJECTS) $(NAME)

re      : fclean all

.PHONY 	: all clean fclean re