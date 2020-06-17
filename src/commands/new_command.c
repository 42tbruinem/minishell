/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_command.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 19:22:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:43:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <msh_lex.h>
#include <msh_cmd.h>

static	int		is_pipe(int *types)
{
	int	i;

	i = 0;
	while (types[i] != SEPARATOR)
	{
		if (types[i] == PIPEDCOMMAND)
			return (1);
		i++;
	}
	return (0);
}

t_cmd			*new_command(char **argstart, int *types, t_vec *fd_arr)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmdpipe[0] = -1;
	new->cmdpipe[1] = -1;
	new->cmdtype = (is_pipe(types) ? PIPEDCOMMAND : COMMAND);
	if (new->cmdtype == PIPEDCOMMAND)
	{
		if (pipe(new->cmdpipe) == -1)
		{
			free(new);
			return (NULL);
		}
		vec_add(fd_arr, &new->cmdpipe[0]);
		vec_add(fd_arr, &new->cmdpipe[1]);
	}
	new->argtypes = types;
	new->args = argstart;
	new->next = NULL;
	return (new);
}
