NAME = mini

FLAGS = -Wall -Werror -Wextra -lreadline

ADDI_FLAGS = -fsanitize=address

COMILING = gcc

F_REMOVE = rm -rf

FUNCTIONS = ft_split.c\
			ft_substr.c\
			ft_strlen.c\
			ft_strstr.c\

OBJECTS = $(FUNCTIONS:.c=.o)

all = $(NAME)

$(NAME) : $(OBJECTS)
			$(COMILING) $(FLAGS) $(OBJECTS) main.c -o $(NAME)

clean   :
			$(F_REMOVE) $(OBJECTS)
			
fclean  :	clean
			$(F_REMOVE) $(OBJECTS) $(NAME)

re      :	fclean all