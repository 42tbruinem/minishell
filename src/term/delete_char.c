/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_char.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:37:30 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 12:14:53 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

/*
** delete_char() will reallocate a new length for the command string, and
** remove the last character from it.
*/

static void	visual_delete(t_line *line)
{
	size_t	row;
	size_t	index;

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
		if (index > vecstr_len(&line->cmd))
			break ;
		termcmd(INSERT_START, 0, 0, 1);
		ft_printf("%c", vecstr_val(&line->cmd, index));
		termcmd(INSERT_END, 0, 0, 1);
		row++;
	}
}

int			delete_char(t_line *line)
{
	size_t		index;

	index = line->inputrow * line->max.col + line->cursor.col - line->promptlen;
	if (line->inputrow == 0 && line->cursor.col == (int)line->promptlen)
		return (0);
	if (vecstr_slice(&line->cmd, index - 1,
				index))
		return (-1);
	line->total_rows = (vecstr_len(&line->cmd) + line->promptlen) /
		line->max.col;
	if (line->cursor.col == 0)
	{
		line->inputrow--;
		line->cursor.col = line->max.col - 1;
		line->cursor.row--;
	}
	else
		line->cursor.col--;
	termcmd(MOVE_COLROW, line->cursor.col, line->cursor.row, 1);
	termcmd(DELETE_START, 0, 0, 1);
	termcmd(DELETE_CHAR, 0, 0, 1);
	termcmd(DELETE_END, 0, 0, 1);
	visual_delete(line);
	return (0);
}
