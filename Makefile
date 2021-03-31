NAME = minishell

MAIN = ./srcs/minishell.c

OBJ_MAIN = ${MAIN:.c=.o}

SRCS = env_utils.c env_utils2.c hist_utils.c hist_utils2.c \
		ft_word_utils.c ft_word_split.c \
		ft_echo.c ft_cd.c ft_pwd.c \
		ft_lst_search.c ft_exec_call.c

PATH_SRCS = ./srcs/

_SRCS = ${addprefix ${PATH_SRCS}, ${SRCS}}

OBJS = ${_SRCS:.c=.o}

LINK = ar rc

CC = clang

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

PATH_HEADER = ./includes/

.c.o:
		${CC} ${FLAGS} ${BUFFER} -I${PATH_HEADER} -c $< -o ${<:.c=.o}

MYLIB = mylib.a

PATH_LIBFT = ./libft/

LIBFT = libft.a

all:			${NAME}

${NAME}:		${OBJ_MAIN} ${OBJS}
				${LINK} ${MYLIB} ${OBJS}
				ranlib ${MYLIB}
				make -C ${PATH_LIBFT}
				${CC} ${FLAGS} ${OBJ_MAIN} ${MYLIB} ${PATH_LIBFT}${LIBFT} -o ${NAME}

clean:
				${RM} ${OBJ_MAIN} ${OBJS}
				make clean -C ${PATH_LIBFT}

fclean:			clean
				${RM} ${NAME} ${MYLIB}
				make fclean -C ${PATH_LIBFT}
				rm -rf *.dSYM

re:				fclean all

.PHONY:			all clean fclean re
