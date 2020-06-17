/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_eof.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 16:39:36 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>
#include <msh_lex.h>

int		send_eof(t_line *line, char buf[6])
{
	int			endstate;

	if (vecstr_len(&line->cmd) == line->multiline_len)
	{
		if (line->multiline_len > 0)
		{
			endstate = get_endstate(&line->cmd);
			if (endstate == INDOUBLEQUOTE)
				ft_printf_fd(STDERR, "msh: unexpected EOF while looking for"
						"matching `\"\'\n");
			else
				ft_printf_fd(STDERR, "msh: unexpected EOF while looking for"
						"matching `\'\'\n");
			line->cursor.row += 1;
			if (line->cursor.row >= line->max.row)
				line->cursor.row -= 1;
			line->multiline_len = 0;
			line->promptlen = ft_no_ansi_strlen(line->prompt);
			clear_input(line, buf);
			return (0);
		}
		ft_printf("exit\n");
		return (CTRL_D);
	}
	return (0);
}
