/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/28 02:14:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include <termcap.h>
#include <termios.h>
#include "msh_term.h"

void	termcmd(char *command, int p1, int p2, int lines_affected)
{
	tputs(tgoto(tgetstr(command, NULL), p1, p2),
		lines_affected, &ft_putchar);
}

int		cursor_move_or_history(t_line *line, int c)
{
	if (c == RIGHT_KEY)
		cursor_right(line);
	if (c == LEFT_KEY)
		cursor_left(line);
	return (0);
}

int		esc_cursor_or_history(t_line *line, char buf[6])
{
	if (buf[1] == 0)
	{}// Toggle ESC mode - delete whole of cmd if backspace pressed
	else if (buf[4] != 0)
	{}// CTRL-ARROW pressed - more complicated cursor movement
	else
		return (cursor_move_or_history(line, buf[2]));
	return (0);
}

int		handle_in(t_line *line, char buf[6])
{
	if (ft_isalnum(buf[0]) || buf[0] == ' ')
		if (add_char(line, buf) == -1)
			return (-1);
	if (buf[0] == DEL)
		if (delete_char(line) == -1)
			return (-1);
	if (buf[0] == ESC)
		if (esc_cursor_or_history(line, buf) == -1)
			return (-1);
	if (buf[0] == NEWLINE)
		return (1);
	/* ft_printf("entered key = {%d,%d,%d,%d,%d,%d}\n", buf[0], buf[1], buf[2], */
	/* 		buf[3], buf[4], buf[5]); */
	return (0);
}

void	refresh_cursor(t_line *line)
{
	if (line->scroll == SCROLLDOWN)
	{
		tputs(tgetstr(SCROLL_LINE, NULL), 1, &ft_putchar);
		line->scroll = 0;
	}
	termcmd(MOVE_COLROW, line->cursor.col, line->cursor.row, 1);
}

int		read_input(t_line *line, t_msh *prog)
{
	char		buf[6];
	int			send;

	line->cursor.col = line->promptlen;
	line->cursor.row = 0;
	line->total_rows = 0;
	send = 0;
	(void)prog;
	termcmd(CLEAR_SCREEN, 0, 0, 1);
	refresh(line);
	while (!send)
	{
		ft_bzero(buf, 6);
		read(STDIN, buf, 6);
		send = handle_in(line, buf);
		refresh_cursor(line);
		line->total_rows = (line->cmd_len + line->promptlen) /
			(line->max.col);
	}
	line->total_rows = (line->cmd_len + line->promptlen) /
		(line->max.col);
	line->cursor.row = line->total_rows + 1;
	return (0);
}
