/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 19:22:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:43:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <msh_cmd.h>

t_cmd	*push_command(t_cmd **commands, t_cmd *new)
{
	t_cmd	*iter;

	if (!new)
		return (NULL);
	if (!*commands)
	{
		*commands = new;
		return (new);
	}
	iter = *commands;
	while (iter && iter->next)
		iter = iter->next;
	iter->next = new;
	return (new);
}
