/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/25 00:30:20 by tbruinem      ########   odam.nl         */
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

	line = &prog->line;
	ft_printf("%s", line->prompt);
	if (get_next_line(STDIN, &line->cmd.str) <= 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	line->cmd.capacity = ft_strlen(line->cmd.str) + 1;
	line->cmd.len = line->cmd.capacity;
	return (1);
}
