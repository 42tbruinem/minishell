/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_program.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/22 14:35:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <msh_exec.h>
#include <msh_io.h>

#include <stdio.h>

static void	run(t_msh *prog, t_cmd *cmd, char *abspath)
{
	close_ifnot(&prog->file_arr, cmd->iostream);
	if (cmd->iostream[READ] != -1 &&
		dup2(cmd->iostream[READ], STDIN) == -1)
		exit(1);
	if (cmd->iostream[WRITE] != -1 &&
		dup2(cmd->iostream[WRITE], STDOUT) == -1)
		exit(1);
	if (abspath && execve(abspath, cmd->args, prog->envp) == -1)
		exit(1);
	exit(1);
}

void		run_program(t_msh *prog, t_cmd *cmd, char *abspath)
{
	int pid;

	if (!prog->envp)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
		run(prog, cmd, abspath);
	vec_add(&g_pid, &pid);
	close_iostream(cmd->iostream);
	free(abspath);
}
