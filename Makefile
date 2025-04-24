NAME	=	pipex
HEADER	=	pipex.h

SRC_DIR	=	src
UTILS_DIR =	utils

SRC		=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/pipe.c \
			$(SRC_DIR)/free_error.c \
			$(UTILS_DIR)/utils.c \
			$(UTILS_DIR)/ft_split.c

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -O2 -g -fsanitize=address

OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

