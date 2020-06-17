/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 14:57:15 by rlucas        ########   odam.nl         */
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
	if (line->multiline_len > 0)
	{
		if (vecstr_truncate(&line->cmd, line->multiline_len))
			return (-1);
	}
	else if (vecstr_reset(&line->cmd))
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
	if (line->multiline_len == 0)
		ft_printf("%s", line->prompt);
	else
		ft_printf("%s", line->multiline_prompt);
	line->cursor.col = line->promptlen;
	line->inputrow = 0;
	return (0);
}
