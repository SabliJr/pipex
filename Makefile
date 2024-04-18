NAME = pipex

RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
EOC:="\033[0;0m"
YELLOW:="\033[1;33m"

GNL_FILES = ./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c 

PIPEX_FILES = ./src/pipex.c\
			./src/pipex_utils.c \
			./src/ft_split.c \
			./src/general_utils.c \

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3

OBJS = ${PIPEX_FILES:.c=.o} ${GNL_FILES:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	${CC} ${CFLAGS} ${OBJS} -o $(NAME)
	echo $(GREEN) "[OK COMPILED]" $(EOC)

all: $(NAME)

clean:
	rm -f $(OBJS)
	echo $(PURPLE) "[🧹Cleaning Objs...🧹]" $(EOC)

fclean:
	rm -f $(NAME)
	echo $(YELLOW) "[🧹Cleaning Names...🧹]" $(EOC)

re: fclean all
.PHONY: all clean fclean re
