#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/stat.h>

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
	char			*old_word;
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

typedef struct s_pipe
{
	int	pipe_fd[2];
	int	flag;
}	t_pipe;

typedef struct s_global
{
	t_env	**env;
	int		status;
	int		heredoc_flag;
	int		fd_in;
	int		fd_out;
}	t_global;

extern t_global g_global;
//init
void	init_minishell(void);
int		minishell_2(t_token **p_tok, char *str);
void	minishell(void);

// env
t_env	*new_env(char *str);
t_env	**make_env(void);
char	**convet_environ(void);
// tokenize
t_token	*tokenizer(char *str, t_token *tok);
int		space_check(char *str, int start);
int		operater_check(char *str, int *start, int *end, t_token **tok);
int		seartch_quote(char *str, int start, int *end, t_token *tmp);
void	make_token(t_token **tok, char *str, int start, int end);
char	*new_strdup(const char *s1, int size);
t_token	*new_token(char *str, int start, int end);
int		operater_cmp(char *str, int end);
void	token_kind(t_token *tok);
int		ispace_check(char *str, int start);
	// expantion
void	expansion(t_token *tok, t_token **p_tok);
size_t	char_expansion(char **dest, char *src);
size_t	variable_expansion(char **dest, char *src);
bool	check_variable(char *src, size_t *cnt);
char	*new_getenv(char *name);
// exec
char	**envp_make_path(void);
char	*make_path(char *argv);
char	*serch_path(char	*tmp, char **env_split);
char	**token_path(t_token **p_tok);
char	*create_absolute_path(char	*argv);
int		check_operation(t_token **p_tok);
int		set_input(t_token **p_tok);
int		set_output(t_token **p_tok);
int		set_add(t_token **p_tok);
void	set_fd(t_token **p_tok, int *in, int *out);
int		check_operation(t_token **p_tok);
bool	pipe_check(t_token **p_tok, t_pipe *pipe_data);
int		count(t_token *p_tok);
void	exec_cmd(t_token **p_tok, int input_fd, int output_fd);
void	exec_pipe(t_token **p_tok, int input_fd, int output_fd);
void	exec(char	**path);
void	chiled1(t_token **p_tok, t_pipe *pipe_data, int input_fd);
void	chiled2(t_token **p_tok, t_pipe *pipe_data, int output_fd);
void	exec_no_oparat(t_token **p_tok, int input_fd, int output_fd);
void	exec_redirect_out(t_token **p_tok, int input_fd);
void	exec_redirect_inp(t_token **p_tok);
void	exec_heardocu(t_token **p_tok);
void	exec_colon(t_token **p_tok);
int		heredoc_cmd(t_token *p_tok);
int		builtin_check(char **args);
void	exe_parent(char	**args, t_token **p_tok, int input_fd);
char	**in_exec_path(char **args);
void	swich_fd_check_builtin(int input_fd, int output_fd, char **args);
void	init_pipe_setfd(int *output_fd, t_pipe *pipe_data);
void	close_pipe(t_pipe *pipe_data);
void	heredoc_stop(char **args);
	// heredoc
void	expansion_heredoc(char **str);
// file oparate
int		file_open_wrt(char *argv);
int		file_open_rd(char	*argv);
int		file_open_wrt_add(char *argv);
int		ft_open(t_token **p_tok);
	// free
void	all_free(char **env_split);
void	all_free_token(t_token **p_tok);
void	free_token(t_token *tok);
void	all_free_and_tmp(char *tmp, char **env_split);
void	command_not_found(char *str);
void	path_all_free(char **env_split);
// テスト用
void	print_token(t_token **p_tok);
// builtin
int		builtin_pwd(char **args);
int		builtin_echo(char **args);
//cd
int		builtin_cd(char **args);
char	*home_path(void);
void	remake_pwd(char *new_path);
int		serch_home(void);
char	*my_getcwd(char *buf, size_t length);
char	*make_next_path(char *path_name, char *word);
char	*my_getcwd(char *buf, size_t length);
void	remake_pwd(char	*new_path);
char	*prev_move(char	*path_name);
int		builtin_export(char **args);
void	add_env(char *str);
int		export_elem_error(char *str);
int		builtin_env(char **args);
int		builtin_list(char **args);
int		builtin_exit(char **args);
int		builtin_unset(char **args);
// signal
void	signal_one(void);
void	signal_heredocu(void);
void	signal_cmd(void);
// utils
void	*malloc_error(size_t size);
char	*new_strjoin(char const *s1, char const *s2, size_t s2_len);
int		ft_strcmp(char *s1, char *s2);
#endif
