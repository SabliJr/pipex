NAME = pipex
BONUS_NAME = pipex_bonus

RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
EOC:="\033[0;0m"
YELLOW:="\033[1;33m"
ORANGE:="\033[0;33m"

GNL_FILES = ./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c 

PIPEX_FILES = ./src/pipex.c\
			./src/pipex_utils.c \
			./src/ft_split.c \
			./src/general_utils.c \
			./src/extra_fts.c

PIPEX_BONUS_FILES = ./Bonus/src/bonus_pipex.c \
					./Bonus/src/bonus_utils.c \
					./Bonus/src/bonus_general.c \
					./Bonus/src/ft_split.c \
					./Bonus/src/put_errs.c \
					./Bonus/src/other_utils.c

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3

OBJS = ${PIPEX_FILES:.c=.o} ${GNL_FILES:.c=.o}
SRCS = ${PIPEX_FILES}
SRCSALL = ${PIPEX_BONUS_FILES} ${PIPEX_FILES}
OBJS_BONUS = ${PIPEX_BONUS_FILES:.c=.o} ${GNL_FILES:.c=.o}


.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	${CC} ${CFLAGS} ${OBJS} -o $(NAME)
	echo $(GREEN) "[OK COMPILED]" $(EOC)

$(BONUS_NAME): ${OBJS_BONUS}
	${CC} ${CFLAGS} ${OBJS_BONUS} -o $(BONUS_NAME)
	echo $(YELLOW) "[OK BOUNS COMPILED]"

bonus: $(BONUS_NAME)

all: $(NAME) $(BONUS_NAME)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	echo $(PURPLE) "[🧹Cleaning Objs...🧹]" $(EOC)

fclean:
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	echo $(ORANGE) "[🧹Cleaning Names...🧹]" $(EOC)

re: fclean all
.PHONY: all clean fclean re
