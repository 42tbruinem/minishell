/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 16:30:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <msh_builtin.h>
#include <msh_exec.h>
#include <msh_io.h>
#include <msh_lex.h>

static	t_builtin	get_builtin(int id)
{
	static const t_builtin	builtins[] = {
	[B_ENV] = &ft_env,
	[B_PWD] = &ft_pwd,
	[B_ECHO] = &ft_echo,
	[B_EXPORT] = &ft_export,
	[B_UNSET] = &ft_unset,
	[B_EXIT] = &ft_exit,
	[B_CD] = &ft_cd
	};

	return (builtins[id]);
}

static void			nofork(t_msh *prog, t_cmd *cmd, int id)
{
	int		std[2];

	std[0] = dup(STDIN);
	std[1] = dup(STDOUT);
	if (std[0] == -1 || std[1] == -1)
		exit(1);
	if (cmd->iostream[0] != -1)
		if (dup2(STDIN, cmd->iostream[0]) == -1)
			exit(1);
	if (cmd->iostream[1] != -1)
		if (dup2(STDOUT, cmd->iostream[1] == -1))
			exit(1);
	get_builtin(id)(prog, ft_str2len(cmd->args), cmd->args);
	if (dup2(STDIN, std[0]) == -1)
		exit(1);
	if (dup2(STDOUT, std[1]) == -1)
		exit(1);
}

void				run_builtin(t_msh *prog, t_cmd *cmd, int id)
{
	int	pid;

	if (cmd->cmdtype != PIPEDCOMMAND &&
		(!cmd->next || cmd->next->cmdtype != PIPEDCOMMAND))
		return (nofork(prog, cmd, id));
	pid = fork();
	if (!pid)
	{
		close_ifnot(&prog->file_arr, cmd->iostream);
		if (cmd->iostream[READ] != -1 &&
			dup2(cmd->iostream[READ], STDIN) == -1)
			exit(1);
		if (cmd->iostream[WRITE] != -1 &&
			dup2(cmd->iostream[WRITE], STDOUT) == -1)
			exit(1);
		get_builtin(id)(prog, ft_str2len(cmd->args), cmd->args);
		close_iostream(cmd->iostream);
		exit(0);
	}
	vec_add(&g_pid, &pid);
	close_iostream(cmd->iostream);
}
