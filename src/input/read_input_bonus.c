/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/28 20:47:03 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>
#include <msh_lex.h>
#include <errno.h>

static int	signal_received(t_line *line, t_msh *prog)
{
	if (line->multiline_len > 0)
	{
		line->multiline_len = 0;
		line->promptlen = ft_no_ansi_strlen(line->prompt);
	}
	prog->exit_status = 1;
	if (vecstr_reset(&line->cmd))
		return (0);
	line->cursor.row += g_siggy +
		(line->promptlen + vecstr_len(&line->cmd)) / line->max.col;
	if (line->cursor.row >= line->max.row)
		line->cursor.row = line->max.row - 1;
	line->cursor.col = line->promptlen;
	line->promptlen = ft_no_ansi_strlen(line->prompt);
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

static int	check_multiline(t_msh *prog, t_line *line)
{
	int			endstate;

	endstate = get_endstate(&line->cmd);
	if (endstate == INDOUBLEQUOTE || endstate == INSINGLEQUOTE ||
			endstate == PIPE_PIPE)
	{
		if (add_char(line, '\n') == -1)
			error_exit(prog, MEM_FAIL);
		line->multiline_len = vecstr_len(&line->cmd);
		line->total_rows = 0;
		line->inputrow = 0;
		line->promptlen = ft_strlen(line->multiline_prompt);
		line->cursor.row += 1;
		if (line->cursor.row >= line->max.row)
			line->cursor.row -= 1;
		line->cursor.col = line->promptlen;
		ft_printf("%s", line->multiline_prompt);
		refresh_cursor(line);
		return (0);
	}
	return (1);
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
		dprintf(2, "[%d][%d][%d][%d][%d][%d]\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		if (g_siggy > 0)
			if (!signal_received(line, prog))
				return (-1);
		if (finished(prog, line, buf))
			if (check_multiline(prog, line))
				break ;
	}
	line->cursor.row = line->cursor.row + line->total_rows + 1;
	line->cursor.col = 0;
	refresh_cursor(line);
	return (1);
}
