/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   special_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 14:41:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>
#include <msh_keyevents.h>

int		special_command(t_line *line, char buf[6])
{
	if (buf[1] == 127)
		if (delete_word(line) == -1)
			return (-1);
	if (buf[1] == 0)
		line->escmode = 1;
	else if (buf[4] == 53)
		cursor_move_word(line, buf[5]);
	else if (buf[4] == 50)
		cursor_move_row(line, buf[5]);
	else
		return (cursor_move(line, buf[2]));
	return (0);
}
