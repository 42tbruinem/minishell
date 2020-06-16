/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 17:31:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 19:35:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libft.h>
#include <minishell.h>
#include <sys/types.h>
#include <stdio.h>

void	sighandler(int signal)
{
	size_t		i;
	pid_t		process;

	i = 0;
	if (g_pid.index == 0)
	{
		if (signal == SIGINT)
			ft_printf("^C");
		if (signal == SIGQUIT)
			ft_printf("^\\");
		while ((int)i < g_total_lines - g_current_line + 1)
		{
			ft_printf("\n");
			i++;
		}
		ft_printf("%s", g_prompt);
		g_siggy += 1;
		i = 0;
	}
	while (i < g_pid.index)
	{
		vec_get(&g_pid, &process, i);
		if (kill(process, signal) == -1)
			(void)i;
		i++;
	}
}
