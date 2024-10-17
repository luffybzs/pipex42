# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 14:37:00 by ayarab            #+#    #+#              #
#    Updated: 2024/10/15 22:10:54 by ayarab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	pipex.c ft_free.c pipex_error.c ft_exec_cmd.c \
		get_next_line.c get_next_line_utils.c  \
		ft_parsing_pipex.c \
		 
					
LIBFT_DIR       = libft/
LIBFT			= $(LIBFT_DIR)libft.a
OBJS			= $(SRCS:.c=.o)

CC				= cc -g3
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= pipex


all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
clean:
				$(RM) $(OBJS)
				make clean -sC $(LIBFT_DIR)

fclean:			clean
				$(RM) $(NAME)
				make fclean -sC $(LIBFT_DIR)

re:				fclean $(NAME)

$(LIBFT): 			
				make -sC $(LIBFT_DIR)

%.o : %c
				$(CC) $(CFLAGS) -c $< -o $@
				
  
.PHONY:			all clean fclean re bonus