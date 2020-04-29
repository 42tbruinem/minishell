/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tc_funcs1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:59:21 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/29 16:46:26 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include "msh_term.h"

/*
** add_char() will reallocate a new length for the command string, then
** add the newly input character to it.
*/

int		insert_char(t_line *line, char c)
{
	size_t	index;

	if (line->cmd_len > line->alloced_cmd - 1)
	{
		line->alloced_cmd += 100;
		line->cmd = ft_realloc(line->cmd, line->alloced_cmd);
		if (!line->cmd)
			return (-1);
	}
	index = line->inputrow * line->max.col + line->cursor.col - line->promptlen;
	ft_memmove(line->cmd + index + 1, line->cmd + index,
			line->alloced_cmd - index);
	line->cmd[index] = c;
	return (0);
}

int		add_char(t_line *line, char c)
{
	size_t		row;
	size_t		index;

	if (c == '\n')
		c = ' ';

	// Increase length of command string
	line->cmd_len++;

	// Assign total rows that command spans
	line->total_rows = (line->cmd_len + line->promptlen) / line->max.col;

	// Internal component - change stored array values.
	if (insert_char(line, c) == -1)
		return (-1);

	// Display component - cursor should already be at relevant position. Enter
	// insert mode and print new character to screen.
	termcmd(INSERT_START, 0, 0, 1);
	ft_printf("%c", c);
	termcmd(INSERT_END, 0, 0, 1);

	// Wrapping - If the current row is not the last line of input, then go
	// to the start of every following row, and enter the LAST char of the
	// previous row.
	row = line->inputrow;
	while (row < line->total_rows)
	{
		termcmd(MOVE_COLROW, 0, line->cursor.row - line->inputrow + row + 1, 1);
		index = row * line->max.col + line->max.col - line->promptlen;
		if (index > line->cmd_len)
			break ;
		if (line->cmd[index] >= 32 && line->cmd[index] <= 126)
		{
			termcmd(INSERT_START, 0, 0, 1);
			ft_printf("%c", line->cmd[index]);
			termcmd(INSERT_END, 0, 0, 1);
		}
		row++;
	}

	// Cursor management - move cursor to the right. If it goes to the next
	// line, then change the value of inputrow, reset column, and move cursor
	// to next row.
	line->cursor.col++;
	if (line->cursor.col >= line->max.col)
	{
		line->cursor.col = 0;
		line->cursor.row++;
		line->inputrow++;
	}
	return (0);
}

/*
** delete_char() will reallocate a new length for the command string, and
** remove the last character from it.
*/

void	remove_char(t_line *line)
{
	size_t		index;

	index = line->inputrow * line->max.col + line->cursor.col - line->promptlen;
	ft_memmove(line->cmd + index, line->cmd + index + 1, line->alloced_cmd -
			index - 1);
}

int		delete_char(t_line *line)
{
	size_t		row;
	size_t		index;

	// Check if our command is already 0.
	if (line->inputrow == 0 && line->cursor.col == line->promptlen)
		return (0);

	// Decrease length of command.
	line->cmd_len--;

	// Assign total rows that command spans
	line->total_rows = (line->cmd_len + line->promptlen) / line->max.col;

	// Move cursor, to previous row if at start of row.
	if (line->cursor.col == 0)
	{
		line->inputrow--;
		line->cursor.col = line->max.col - 1;
		line->cursor.row--;
	}
	else
		line->cursor.col--;

	// Internal component - remove character from stored array.
	remove_char(line);

	// Display component - Delete character from terminal display.
	termcmd(MOVE_COLROW, line->cursor.col, line->cursor.row, 1);
	termcmd(DELETE_START, 0, 0, 1);
	termcmd(DELETE_CHAR, 0, 0, 1);
	termcmd(DELETE_END, 0, 0, 1);

	row = line->inputrow;
	while (row < line->total_rows)
	{
		termcmd(MOVE_COLROW, 0, line->cursor.row - line->inputrow + row + 1, 1);
		termcmd(DELETE_START, 0, 0, 1);
		termcmd(DELETE_CHAR, 0, 0, 1);
		termcmd(DELETE_END, 0, 0, 1);
		termcmd(MOVE_COLROW, line->max.col, line->cursor.row - line->inputrow +
				row, 1);
		index = row * line->max.col + line->max.col - line->promptlen - 1;
		if (index > line->cmd_len)
			break ;
		termcmd(INSERT_START, 0, 0, 1);
		ft_printf("%c", line->cmd[index]);
		termcmd(INSERT_END, 0, 0, 1);
		row++;
	}
	return (0);
}

/*
** cursor_left() moves the cursor one position to the left
*/

int		cursor_left(t_line *line)
{
	if (line->inputrow == 0 && line->cursor.col == line->promptlen)
		return (0);
	if (line->cursor.col == 0)
	{
		line->inputrow--;
		line->cursor.col = line->max.col - 1;
		line->cursor.row--;
	}
	else
		line->cursor.col--;
	return 3;
}

int		cursor_right(t_line *line)
{
	if (line->inputrow * line->max.col + (line->cursor.col + 1) > line->cmd_len
			+ line->promptlen)
		return (0);
	line->cursor.col++;
	if (line->cursor.col >= line->max.col)
	{
		line->cursor.col = 0;
		line->cursor.row++;
		line->inputrow++;
	}
	return (0);
}
