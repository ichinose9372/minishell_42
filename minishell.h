#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

extern char	**environ;
# define READ	0
# define WRITE	1
# define PATH_SIZE	512


typedef enum e_token_kind
{
	WORD,
	PIPE,
	OUTPUT,
	INPUT,
	ADD,
	HEREDOC,
}	t_token_kind;

typedef struct s_token
{
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

//double pointer
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

extern t_env	**env;

// env
t_env	*new_env(char *str);
t_env	*make_env(void);

// tokenize
t_token	*tokenizer(char *str, t_token *tok);
int		space_check(char *str, int start);
int		operater_check(char *str, int *start, int *end, t_token **tok);
int		seartch_quote(char *str, int start, int *end);
void	make_token(t_token **tok, char *str, int start, int end);
char	*new_strdup(const char *s1, int size);
t_token	*new_token(char *str, int start, int end);
int		operater_comp(char *str, int end);

// expantion
void	expansion(t_token *tok, t_token **p_tok);

// exec
char	**envp_make_path(char **envp);
char	*make_path(char *split_arg, char **envp);
char	**envp_make_path(char **envp);
char	*serch_path(char	*tmp, char **env_split);
char	*make_path(char *split_arg, char **envp);
char	**token_path(t_token **p_tok);
int		check_no_operation(t_token **p_tok);
void	do_cmd(t_token **p_tok, int input_fd, int output_fd);

// file oparate
int		file_open_wrt(char *argv);
int		file_open_rd(char	*argv);
int		file_open_wrt_add(char *argv);

// free
void	all_free(char **env_split);
void	all_free_token(t_token **p_tok);
void	all_free_and_tmp(char *tmp, char **env_split);
void	command_not_found(char *str);

// テスト用
void	print_token(t_token **tok);

// builtin
bool	builtin_pwd(t_token **p_tok);
#endif
