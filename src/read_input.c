/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/15 13:34:03 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include <termcap.h>
#include <termios.h>
#include "msh_term.h"
#include <errno.h>

static void	refresh_cursor(t_line *line)
{
	if (line->cursor.row < 0)
	{
		while (line->cursor.row < 0)
		{
			termcmd(MOVE_COLROW, 0, 0, 1);
			termcmd(SCROLL_UP, 0, 0, 1);
			line->cursor.row++;
		}
	}
	if (line->cursor.row >= line->max.row)
	{
		line->cursor.row -= 1;
		termcmd(SCROLL_LINE, 0, 0, 1);
	}
	termcmd(MOVE_COLROW, line->cursor.col, line->cursor.row, 1);
}

static int	get_col(int row)
{
	char		buf[10];
	int			col;

	col = 0;
	ft_printf_fd(STDOUT, "\033[6n");
	read(STDIN, buf, 10);
	if (row < 10)
		col = ft_atoi(buf + 4);
	else if (row > 10 && row < 100)
		col = ft_atoi(buf + 5);
	else if (row > 100)
		col = ft_atoi(buf + 6);
	return (col);
}

static int	get_row(void)
{
	char		buf[10];
	int			row;

	ft_printf_fd(STDOUT, "\033[6n");
	read(STDIN, buf, 10);
	row = ft_atoi(buf + 2);
	return (row);
}

static int	initialize_line_editor(t_line *line, int get_c_and_r)
{
	if (get_c_and_r)
	{
		line->cursor.row = get_row() - 1;
		line->cursor.col = get_col(line->cursor.row + 1) - 1;
	}
	line->promptlen = line->cursor.col;
	line->total_rows = 0;
	line->inputrow = 0;
	line->escmode = 0;
	g_current_line = line->inputrow;
	g_total_lines = line->total_rows;
	return (0);
}

int			read_input(t_msh *prog)
{
	t_line		*line;
	char		buf[6];
	int			send;

	line = &prog->line;
	ft_printf("%s", line->prompt);
	if (initialize_line_editor(line, 1) == -1)
		return (-1);
	send = 0;
	refresh_cursor(line);
	while (!send)
	{
		ft_bzero(buf, 6);
		read(STDIN, buf, 6);
		if (g_siggy == 1)
		{
			g_siggy = 0;
			/* line->cursor.row += line->total_rows - line->inputrow + 1; */
			/* line->promptlen = ft_no_ansi_strlen(line->prompt); */
			/* line->cursor.col = line->promptlen; */
			/* g_current_line = line->inputrow; */
			/* g_total_lines = line->total_rows; */
			line->cursor.row += line->total_rows - line->inputrow + 1;
			if (initialize_line_editor(line, 0) == -1)
				return (-1);
			line->promptlen = ft_no_ansi_strlen(line->prompt);
			line->cursor.col = line->promptlen;
			refresh_cursor(line);
			if (vecstr_truncate(&line->cmd, 0))
				return (-1);
		}
		send = handle_input(line, buf);
		if (send < 0)
			error_exit(prog, MEM_FAIL, IN_INPUT);
		if (send == CTRL_D)
			std_exit(prog);
		g_current_line = line->inputrow;
		g_total_lines = line->total_rows;
		refresh_cursor(line);
	}
	line->cursor.row = line->cursor.row + line->total_rows + 1;
	line->cursor.col = 0;
	refresh_cursor(line);
	return (1);
}
