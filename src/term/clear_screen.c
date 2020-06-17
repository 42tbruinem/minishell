/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_screen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 14:54:16 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

int		clear_screen(t_line *line, char buf[6])
{
	size_t		index;

	index = line->inputrow * line->max.col + line->cursor.col - line->promptlen;
	(void)buf;
	termcmd(CLEAR_SCREEN, 0, 0, 1);
	termcmd(MOVE_COLROW, 0, 0, 1);
	if (line->multiline_len > 0)
	{
		ft_printf("%s%s", line->multiline_prompt, vecstr_get(&line->cmd) +
				line->multiline_len);
		line->promptlen = ft_strlen(line->multiline_prompt);
	}
	else
	{
		ft_printf("%s%s", line->prompt, vecstr_get(&line->cmd));
		line->promptlen = ft_no_ansi_strlen(line->prompt);
	}
	line->cursor.row = line->inputrow;
	line->cursor.col = (index + line->promptlen) % (line->max.col);
	return (0);
}
