# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adelille <adelille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 19:21:49 by adelille          #+#    #+#              #
#    Updated: 2021/03/30 12:03:22 by adelille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	minishell
CC = 	clang -Wall -Werror -Wextra
RM = 	rm -rf
# FLAGS =	-O2

# **************************************************************************** #

MAKEFLAGS += --silent

B =		$(shell tput bold)
BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)
D =		$(shell tput sgr0)
BEL =	$(shell tput bel)
CLR =	$(shell tput el 1)

# **************************************************************************** #
#	 LIB	#

LBPATH =	./libft/
LBNAME =	$(LBPATH)libft.a
LBINC =		-I$(LBPATH)

# **************************************************************************** #

SRCSPATH =	./srcs/
#OBJSPATH =	./objs/
INC =		./includes/

SRCSNAME =

#SRCS = $(addprefix $(SRCSPATH), $(SRCSNAME))
#OBJS = $(addprefix $(OBJSPATH), $(OBJSNAME))
OBJS = $(SRCSNAME:.s=.o)

# *************************************************************************** #

%.o:	%.s
	@$(CC) $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
	@make -C $(LBPATH)
	@$(CC) $(OBJS) $(LBNAME) -L$(LBPATH) $(LBINC) -I$(INC) -o $(NAME)
	@echo "\n$(B)$(MAG)$(BEL)minishell\tcompiled !$(D)\n"

libft:
	@make -C $(LBPATH) -f Makefile

clean:
	@$(RM) $(OBJS)
	@echo "$(B)Cleared$(D)"

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re, libft

# **************************************************************************** #
