/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:13:39 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 19:56:53 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef struct s_info
{
	int				pip[2];
	char			**av;
	char			**ev;
	char			**exe_arg;
	char			*cmd;
	char			*raw_cmd;
	int				fd1;
	int				fd2;
	pid_t			proc;
	int				ac;
}					t_info;

//handler_bonus.c
void	px_manage_av_cmds(t_info *info);
void	px_handle_child(t_info **info, int i);
void	px_handle_parent(t_info **info, int i);

//path_and_cmd_bonus.c
char	*px_find_path(t_info **info);
int		px_if_av_cmd_x_ok(t_info **info, int i);
void	px_find_cmd(t_info **info, int i);

//utils_bonus.c
void	px_free_string(char **s);
void	px_free_split(char ***split);
char	*px_cut_bef_space(char *s);
char	*px_skip_space(char *s);
int		px_check_ifempty(char *s);

//pipex_utils_bonus.c
t_info	*infonew(char **av, char **ev, int ac);
void	infofree(t_info **info, int flag);
void	px_print_error(t_info *info, int flag, int i);
void	px_create_execve_args(t_info **info, int i);

//pipex_bonus.c
void	px_parent(t_info **info, int i_last);
void	px_child(t_info **info, int i);
void	px_pipex_bonus(t_info *info, int i, int i_last);

#endif
