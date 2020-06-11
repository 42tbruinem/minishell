/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   in_out_redirection.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 21:53:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:53:14 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		in_out_redirection(t_msh *prog, t_cmd *command)
{
	command->iostream[0] = -1;
	command->iostream[1] = -1;
	if (command->cmdtype == PIPEDCOMMAND)
		command->iostream[READ] = command->cmdpipe[READ];
	if (command->next && command->next->cmdtype == PIPEDCOMMAND)
		command->iostream[WRITE] = command->next->cmdpipe[WRITE];
	return (set_redirection(command, command->args,
		command->argtypes, &prog->file_arr));
}
