CC = cc -g
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RM = rm -rf

SRCS = 	parsing/check_errores1.c parsing/env.c parsing/expanding.c parsing/free.c parsing/helper1.c \
		parsing/helper2.c parsing/helper3.c  parsing/lexer.c parsing/libft1.c  \
		parsing/libft2.c parsing/libft3.c parsing/libft4.c parsing/libft5.c parsing/linkedlist1.c \
		parsing/merging.c  parsing/temp.c parsing/checking.c parsing/fixing_tokens.c \
		executor/built_in_cmd.c executor/cd.c executor/env2.c executor/execute2.c executor/execute3.c executor/execute.c\
		executor/export.c executor/export_help.c executor/redirections.c executor/signals.c executor/unset.c  executor/split.c \
		executor/utils1.c executor/utils2.c executor/herdoc.c\
		garbage_collector.c main.c\
		 
OBJS = ${SRCS:.c=.o}

NAME =minishell

all: ${NAME}
#?
.c.o:
	${CC} ${CFparsing/LAGS} -g -c $< -o $@

${NAME}: ${OBJS}
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	${RM} ${OBJS} ${O_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean re bonus clean
