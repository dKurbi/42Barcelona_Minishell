/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:10:18 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 15:57:10 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	waitpid_process(t_msh *msh, int num_commands)
{
	int	status;

	while (num_commands >= 0)
	{
		num_commands--;
		waitpid(-1, &status, 0);
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
