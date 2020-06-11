/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 19:22:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:04:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

void	print_command(t_cmd *command)
{
	size_t				i;
	static const char	*commandtypes[] = {
	[EOC] = "END_OF_COMMAND",
	[PIPE] = "PIPE",
	[APPEND] = "APPEND",
	[TRUNC] = "TRUNC",
	[IN_REDIR] = "IN_REDIR",
	[DEFAULT] = "DEFAULT"
	};

	i = 0;
	dprintf(2, "type: %s\n", commandtypes[command->cmdtype]);
	while (command->args[i])
	{
		dprintf(2, "%s%c", command->args[i], command->args[i + 1] ? ' ' : '\n');
		i++;
	}
}
