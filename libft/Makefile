# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svet <svet@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/04 15:46:13 by skrasin           #+#    #+#              #
#    Updated: 2020/05/25 13:04:49 by svet             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/sh

srcdir := ./srcs/
incdir := ./includes/
srcdirs := char mem str io math list
srcdirs_bonus := list_bonus
objects := $(patsubst %.c, %.o, $(foreach dir, $(addprefix $(srcdir), $(srcdirs)), $(wildcard $(dir)/*.c)))
objects_bonus := $(patsubst %.c, %.o, $(wildcard $(addprefix $(srcdir), $(srcdirs_bonus))/*.c))
NAME := libft.a
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I$(incdir)
ARFLAGS := $(ARFLAGS)s

# .PRECIOUS: %.o

all: $(NAME)

$(NAME) : $(NAME)($(objects))

bonus : $(NAME)($(objects_bonus))

clean:
	-$(RM) $(objects) $(objects_bonus)

fclean: clean
	-$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus srcs includes char mem str io math list list_bonus
