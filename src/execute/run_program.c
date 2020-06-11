/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_program.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:20:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int		run_program(t_msh *prog, t_cmd *cmd, char *abspath)
{
	int pid;

	if (!prog->envp)
		return (1);
	pid = fork();
	if (!pid)
	{
		close_ifnot(&prog->file_arr, cmd->iostream);
		if (cmd->iostream[READ] != -1 &&
			dup2(cmd->iostream[READ], STDIN) == -1)
			exit(0);
		if (cmd->iostream[WRITE] != -1 &&
			dup2(cmd->iostream[WRITE], STDOUT) == -1)
			exit(0);
		if (abspath && execve(abspath, cmd->args, prog->envp) == -1)
			exit(0);
		if (!abspath && execve(cmd->args[0], cmd->args, prog->envp) == -1)
			exit(0);
		close_iostream(cmd->iostream);
		exit(0);
	}
	vec_add(&g_pid, &pid);
	close_iostream(cmd->iostream);
	free(abspath);
	return (0);
}
