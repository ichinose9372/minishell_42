NAME	=	minishell

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=	-lreadline

SRCS	=	main.c\
			exec_cmd.c\
			make_path.c\
			pipe_file_init.c\
			tokenize.c\
			tokenize_utils.c\
			error_free.c\
			env.c\
			expansion.c\

HEAD_FILE	=	minishell.h

LIBFT_DIR	=	libft
LIBFT	=	$(LIBFT_DIR)/libft.a

RM	=	rm -rf

OBJS	=	$(SRCS:.c=.o)

.PHONY:	all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $@

$(OBJS) : %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

re:		fclean all

