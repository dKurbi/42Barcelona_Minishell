/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:29:48 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/14 13:50:34 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pre_init_check(t_msh **msh, int ac, char **av, char **ev)
{
	if (!isatty(STDIN_FILENO))
		print_error_exit(msh, ERR_NOT_TTY);
	if (ac != 1)
		print_error_exit(msh, ERR_AC);
	*msh = mshnew(av, ev);
	if (!*msh)
		print_error_exit(msh, ERR_MALLOC);
}
