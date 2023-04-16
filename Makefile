NAME	=	minishell

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=	-L $(shell brew --prefix readline)/lib -lreadline

SRCS	=	main.c\
			init.c\
			exec_cmd.c\
			make_path.c\
			pipe_file_init.c\
			tokenize.c\
			tokenize_utils.c\
			error_free.c\
			make_env.c\
			expansion.c\
			expantion_utils.c\
			pwd.c\
			echo.c\
			export.c\
			export_add.c\
			export_utils.c\
			env.c\
			exec_utils.c\
			cd.c\
			exit.c\
			unset.c\
			exec_pipe.c\
			exec_heardocu.c\
			signal.c\
			signal_cmd.c\
			utils.c\
			expansion_heredoc.c\

HEAD_FILE	=	minishell.h

LIBFT_DIR	=	libft
LIBFT	=	$(LIBFT_DIR)/libft.a

RM	=	rm -rf

OBJ_DIR	=	obj

OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

.PHONY:	all clean fclean re

all: $(NAME)
	$(shell echo > ~/.inputrc set echo-control-characters off)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c $(HEAD_FILE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(shell brew --prefix readline)/include

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
