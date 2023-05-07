NAME	=	minishell

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=	-L $(shell brew --prefix readline)/lib -lreadline

INCLUDE	=	./include

BUILT_SRC = cd.c cd_utils.c cd_utils2.c echo.c env.c exit.c export_add.c export_utils.c export.c pwd.c unset.c
BUILT = $(addprefix builtin/, $(BUILT_SRC))

MAIN_SRC = main.c
MAIN = $(addprefix main/, $(MAIN_SRC))

EXEC_SRC = exec_cmd_utils.c exec_cmd.c exec_fd_set.c exec_heardocu.c exec_check_builtin.c\
			make_path_absolut.c make_path.c file_init.c
EXEC = $(addprefix exec/, $(EXEC_SRC))

EXPANSION_SRC = expansion_heredoc.c expansion.c expansion_utils.c
EXPANSION = $(addprefix expansion/, $(EXPANSION_SRC))

INIT_AND_UTILS_SRC = free.c init.c make_env.c utils.c
INIT_AND_UTILS = $(addprefix init_and_utils/, $(INIT_AND_UTILS_SRC))

SIGNAL_SRC = signal.c signal_cmd.c
SIGNAL = $(addprefix signal/, $(SIGNAL_SRC))

TOKENIZE_SRC = tokenize.c tokenize_utils.c
TOKENIZE = $(addprefix tokenize/, $(TOKENIZE_SRC))

SRCS = $(MAIN) $(BUILT) $(EXEC) $(EXPANSION) $(INIT_AND_UTILS) $(SIGNAL) $(TOKENIZE)

SRCS_DIR	=	src/
OBJ_DIR	=	obj/

# OBJS = $(patsubst $(SRCS), $(OBJ_DIR), $(SRCS:.c=.o))
OBJ_NAME	=	$(SRCS:.c=.o)
OBJS		=	$(addprefix obj/, $(OBJ_NAME))


LIBFT_DIR	= ./libft
LIBFT	=	$(LIBFT_DIR)/libft.a

RM	=	rm -rf


.PHONY:	all clean fclean re

all: $(NAME)
	$(shell echo > ~/.inputrc set echo-control-characters off)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(OBJS) $(LIBFT) $(LFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(shell brew --prefix readline)/include -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
