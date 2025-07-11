# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 15:20:47 by lsadi             #+#    #+#              #
#    Updated: 2024/11/18 01:36:58 by lsadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_str_len.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_str_chr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_strnstr.c ft_atoi.c \
      ft_itoa.c ft_substr.c ft_str_join.c ft_strtrim.c ft_strdup.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c free_split.c \
      ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_memcmp.c ft_calloc.c ft_strjoin_three.c



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
