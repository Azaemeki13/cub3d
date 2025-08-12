# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 12:12:31 by chsauvag          #+#    #+#              #
#    Updated: 2025/08/12 09:51:44 by cauffret         ###   ########.fr        #
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
       src/initialisation_map.c \
       src/initialisation_utils.c \
       src/initialisation_utils2.c \
       src/initialisation_utils3.c \
       src/initialisation_utils4.c \
       src/initialisation.c \
       src/memory.c \
       src/miscs.c \
       src/parser.c \
       src/raycasting_engine.c \
       src/raycasting_engine_utils.c \
       src/rendering.c \
       src/color.c \
       src/key_hook_moves.c

INCLUDE = -I include -I minilibx-linux
MLX_LIB = -L ./minilibx-linux -lmlx -lXext -lX11
MATH_LIB = -lm

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(MATH_LIB) -o $(NAME)

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