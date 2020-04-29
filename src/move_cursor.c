/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:38:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/29 19:22:34 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cursor_home(t_line *line)
{
	line->cursor.col = line->promptlen;
	line->cursor.row = line->cursor.row - line->inputrow;
	line->inputrow = 0;
}

void	cursor_end(t_line *line)
{
	line->cursor.row = line->cursor.row - line->inputrow + line->total_rows;
	line->cursor.col = (line->cmd_len + line->promptlen) % line->max.col;
	line->inputrow = line->total_rows;
}

/*
** cursor_left() moves the cursor one position to the left
*/

void	cursor_left(t_line *line)
{
	if (line->inputrow == 0 && line->cursor.col == line->promptlen)
		return ;
	if (line->cursor.col == 0)
	{
		line->inputrow--;
		line->cursor.col = line->max.col - 1;
		line->cursor.row--;
	}
	else
		line->cursor.col--;
}

void	cursor_right(t_line *line)
{
	if (line->inputrow * line->max.col + (line->cursor.col + 1) > line->cmd_len
			+ line->promptlen)
		return ;
	line->cursor.col++;
	if (line->cursor.col >= line->max.col)
	{
		line->cursor.col = 0;
		line->cursor.row++;
		line->inputrow++;
	}
}
