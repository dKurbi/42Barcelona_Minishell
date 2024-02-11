/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:10:18 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/09 15:58:24 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//for pipes
void	waitpid_process(t_msh *msh, int num_commands)
{
	int	status;
	int	flag;

	flag = 0;
	while (--num_commands >= 0)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && !flag)
			{
				msh->exit_status = 130;
				printf("\n");
				flag = 1;
			}
			else if (WTERMSIG(status) == SIGQUIT && !flag)
			{
				msh->exit_status = 131;
				printf("Quit: 3\n");
				flag = 1;
			}
		}
	}
}

//waiting to all commands and return it's status
void	wait_process(t_msh *msh, pid_t pid, int num_commands)
{
	int	status;

	while (num_commands >= 0)
	{
		num_commands--;
		if (pid == wait(&status))
		{
			if (WIFEXITED(status))
				msh->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					msh->exit_status = 130;
					printf("\n");
				}
				else if (WTERMSIG(status) == SIGQUIT)
				{
					msh->exit_status = 131;
					printf("\nQuit: 3\n");
				}
			}
		}
	}
}
