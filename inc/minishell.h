/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:49:09 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/26 20:17:17 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/* ************************************************************************** */
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
# define ERR_BUILTIN_HAS_ARGS "illegal option\n"
# define ERR_NO_PWD "failed finding pwd\n"
# define ERR_TOO_MANY "too many arguments\n"
# define ERR_NUMERIC "numeric argument required\n"
# define ERR_INVALID_INDENT "not a valid identifier\n"
/* ************************************************************************** */

/* ************************************************************************** */
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
/* ************************************************************************** */


/* ************************************************************************** */
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
/* ************************************************************************** */

/* ************************************************************************** */
//	strings
# define STR_PIPE "|"
# define STR_HEREDOC "<<"
# define STR_APPEND ">>"
# define STR_OUTPUT ">"
# define STR_INPUT "<"
# define STR_MINISHELL "minishell: "
/* ************************************************************************** */

/* ************************************************************************** */
# define EXECUTE_PIPE 1
# define EXECUTE_COMMAND 0
/* ************************************************************************** */

/* ************************************************************************** */
# define MAIN_MODE 0
# define EXEC_MODE 1
/* ************************************************************************** */

typedef struct s_exec
{
	int		pip[2];
	int		old_pip[2];
	int		fd_here_doc[2];
	int		fd_stdin;
	int		fd_stdout;
	char	**exec_arg;
	char	*cmd_with_path;
	char	*cmd_no_path;
	char	*path;
	pid_t	proc;
	int		wait_status;
}	t_exec;

typedef struct s_create
{
	char	*rline;
	int		last;
	char	*join;
	char	*str;
}	t_create;

typedef struct s_line
{
	char			*str;
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
}		t_msh;

//	split pipe
//	ft_split_pipe.c
int			ft_split_len_word(char *s, int i);
int			ft_split_calc_words(char *s);
char		**ft_split_free(char **split);
char		**ft_split_pipe(char *s);

//	builtins exec
//	minishell_builtin_cd.c
char		*search_home(t_msh *msh);
int			builtin_cd(t_msh *msh);

//	builtins exec
//	minishell_builtin_echo.c
int			builtin_echo(t_msh *msh);

//	builtins exec
//	minishell_builtin_env_utils.c
int			env_len(t_msh *msh);
int			if_var_in_env(t_msh *msh, char *var);

//	builtins exec
//	minishell_builtin_env.c
char		**create_env(char **env);
int			builtin_env(t_msh *msh);

//	builtins exec
//	minishell_builtin_exit.c
int			builtin_exit(t_msh *msh);

//	builtins exec
//	minishell_builtin_export_2.c
int			export_len_env(char **ev);
int			len_before_equal(char *str);
int			export_create_var_len(t_msh *msh, int i);
char		*export_create_var(t_msh *msh, int i);

//	builtins exec
//	minishell_builtin_export.c
int			builtin_export(t_msh *msh);

//	builtins exec
//	minishell_builtin_pwd.c
int			builtin_pwd(t_msh *msh);

//	builtins exec
//	minishell_builtin_unset.c
int			builtin_unset(t_msh *msh);

//	cases
//	minishell_case.c
char		*case_dollar(char *str, t_msh *msh);
char		*case_dollar_with_quotes(char *str, t_msh *msh);

//	check syntax
//	minishell_check_syntax.c
int			is_redirection(int type);
int			check_syntax(t_msh *msh);

//	check
//	minishell_check.c
int			initial_check(t_msh *msh);
int			check_file(char *file);
int			check_command(char *str);
int			check_ifbuiltin(char *str);
int			check_var_equal(char *str);

//	error
//	minishell_error.c
void		print_error_exit(t_msh **msh, char *s_err);
void		print_warning(char *s_warn);
void		print_warning_with_arg(char *file, char *s_warn);
void		print_perror(char *s_err);
void		print_perror_with_arg(char *cmd, char *file);

//	execute controling redirections
//	minishell_exec_redirection.c
int			control_redirection(t_msh *msh);
void		restore_redirection(t_msh *msh);

//	execute command
//	minishell_execute_command.c
int			execute_child_argv(t_msh **msh);
void		execute_check_command_and_execve(t_msh *msh);
void		execute_child(t_msh *msh);
void		execute_cmd(t_msh *msh);

//	execute pipes
//	minishell_execute_pipe.c
void		execute_cmd_pipe(t_msh *msh);

//	execute (general file for executions)
//	minishell_execute.c
void		execute_builtin(t_msh *msh);
void		execution_line(t_msh *msh, int mode);
void		execution_pipes(t_msh *msh);
void		execution(t_msh *msh);

//	expanding ($ sign)
//	minishell_expand.c
int			where_is_dollar(char *str, int i);
char		*clean_var(char *str);
char		*expand(char *var, t_msh *msh);

//	free strings
//	minishell_free_str.c
void		free_3_str(char **s1, char **s2, char **s3);
void		free_str(char **str);
void		free_double_str(char ***double_str);

//	free
//	minishell_free.c
void		free_msh(t_msh **msh);
void		free_lst_line(t_line **lst_line);
void		free_lst_pipe(t_pipe **lst_pipe);
void		free_exec(t_exec *exec);
void		exit_free_child(t_msh *msh, int exit_status);

//  getter
//	minishell_getter.c
void		get_cmd_with_path(t_msh **msh);
char		**get_exec_argv(t_msh *msh, t_line *lst_line);

//	heredoc control
//	minishell_heredoc.c
void		write_herdoc(t_msh *msh, t_line *copy);
void		check_heredoc(t_msh *msh);
void		heredoc_redir(t_msh *msh);

//	lst_line but with quotes control
//	minishell_lst_line_quotes.c
char		*join_str_and_quotes(t_msh *msh, t_create crt);
int			lst_add_quotes(t_msh *msh, t_line **lst_line, t_create crt, int i);
int			lst_add_str(t_msh *msh, t_line **lst_line, t_create crt, int i);

//	lst_line 
//	minishell_lst_line.c
t_line		*new_lst_with_quotes(t_msh *msh, t_line **lst_line, char *rline);
t_line		*new_lst_without_quotes(t_msh *msh, t_line **lst_line, char *rline);
t_line		*new_lst_line(t_msh *msh, char *read_line);

//	operators
//	minishell_operators.c
int			check_operators(char *str);
void		decide_operators(char *str, int i, t_line **lst_line);
int			skip_operators(char *str, int i);
void		addstr_to_lst_line(char *str, t_line **lst_line, int i);

//	pipe
//	minishell_pipe.c
int			check_pipe_in_word(char *str);
void		addback_lst_pipe(t_msh *msh, t_pipe **lst_pipe, char *str);
t_pipe		*new_lst_pipe(t_msh *msh);

//	quotes
//	minishell_quotes.c
int			is_quotes_pair(char *str, int i, int end);
int			where_next_quote_is(char *str, char quote, int i);
int			where_next_any_quote_is(char *str, int i);
void		strtrim_quotes_all(t_msh *msh);

//	Search (something in **env)
//	minishell_search.c
char		*search_path(t_msh *msh);
char		*search_shell(t_msh *msh);
char		*search_pwd(t_msh *msh);
char		*search_oldpwd(t_msh *msh);

//	Signal
//	minishell_signal.c
void		handle_signal_heredoc(int sign, siginfo_t *sa, void *data);
//void	handle_signal_heredoc(int sign);
void		handle_signal_main(int sign, siginfo_t *sa, void *data);
void		handle_signal_exec_mode(int sign, siginfo_t *sa, void *data);
void		handle_nothing(int sign, siginfo_t *sa, void *data);
void		signal_control_heredoc(t_msh *msh);
void		signal_control_exec(t_msh *msh);
void		signal_control_main(t_msh *msh);
void		signal_control_block(t_msh *msh);

//	struct
//	minishell_struct.c
t_msh		*mshnew(char **env);
t_exec		execnew(void);
void		add_new_line_node(char *line, int type_str, t_line **lst_line);
t_line		*ft_lst_line_last(t_line *lst);

//	utils
//	minishell_utils_2.c
int			calculate_len_lst_line(t_line *lst_line);
int			calculate_last_pos_word(char *str, int i);
char		*strtrim_str_quotes(char *str);
int			decide_type(char *str);
void		ft_close(int fd);
void		ft_close_pointer(int *fd);

//	utils
//	minishell_utils.c
int			check_ifempty_str(char *str);
void		change_exec_arg_script(t_msh *msh);
char		if_quote_start_final(char *str);
int			if_srcipt(char *str);
void		print_warning_with_3_arg(char *s1, char *s2, char *s_warn);





//	ATENCIO!!!
//	eliminar despues!!!
void		PRINT_lst_line(t_line *lst_line);
void		PRINT_lst_pipe(t_pipe *lst_pipe);
void		PRINT_split_line(char **double_str);
void		PRINT_comillas(char *read_line);
void		PRINT_fd(int fd);

#endif
