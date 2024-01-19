/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:03:00 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/12 20:04:29 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//esto es para que evitar norminette
void	free_3_str(char **s1, char **s2, char **s3)
{
	if (*s1 != NULL)
		free_str(s1);
	if (*s2 != NULL)
		free_str(s2);
	if (*s3 != NULL)
		free_str(s3);
}

//free memoria de char *
void	free_str(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

//free memoria de char **
void	free_double_str(char ***double_str)
{
	int	i;

	if (*double_str == NULL)
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
