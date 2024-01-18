/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:35:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/18 01:12:05 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//equal es = (puede calcular hasta declare -x var=... || declare -x var)
int	len_before_equal(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}