/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_eof.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/29 14:33:24 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>
#include <msh_lex.h>

static int	restart_input(t_line *line, char buf[6])
{
	int			endstate;

	endstate = get_endstate(&line->cmd);
	if (endstate == INDOUBLEQUOTE)
		ft_printf_fd(STDERR, "msh: unexpected EOF while looking for"
				" matching `\"\'\n");
	else if (endstate == PIPE_PIPE)
		ft_printf_fd(STDERR, "msh: unexpected EOF while looking for"
				" matching `|\'\n");
	else
		ft_printf_fd(STDERR, "msh: unexpected EOF while looking for"
				" matching `\'\'\n");
	line->cursor.row += 1;
	if (line->cursor.row >= line->max.row)
		line->cursor.row -= 1;
	line->multiline_len = 0;
	line->promptlen = ft_no_ansi_strlen(line->prompt);
	clear_input(line, buf);
	return (0);
}

int			send_eof(t_line *line, char buf[6])
{
	if (vecstr_len(&line->cmd) == line->multiline_len)
	{
		if (line->multiline_len > 0)
			return (restart_input(line, buf));
		ft_printf("exit\n");
		return (CTRL_D);
	}
	return (0);
}
