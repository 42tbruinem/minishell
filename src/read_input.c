/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/23 22:46:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include <termcap.h>
#include <termios.h>

int		cursor_move_or_history(t_line *line, int c)
{
	if (c == RIGHT_KEY)
		cursor_right(line);
	if (c == LEFT_KEY)
		cursor_left(line, 0);
	return (0);
}

int		esc_cursor_or_history(t_line *line, char buf[6])
{
	if (buf[1] == 0)
	{}// Toggle ESC mode - delete whole of cmd if backspace pressed
	else if (buf[4] != 0)
	{}// CTRL-ARROW pressed - more complicated cursor movement
	else
		return(cursor_move_or_history(line, buf[2]));
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
		tputs(tgetstr("sf", NULL), 1, &ft_putchar);
		line->scroll = 0;
	}
	tputs(tgoto(tgetstr("ch", NULL), line->cursor.row, line->cursor.col),
			1, &ft_putchar);
}

int		read_input(t_line *line, t_msh *prog)
{
	char		buf[6];
	int			send;

	line->cursor.col = line->promptlen;
	line->cursor.row = 0;
	line->total_rows = 0;
	tputs(tgoto(tgetstr("ch", NULL), 0, line->cursor.col), 1, &ft_putchar);
	line->cmd_len = 0;
	send = 0;
	(void)prog;
	refresh(line);
	while (!send)
	{
		ft_bzero(buf, 6);
		read(STDIN, buf, 6);
		send = handle_in(line, buf);
		line->total_rows = (line->cmd_len + line->promptlen) / 88;
		refresh_cursor(line);
	}
	return (0);
}
