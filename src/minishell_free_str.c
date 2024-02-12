/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:03:00 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/11 19:58:06 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//free 3 strings
void	free_2_str(char **s1, char **s2)
{
	if (*s1 != NULL)
		free_str(s1);
	if (*s2 != NULL)
		free_str(s2);
}

//free memory of char *
void	free_str(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

//free memory of char **
void	free_double_str(char ***double_str)
{
	int	i;

	if (*double_str == NULL || double_str == NULL)
		return ;
	i = 0;
	while ((*double_str)[i])
	{
		free_str(&(*double_str)[i]);
		i++;
	}
	free(*double_str);
	*double_str = NULL;
}
