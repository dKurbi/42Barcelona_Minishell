/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal_handle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 04:25:20 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/29 04:25:54 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	handle_signal_heredoc(int sign, siginfo_t *sa, void *data)
{
	(void)(sa);
	(void)(data);
	if (sign == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		exit(1);
	}
}

void	handle_signal_main(int sign, siginfo_t *sa, void *data)
{
	(void)(sa);
	(void)(data);

	if (sign == SIGINT)
	{
		g_exit_status = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_exec_mode(int sign, siginfo_t *sa, void *data)
{
	(void)(data);
	(void)(sa);
	if (sign == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		exit(130);
	}
	if (sign == SIGQUIT)
	{
		printf("\n");
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(131);
	}
}
