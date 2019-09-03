CC			= gcc
RM			= rm -f
NAME		= wolf3d
DEBUG		= -g -fsanitize=address -fsanitize=undefined
CFLAGS		= -Wall -Wextra -Werror $(DEBUG)
LIBFT 		= libft/libft.a
MINILIBX	= minilibx/libmlx.a
INCLUDES	= -I includes \
			  -I libft/includes \
			  -I minilibx/

LIB			= -L libft/ -lft \
			  -L minilibx/ -lmlx -framework OpenGL -framework AppKit

MAIN		= main.c game.c put.c key.c
UTILITIES	= parser.c set.c free.c

FUNCTIONS	= $(addprefix srcs/, $(MAIN) $(UTILITIES))
OBJECTS		= $(FUNCTIONS:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

$(MINILIBX):
	@make -C minilibx

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB)

clean:
	@make clean -C libft
	@make clean -C minilibx
	@$(RM) $(OBJECTS)

fclean: clean
	@make fclean -C libft
	@make fclean -C minilibx
	@$(RM) $(NAME)

re: fclean all

# EOF #
