/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:49:09 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/12 16:12:33 by dkurcbar         ###   ########.fr       */
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

#define ERR_AC "only provide ./minishell\n"
#define ERR_MALLOC "memory allocation error\n"

typedef struct s_exec
{
	int		pip[2];
	char	**exe_arg;
	char	*cmd;
	char	*raw_cmd;
	char	*path;
	char	**split_path;
	pid_t	proc;

	int		wait_status;

}	t_exec;

typedef struct s_msh
{
	char	*line;
	char	**ev;
	t_exec	exec;
}		t_msh;

//	error
void	exit_error(char *s_err);

//	struct
t_msh	*mshnew(char **env);

#endif
