NAME = minishell

MAIN = ./srcs/minishell.c

OBJ_MAIN = ${MAIN:.c=.o}
LOCA_OBJ_MAIN = $(addprefix ${PATH_OBJS}, $(notdir ${OBJ_MAIN}))

SRCS = utils/prompt_utils.c engine/ft_word_split.c engine/ft_exec_call.c engine/ft_redirection.c \
		command/ft_echo.c command/ft_cd.c command/ft_pwd.c command/ft_env.c command/ft_export.c command/ft_export2.c command/ft_unset.c command/ft_exec.c \
		utils/env_utils.c utils/env_utils2.c utils/env_utils3.c utils/env_utils4.c utils/hist_utils.c utils/hist_utils2.c utils/word_utils.c \
		utils/word_utils2.c engine/process_input.c engine/process_input2.c utils/ft_strcat.c utils/ft_parse_transform.c \
		utils/ft_error.c utils/ft_statable.c utils/ft_len_post_transform.c

PATH_SRCS = ./srcs/

PATH_OBJS = ./objs/

_SRCS = ${addprefix ${PATH_SRCS}, ${SRCS}}

OBJS = ${_SRCS:.c=.o}
LOCA_OBJS = $(addprefix ${PATH_OBJS}, $(notdir ${OBJS}))

LINK = ar rc

CC = clang

FLAGS = -Wall -Wextra -Werror

# FLAGS += -g -fsanitize=address

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
				@echo "$(shell tput bold)${NAME} compiled$(shell tput sgr0)"

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
