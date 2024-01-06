/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:26:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/06 19:46:10 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_signal(int sign, siginfo_t *sa, void *data)
{
	t_msh *msh;
			
	msh = (t_msh *) data;
	if (sign == SIGINT)
	{
		printf("\nctrl c\n");
		printf("%d\n", msh->exit_status);
		printf("proceso n: %d\n", sa->si_pid);
	}
}