/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/25 15:35:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <msh_term.h>
#include <msh_lex.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

static void	signal_received(t_msh *prog)
{
	if (g_siggy)
		if (vecstr_reset(&prog->line.cmd))
			exit(1);
}

int			read_input(t_msh *prog)
{
	char		*tmp;
	int			ret;

	ft_printf("%s", prog->line.prompt);
	tmp = NULL;
	ret = get_next_line(STDIN, &tmp);
	while (ret >= 0)
	{
		signal_received(prog);
		if (ret == 0 && ((tmp) ? ft_strlen(tmp) : 0) + prog->line.cmd.len == 0)
		{
			ft_printf("exit\n");
			exit(0);
		}
		if (vecstr_append_str(&prog->line.cmd, tmp))
			exit(1);
		free(tmp);
		tmp = NULL;
		if (ret == 1)
			break ;
		else
			ret = get_next_line(STDIN, &tmp);
	}
	return (1);
}
