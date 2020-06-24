/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 17:31:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/24 14:59:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libft.h>
#include <minishell.h>
#include <sys/types.h>
#include <errno.h>

static void		kill_processes(int signal)
{
	size_t		i;
	pid_t		process;

	i = 0;
	while (i < g_pid.index)
	{
		vec_get(&g_pid, &process, i);
		kill(process, signal);
		i++;
	}
}

void			sighandler(int signal)
{
	size_t		i;

	i = 0;
	if (g_pid.index == 0)
	{
		g_siggy += 1;
	}
	kill_processes(signal);
}
