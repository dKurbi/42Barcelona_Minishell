/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:49:09 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/06 19:32:14 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

// error code
# define ERR_AC "only provide ./minishell\n"
# define ERR_MALLOC "memory allocation error\n"
# define ERR_QUOTE "quote>\n"
# define ERR_PIPE "content after pipe required\n"
# define ERR_SYNTAX "syntax error near unexpected token\n"

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

//	strings
# define STR_PIPE "|"
# define STR_HEREDOC "<<"
# define STR_APPEND ">>"
# define STR_OUTPUT ">"
# define STR_INPUT "<"

# define EXECUTE_PIPE 1
# define EXECUTE_COMMAND 0

typedef struct s_exec
{
	int		pip[2];
	int		fd_stdin;//nuevos variables para hacer pipes(para recibir)
	int		fd_stdout;//nuevos variables para hacer pipes(para redirigir)
	char	**exe_arg;
	char	*cmd;
	char	*raw_cmd;
	char	*path;
	char	**split_path;
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

//	cases
//	minishell_case.c
char		*case_dollar(char *str, t_msh *msh);
char		*case_dollar_with_quotes(char *str, t_msh *msh);

//	check
//	minishell_check.c
int			initial_check(t_msh *msh);

//	check syntax
//	minishell_check_syntax.c
int			check_syntax(t_msh *msh);

//	error
//	minishell_error.c
void		print_error_exit(t_msh **msh, char *s_err);
void		print_warning(char *s_warn);

//	execute
//	minishell_execute.c
void		execution(t_msh *msh);

//	struct
//	minishell_struct.c
t_msh		*mshnew(char **env);
t_parser	parsernew(void);
t_exec		execnew(void);
void		add_new_line_node(char *line, int type_str, t_line **lst_line);

//  parser
//	minishell_parser.c
void		parser_line(t_msh *msh);
int			decide_type(char *str);

//  getter
//	minishell_getter.c
char		*get_raw_cmd(t_msh *msh);
char		*get_cmd(t_msh *msh);
char		**get_exec_argv(t_msh *msh, t_line *lst_line);

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
void		addstr_to_lst_line(char *str, t_line **lst_line);

//	free
//	minishell_free.c
void		free_msh(t_msh **msh);
void		free_lst_line(t_line **lst);
void		free_lst_pipe(t_pipe **lst_pipe);
void		free_3_str(char **s1, char **s2, char **s3);

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

// Signal

void handle_signal(int sign, siginfo_t *sa, void *data);




//	ATENCIO!!!
//	eliminar despues!!!
void		PRINT_lst_line(t_line *lst_line);
void		PRINT_lst_pipe(t_pipe *lst_pipe);
void		PRINT_split_line(char **double_str);



#endif
