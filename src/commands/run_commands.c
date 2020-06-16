/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 21:50:53 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 19:34:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static	void	collect_souls(t_msh *prog)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < g_pid.index)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			prog->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			prog->exit_status = 128 + WTERMSIG(status);
		i++;
	}
	vec_destroy(&g_pid, NULL);
}

int				run_commands(t_msh *prog, t_cmd *commands)
{
	t_cmd	*del;

	if (!vec_new(&g_pid, sizeof(int)))
		return (0);
	while (commands)
	{
		if (!in_out_redirection(prog, commands))
			return (0);
		(void)execute(prog, commands);
		del = commands;
		commands = commands->next;
		free(del);
	}
	vec_destroy(&prog->args, NULL);
	vec_destroy(&prog->argtypes, NULL);
	close_all(&prog->file_arr);
	vec_destroy(&prog->file_arr, NULL);
	collect_souls(prog);
	return (1);
}
