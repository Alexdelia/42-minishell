NAME = minishell

MAIN = ./srcs/minishell.c

OBJ_MAIN = ${MAIN:.c=.o}
LOCA_OBJ_MAIN = $(addprefix ${PATH_OBJS}, $(notdir ${OBJ_MAIN}))

SRCS = ft_prompt.c ft_word_split.c ft_exec_call.c ft_redirection.c ft_lst_search.c \
		command/ft_echo.c command/ft_cd.c command/ft_pwd.c command/ft_env.c \
		utils/env_utils.c utils/env_utils2.c utils/hist_utils.c utils/hist_utils2.c utils/ft_word_utils.c

PATH_SRCS = ./srcs/

PATH_OBJS = ./objs/

_SRCS = ${addprefix ${PATH_SRCS}, ${SRCS}}

OBJS = ${_SRCS:.c=.o}
LOCA_OBJS = $(addprefix ${PATH_OBJS}, $(notdir ${OBJS}))

LINK = ar rc

CC = clang

FLAGS = -Wall -Wextra -Werror

MAKEFLAGS += --silent

RM = rm -rf

PATH_HEADER = ./includes/

%.o: %.c
		${CC} ${FLAGS} ${BUFFER} -I${PATH_HEADER} -c $< -o $(PATH_OBJS)$(notdir $@)

MYLIB = mylib.a

PATH_LIBFT = ./libft/

LIBFT = libft.a

all:			${NAME}

${NAME}:		objs_dir ${OBJS} ${OBJ_MAIN}
				${LINK} ${MYLIB} ${LOCA_OBJS}
				ranlib ${MYLIB}
				make -C ${PATH_LIBFT}
				${CC} ${FLAGS} ${LOCA_OBJ_MAIN} ${MYLIB} ${PATH_LIBFT}${LIBFT} -lncurses -o ${NAME}
				@echo "$(shell tput bold)\t${NAME} compiled$(shell tput sgr0)"

objs_dir:
				mkdir ${PATH_OBJS} 2> /dev/null || true

clean:
				${RM} ${OBJ_MAIN} ${OBJS}
				make clean -C ${PATH_LIBFT}
				@echo "$(shell tput bold)Cleared$(shell tput sgr0)"

fclean:			clean
				${RM} ${PATH_OBJS}
				${RM} ${NAME} ${MYLIB}
				make fclean -C ${PATH_LIBFT}
				rm -rf *.dSYM

re:				fclean all

.PHONY:			all clean fclean re
