/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_eof.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:57:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

int		send_eof(t_line *line, char buf[6])
{
	(void)buf;
	if (vecstr_len(&line->cmd) == 0)
	{
		ft_printf("exit\n");
		return (CTRL_D);
	}
	return (0);
}
