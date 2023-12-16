/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:49:09 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/16 18:45:51 by iassambe         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// error code
# define ERR_AC "only provide ./minishell\n"
# define ERR_MALLOC "memory allocation error\n"
# define ERR_QUOTE "other quote required\n"

// type code
# define TYPE_STR 0// "hola que tal"
# define TYPE_CMD 1// ls
# define TYPE_HDC 2// <<
# define TYPE_PIPE 3// |
# define TYPE_REDIR 4// > o si tenemos <
# define TYPE_FLG 5// -l o si tenemos --no-print-directory

// 	varios code
# define QUOTE 39
# define DQUOTE 34
# define PIPE 124
# define CHAR_SPACE 32

typedef struct s_exec
{
	int		pip[2];
	int		fd_stdin;//nuevos variables para hacer pipes
	int		fd_stdout;//nuevos variables para hacer pipes
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

typedef struct s_msh
{
	char		*read_line;
	char		**ev;
	int			pipe_active;//nuevo variable
	t_line		*lst_line;
	t_exec		exec;
	t_parser	parser;
}		t_msh;

//	error
void		exit_error(char *s_err);

//	struct
t_msh		*mshnew(char **env);
t_parser	parsernew(void);
t_exec		execnew(void);

//  parser
void		parser_line(t_msh *msh);

//  getter
char		*get_raw_cmd(t_msh *msh);
char		*get_cmd(t_msh *msh);

// quotes
int			is_quotes_pair(char *str, int i, int end);
int			where_next_quote_is(char *str, char quote, int i);
int			where_next_any_quote_is(char *str, int i);
void		append_until_required(char *str, char required_char);

//pipe
int			check_pipe_in_word(char *str);
void		pipe_divide_word(char *str, t_line **lst_line);

// line_st
void		add_new_line_node(char *line, int type_str, t_line **lst_line);
t_line		*new_line_list(t_msh *msh, char *str);
t_line		*ft_lst_line_last(t_line *lst);
t_line		*new_list_without_quotes(char *str, t_line **lst_line, t_msh *msh);
t_line		*new_list_with_quotes(char *str, t_msh *msh);

// free
void		free_str(char **str);
void		free_double_str(char ***double_str);
void		free_lst_line(t_line **lst);
void		free_msh(t_msh **msh);


//elimminar despues
void		PRINT_lst_line(t_msh *msh);

#endif