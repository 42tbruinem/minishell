/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 17:31:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/24 23:50:41 by tbruinem      ########   odam.nl         */
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
	if (g_pid.index)
		ft_printf("\n");
	else
		ft_printf("\n%s", g_prompt);
}

void			sighandler(int signal)
{
	if (g_pid.index == 0)
	{
		g_siggy += 1;
	}
	kill_processes(signal);
}
