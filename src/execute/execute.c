/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 16:20:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <msh_builtin.h>
#include <msh_cmd.h>
#include <msh_exec.h>

static	int	is_builtin(char *program)
{
	static const char	*builtins[] = {
	[B_CD] = "cd",
	[B_ECHO] = "echo",
	[B_PWD] = "pwd",
	[B_EXPORT] = "export",
	[B_UNSET] = "unset",
	[B_ENV] = "env",
	[B_EXIT] = "exit",
	[7] = NULL,
	};

	return (ft_str2cmpstr(builtins, program));
}

void		execute(t_msh *prog, t_cmd *cmd)
{
	char	*abspath;
	int		builtin;

	abspath = NULL;
	builtin = is_builtin(cmd->args[0]);
	if (builtin >= 0)
		return (run_builtin(prog, cmd, builtin));
	get_abspath(cmd->args[0], &abspath, prog->env);
	return (run_program(prog, cmd, abspath));
}
