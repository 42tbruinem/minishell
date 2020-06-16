/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:55:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

int		clear_input(t_line *line, char buf[6])
{
	(void)buf;
	if (vecstr_truncate(&line->cmd, 0))
		return (-1);
	line->cursor.row -= line->inputrow;
	while (line->total_rows > 0)
	{
		termcmd(MOVE_COLROW, 0, line->cursor.row + line->total_rows, 1);
		termcmd(DELETE_LINE, 0, 0, 1);
		line->total_rows--;
	}
	termcmd(MOVE_COLROW, 0, line->cursor.row + line->total_rows, 1);
	termcmd(DELETE_LINE, 0, 0, 1);
	ft_printf("%s", line->prompt);
	line->cursor.col = line->promptlen;
	line->inputrow = 0;
	return (0);
}
