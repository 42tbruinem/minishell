/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_screen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:56:26 by tbruinem      ########   odam.nl         */
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
	ft_printf("%s%s", line->prompt, vecstr_get(&line->cmd));
	line->cursor.row = line->inputrow;
	line->promptlen = ft_no_ansi_strlen(line->prompt);
	line->cursor.col = (index + line->promptlen) % (line->max.col);
	return (0);
}
