CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I./includes -Wall -Wextra -Werror
NAME	=	pipex
LIBFT	=	./libft
SRCS	=	pipex.c utils.c

OBJS	=	$(patsubst %.c, %.o, $(SRCS))

all:
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS) $(LIBFT)/libft.a includes/pipex.h libft/libft.h
			@$(CC) -o $(NAME) $(OBJS) $(LIBFT)/libft.a
			@echo "pipex is ready to use ✅ "

%.o: %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(MAKE) -C $(LIBFT)/ clean
			@$(RM)	$(OBJS)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(MAKE) -C $(LIBFT)/ fclean
			@$(RM)	 $(NAME)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re