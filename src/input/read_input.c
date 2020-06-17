/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 11:03:06 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include <termcap.h>
#include <termios.h>
#include "msh_term.h"
#include <errno.h>

static int	signal_received(t_line *line)
{
	if (vecstr_reset(&line->cmd))
		return (0);
	line->cursor.row += g_siggy +
		(line->promptlen + vecstr_len(&line->cmd)) / line->max.col;
	if (line->cursor.row >= line->max.row)
		line->cursor.row = line->max.row - 1;
	line->cursor.col = line->promptlen;
	refresh_cursor(line);
	g_siggy = 0;
	return (1);
}

static int	finished(t_msh *prog, t_line *line, char *buf)
{
	int	send;

	send = handle_input(line, buf);
	if (send < 0)
		error_exit(prog, MEM_FAIL);
	if (send == CTRL_D)
		std_exit(prog, 0);
	g_current_line = line->inputrow;
	g_total_lines = line->total_rows;
	refresh_cursor(line);
	if (send)
		return (1);
	return (0);
}

int			read_input(t_msh *prog)
{
	t_line		*line;
	char		buf[6];

	line = &prog->line;
	ft_printf("%s", line->prompt);
	if (initialize_line_editor(line) == -1)
		return (-1);
	refresh_cursor(line);
	while (1)
	{
		ft_bzero(buf, 6);
		read(STDIN, buf, 6);
		if (g_siggy > 0)
			if (!signal_received(line))
				return (-1);
		if (finished(prog, line, buf))
			break ;
	}
	line->cursor.row = line->cursor.row + line->total_rows + 1;
	line->cursor.col = 0;
	refresh_cursor(line);
	return (1);
}
