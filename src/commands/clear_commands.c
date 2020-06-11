/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 19:22:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:02:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

int		clear_commands(t_cmd *commands)
{
	t_cmd	*iter;
	t_cmd	*del;

	iter = commands;
	while (iter)
	{
		del = iter;
		iter = iter->next;
		free(del);
	}
	return (0);
}
