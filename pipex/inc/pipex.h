/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:18:16 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 01:40:41 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
}					t_info;

//handler.c
void	px_handle_child(t_info **info, int i);
void	px_handle_parent(t_info **info, int i);

//path_and_cmd.c
char	*px_find_path(t_info **info);
int		px_if_av_cmd_x_ok(t_info **info, int i);
void	px_find_cmd(t_info **info, int i);
void	px_manage_av(t_info **info);

//utils.c
void	px_free_string(char **s);
void	px_free_split(char ***split);
char	*px_cut_bef_space(char *s);
char	*px_skip_space(char *s);
int		px_check_ifempty(char *s);

//pipex_utils.c
t_info	*infonew(char **av, char **ev);
void	infofree(t_info **info, int flag);
void	px_print_error(t_info *info, int flag, int i);
void	px_create_execve_args(t_info **info, int i);

//pipex.c
void	px_parent(t_info **info);
void	px_child(t_info **info);
void	px_pipex(t_info *info);

#endif