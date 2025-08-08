CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
FLAGS = ${CFLAGS} ${LFLAGS}
RM = rm -rf

SRCS = 	utils.c\
		parsing/check_errores1.c parsing/env.c parsing/expanding.c parsing/free.c parsing/helper1.c \
		parsing/helper2.c parsing/helper3.c parsing/herdoc.c parsing/lexer.c parsing/libft1.c \
		parsing/libft2.c parsing/libft3.c parsing/libft4.c parsing/libft5.c parsing/linkedlist1.c parsing/main.c \
		parsing/merging.c parsing/temp.c parsing/checking.c parsing/fixing_tokens.c \
		executor/built_in_cmd.c executor/cd.c executor/env2.c executor/execute2.c executor/execute3.c executor/execute.c\
		executor/export.c executor/export_help.c executor/redirections.c executor/signals.c executor/unset.c

OBJS = ${SRCS:.c=.o}

NAME =minishell

all: ${NAME}
.c.o:
	${CC} ${FLAGS} -g -c $< -o $@

${NAME}: ${OBJS}
	$(CC) $(OBJS) $(FLAGS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean re clean
