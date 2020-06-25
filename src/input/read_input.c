/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/25 14:04:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <msh_term.h>
#include <msh_lex.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

int			read_input(t_msh *prog)
{
	t_line		*line;
	char		*tmp;
	int			ret;

	line = &prog->line;
	ft_printf("%s", line->prompt);
	tmp = NULL;
	ret = get_next_line(STDIN, &tmp);
	while (ret >= 0)
	{
		if (g_siggy)
			if (vecstr_reset(&prog->line.cmd))
				exit(1);
		if (ret == 0 && ((tmp) ? ft_strlen(tmp) : 0) + line->cmd.len == 0)
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
