/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_move_row.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:38:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 15:01:21 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_term.h>

void	cursor_move_row(t_line *line, int c)
{
	if (c == DOWN_KEY)
	{
		if (line->inputrow == line->total_rows)
			return ;
		line->inputrow++;
		line->cursor.row++;
		if (line->inputrow * line->max.col + line->cursor.col - line->promptlen
				> vecstr_len(&line->cmd))
			cursor_end(line);
		return ;
	}
	if (c == UP_KEY)
	{
		if (line->inputrow == 0)
			return ;
		line->cursor.row--;
		line->inputrow--;
		if (line->inputrow * line->max.col + line->cursor.col < line->promptlen)
			cursor_home(line);
		return ;
	}
}
