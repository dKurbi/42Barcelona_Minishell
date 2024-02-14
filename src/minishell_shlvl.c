/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:15:10 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/14 16:33:25 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	increment_shlvl_decide_num(char *str)
{
	int	result;

	result = ft_atoi(str);
	if (result < 0)
		return (-1);
	else if (result >= 1000)
	{
		ft_putstr_fd("minishell: shell level (", STDERR_FILENO);
		ft_putnbr_fd(result + 1, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
		return (0);
	}
	return (result);
}

//LEVELUP shlvl
void	increment_shlvl(t_msh *msh, char ***r, char *if_shlvl)
{
	char	**rtn;
	int		i;
	char	*new_level;
	int		num_atoi;

	num_atoi = 0;
	i = 0;
	rtn = *r;
	while (rtn[i] && ft_strncmp(rtn[i], "SHLVL=", 6))
		i++;
	if (!if_shlvl)
		return ;
	new_level = ft_itoa(increment_shlvl_decide_num(rtn[i] + 6) + 1);
	if (!new_level)
		print_error_exit(&msh, ERR_MALLOC);
	free_str(&rtn[i]);
	rtn[i] = ft_strjoin("SHLVL=", new_level);
	free_str(&new_level);
	if (!rtn[i])
		free_double_str(r);
}
