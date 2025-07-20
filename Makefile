CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RM = rm -rf

SRCS = check_errores1.c free.c helper2.c libft1.c libft3.c linkedlist1.c temp.c expanding.c\
helper1.c lexer.c libft2.c libft4.c main.c env.c helper3.c merging.c utils.c built_in_cmd.c export.c env2.c cd.c unset.c\
execute.c redirections.c utils_exec.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

all: ${NAME}

#?
.c.o:
	${CC} ${CFLAGS} -g -c $< -o $@

${NAME}: ${OBJS}
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	${RM} ${OBJS} ${O_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean re bonus clean
