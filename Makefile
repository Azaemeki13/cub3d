# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 12:12:31 by chsauvag          #+#    #+#              #
#    Updated: 2025/08/04 13:00:18 by chsauvag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror  -g
LIBFT   = libft/libft.a
RM      = rm -f

SRCS =	src/main.c \
		src/window_management.c \
		src/error_management.c \

INCLUDE = -I include -I minilibx-linux
MLX_LIB = -L ./minilibx-linux -lmlx -lXext -lX11

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean:	clean
	$(RM) $(NAME)
	make fclean -C libft

re:	fclean $(NAME)

.PHONY:	all clean fclean re