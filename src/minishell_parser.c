/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:22:21 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/16 18:53:44 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* char	*find_path(t_msh *msh)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (msh->ev[++i])
	{
		if (ft_strnstr(msh->ev[i], "PATH=", 5) != NULL)
		{
			path = msh->ev[i];
			return (ft_strdup(path + 5));
		}
	}
	return (path);
}
void parser_line(t_msh *msh)
{
	msh->parser.path = find_path(msh);
	if (!msh->parser.path)
		msh->parser.path = ft_strdup("");
	find_pipes_quotes(msh);
	msh->parser.split_path =  ft_split(msh->parser.path, ':');
	msh->parser.raw_cmd = get_raw_cmd(msh);
	msh->parser.cmd = get_cmd(msh);
} */
