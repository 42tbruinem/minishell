/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   refresh_cursor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 13:02:50 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/29 13:56:16 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_term.h"

void	refresh_cursor(t_line *line)
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
	if (line->cursor.row >= line->max.row && g_siggy == 0)
	{
		line->cursor.row -= 1;
		termcmd(MOVE_COLROW, 0, line->max.row, 1);
		termcmd(SCROLL_LINE, 0, 0, 1);
	}
	termcmd(MOVE_COLROW, line->cursor.col, line->cursor.row, 1);
}
