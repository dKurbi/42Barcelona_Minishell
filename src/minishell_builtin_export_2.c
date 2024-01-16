/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:35:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 21:41:25 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//equal es =
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