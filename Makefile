CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RM = rm -rf

SRCS = check_errores1.c free.c helper2.c libft1.c libft3.c linkedlist1.c temp.c expanding.c executor/export_help.c\
helper1.c lexer.c libft2.c libft4.c main.c env.c helper3.c merging.c utils.c executor/built_in_cmd.c executor/export.c executor/env2.c\
executor/cd.c executor/unset.c  executor/execute.c executor/execute3.c executor/execute2.c executor/redirections.c  executor/signals.c \
executor/herdoc.c \

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
