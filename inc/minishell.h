/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:49:09 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 03:05:28 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//para mi
# ifdef __linux__
#  define _GNU_SOURCE
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft/libft.h"

# ifndef __linux__

int	g_exit_status;

# endif

// error code
# define ERR_AC "only provide ./minishell\n"
# define ERR_MALLOC "memory allocation error\n"
# define ERR_QUOTE "quote>\n"
# define ERR_PIPE "pipe command error\n"
# define ERR_SYNTAX "syntax error near unexpected token\n"
# define ERR_SIG "signal catching error\n"
# define ERR_FILE_NO_EXIST "No such file or directory\n"
# define ERR_NO_CMD "command not found\n"
# define ERR_FORK "forking error\n"
# define ERR_BUILTIN_HAS_ARGS "invalid option\n"

// type code
# define TYPE_STR 0// "hola que tal"
# define TYPE_CMD 1// ls
# define TYPE_HDC 2// <<
# define TYPE_APND 3// >>
//output redirection: >
# define TYPE_OPUT_RED 4
//input redirection: <
# define TYPE_IPUT_RED 5
# define TYPE_PIPE 6// |
# define TYPE_FLG 7// -l o si tenemos --no-print-directory

// 	varios code
# define QUOTE 39
# define DQUOTE 34
# define PIPE 124
# define CHAR_SPACE 32
//output redirection - >
# define OPUT_RED 62
//input redirection - <
# define IPUT_RED 60
# define POINT 46

//	strings
# define STR_PIPE "|"
# define STR_HEREDOC "<<"
# define STR_APPEND ">>"
# define STR_OUTPUT ">"
# define STR_INPUT "<"
# define STR_MINISHELL "minishell: "

# define EXECUTE_PIPE 1
# define EXECUTE_COMMAND 0

# define MAIN_MODE 0
# define EXEC_MODE 1

typedef struct s_exec
{
	int		pip[2];
	int		old_pip[2];
	int		fd_here_doc[2];
	int		fd_stdin;//nuevos variables para hacer pipes(para recibir)
	int		fd_stdout;//nuevos variables para hacer pipes(para redirigir)
	char	**exec_arg;
	char	*cmd_with_path;
	char	*cmd_no_path;
	char	*path;
	pid_t	proc;
	int		wait_status;
}	t_exec;

typedef struct s_parser
{
	char	*cmd;
	char	*raw_cmd;
	char	*path;
	char	**split_path;
	char	**split_read_line;
}	t_parser;

typedef struct s_line
{
	char			*str;
//	int				fd;
	int				type;
	struct s_line	*next;
}		t_line;

typedef struct s_pipe
{
	t_line			*lst_line;
	struct s_pipe	*next;
}				t_pipe;

typedef struct s_msh
{
	char		*read_line;
	char		**ev;
	int			pipe_active;
	int			exit_status;
	t_line		*lst_line;
	t_pipe		*lst_pipe;
	t_exec		exec;
	t_parser	parser;
}		t_msh;

//	split pipe
//	ft_split_pipe.c
int			ft_split_len_word(char *s, int i);
int			ft_split_calc_words(char *s);
char		**ft_split_free(char **split);
char		**ft_split_pipe(char *s);

//	builtins exec
//	minishell_builtin_???.c
int		builtin_cd(t_msh *msh);
int		builtin_echo(t_msh *msh);
int		builtin_env(t_msh *msh);
int		builtin_exit(t_msh *msh);
int		builtin_export(t_msh *msh);
int		builtin_pwd(t_msh *msh);
int		builtin_unset(t_msh *msh);

//	cases
//	minishell_case.c
char		*case_dollar(char *str, t_msh *msh);
char		*case_dollar_with_quotes(char *str, t_msh *msh);

//	check
//	minishell_check.c
int			initial_check(t_msh *msh);
int			check_file(char *file);
int			check_command(char *str);
int			check_ifbuiltin(char *str);

//	check syntax
//	minishell_check_syntax.c
int			check_syntax(t_msh *msh);
int			is_redirection(int type);

//	error
//	minishell_error.c
void		print_error_exit(t_msh **msh, char *s_err);
void		print_warning(char *s_warn);
void		print_warning_with_arg(char *file, char *s_warn);
void		print_perror(char *s_err);

//luego reorganizarlo
int			execute_child_argv(t_msh **msh);
void		execute_child(t_msh *msh);
void		execute_cmd(t_msh *msh);

//	execute
//	minishell_execute.c
void		execute_builtin(t_msh *msh);
void		execution(t_msh *msh);

//	execute redir
//	minishell_exec_redirection.c
void		control_redirection(t_msh *msh);
void		restore_redirection(t_msh *msh);

//	struct
//	minishell_struct.c
t_msh		*mshnew(char **env);
t_parser	parsernew(void);
t_exec		execnew(void);
void		add_new_line_node(char *line, int type_str, t_line **lst_line);

//  parser
//	minishell_parser.c
int			decide_type(char *str);

//  getter
//	minishell_getter.c
void		get_cmd_with_path(t_msh **msh);
char		**get_exec_argv(t_msh *msh, t_line *lst_line);
void		change_exec_arg_script(t_msh *msh);

//	heredoc
//	minishell_heredoc.c
void		write_herdoc(t_msh *msh, t_line *copy);
void		check_heredoc(t_msh *msh);
void		heredoc_redir(t_msh *msh);

//	quotes
//	minishell_quotes.c
int			is_quotes_pair(char *str, int i, int end);
int			where_next_quote_is(char *str, char quote, int i);
int			where_next_any_quote_is(char *str, int i);

//	pipe
//	minishell_pipe.c
int			check_pipe_in_word(char *str);
t_pipe		*new_lst_pipe(t_msh *msh);
void		addback_lst_pipe(t_msh *msh, t_pipe **lst_pipe, char *str);

//	t_line*
//	minishell_lst_line.c
t_line		*new_lst_line(t_msh *msh, char *read_line);
t_line		*new_lst_without_quotes(t_msh *msh, t_line **lst_line, char *rline);
t_line		*new_lst_with_quotes(t_msh *msh, t_line **lst_line, char *rline);

//	operators
//	minishell_operators.c
int			check_operators(char *str);
void		decide_operators(char *str, int i, t_line **lst_line);
int			skip_operators(char *str, int i);
void		addstr_to_lst_line(char *str, t_line **lst_line, int i);

//	free
//	minishell_free.c
void		free_msh(t_msh **msh);
void		free_lst_line(t_line **lst);
void		free_lst_pipe(t_pipe **lst_pipe);
void		free_3_str(char **s1, char **s2, char **s3);
void		free_exec(t_exec *exec);
void		exit_free_child(t_msh *msh, int exit_status);

//	utils
//	minishell_utils.c
int			calculate_len_lst_line(t_line *lst_line);
int			calculate_last_pos_word(char *str, int i);

//	utils
//	minishell_utils.c
int			check_ifempty_str(char *str);
void		free_str(char **str);
void		free_double_str(char ***double_str);
t_line		*ft_lst_line_last(t_line *lst);

//	Expand
//	minishell_expand.c
char		*expand(char *var, t_msh *msh);
char		*clean_var(char *str);
int			where_is_dollar(char *str, int i);

//	Search (something in **env)
//	minishell_search.c
char		*search_pwd(t_msh *msh);
char		*search_shell(t_msh *msh);
char		*search_path(t_msh *msh);

//	Signal
//	minishell_signal.c
void		handle_signal_main(int sign, siginfo_t *sa, void *data);
void		handle_signal_exec_mode(int sign, siginfo_t *sa, void *data);
void		signal_control_exec(t_msh *msh);
void		signal_control_main(t_msh *msh);

// Env
char		**create_env(char **env);

//	ATENCIO!!!
//	eliminar despues!!!
void		PRINT_lst_line(t_line *lst_line);
void		PRINT_lst_pipe(t_pipe *lst_pipe);
void		PRINT_split_line(char **double_str);
void		PRINT_comillas(char *read_line);
void		PRINT_fd(int fd);

#endif
