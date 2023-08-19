# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 14:00:55 by emirzaza          #+#    #+#              #
#    Updated: 2023/08/15 23:24:53 by emirzaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex

FOLDER = src/

SRCS = 			pipex.c \
				pipex_utils.c \
				exec.c \
				file.c \
				parse.c \
				free.c \
				init.c \
				child.c \
				parent.c \
				exit.c \
				special_chr_check.c
SRC_PATHES =	$(addprefix $(FOLDER), $(SRCS))
OBJS =			$(SRC_PATHES:.c=.o)

BSRCS = 		bonus.c \
				pipex_utils.c \
				exec.c \
				file.c \
				parse.c \
				free.c \
				init.c \
				child.c \
				parent.c \
				exit.c \
				special_chr_check.c
BSRC_PATHES =	$(addprefix $(FOLDER), $(BSRCS))
BOBJS =			$(BSRC_PATHES:.c=.o)

CC =			gcc
CFLAGS =	 	-Wall -Wextra -Werror -g

RM = 			rm -rf

$(NAME):		$(OBJS)
				@${MAKE} -C ./libft
				${CC} $(CFLAGS) $(OBJS) ./libft/libft.a -o ${NAME}

all:			$(NAME)

fclean	:		clean
				make fclean -C libft
				$(RM) $(NAME)

clean	:		
				$(RM) $(OBJS)
				$(RM) $(BOBJS)
				make clean -C libft

			
re		:		fclean all

bonus 	:		$(BOBJS)
				@${MAKE} -C ./libft
				@$(CC) $(CFLAGS) $(BOBJS) ./libft/libft.a -o $(NAME)

.PHONY: all clean fclean re
