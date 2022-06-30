NAME = mini

FLAGS = -Wall -Werror -Wextra -lreadline

ADDI_FLAGS = -fsanitize=address

COMILING = gcc

F_REMOVE = rm -rf

FUNCTIONS = Libft/ft_split.c\
			Libft/ft_substr.c\
			Libft/ft_strlen.c\
			Libft/ft_strstr.c\
			Libft/ft_strjoin.c\
			get_env_variables.c\
			input_formating.c\
			pipes.c\

OBJECTS = $(FUNCTIONS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
			$(COMILING) -lreadline $(OBJECTS) main.c -o $(NAME)

clean   :
			$(F_REMOVE) $(OBJECTS)
			
fclean  :	clean
			$(F_REMOVE) $(OBJECTS) $(NAME)

re      :	fclean all