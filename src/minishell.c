/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/12 16:25:24 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_msh	*msh;

	(void) av;
	if (ac != 1)
		exit_error(ERR_AC);
	msh = mshnew(env);
	if (!msh)
		exit_error(ERR_MALLOC);
	while (1)
	{
		msh->line = readline("Minishell$ ");
		printf("%s\n", msh->line);
		parser_line(msh);
		executor_line(msh);
		free(msh->line);
		msh->line = NULL;
	}
	return (0);
}
