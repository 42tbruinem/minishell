/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 19:22:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:43:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <msh_lex.h>
#include <msh_cmd.h>

int			get_commands(t_msh *prog, t_tok *tokens, size_t totaltokens)
{
	size_t	i;
	int		cmd;

	i = 0;
	cmd = 0;
	if (!conv_tokens(prog, tokens, totaltokens))
		return (0);
	if (!vec_new(&prog->file_arr, sizeof(int)))
		return (0);
	prog->commands = NULL;
	while (i < totaltokens)
	{
		if (cmd == tokens[i].cmd_num)
		{
			if (!push_command(&prog->commands,
				new_command((char **)prog->args.store + i + cmd,
				(int *)prog->argtypes.store + i + cmd, &prog->file_arr)))
				return (clear_commands(prog->commands));
			cmd++;
		}
		i++;
	}
	return (1);
}
