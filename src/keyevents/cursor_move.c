/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 15:04:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

int		cursor_move(t_line *line, int c)
{
	if (c == HOME)
		cursor_home(line);
	if (c == END)
		cursor_end(line);
	if (c == RIGHT_KEY)
		cursor_right(line);
	if (c == LEFT_KEY)
		cursor_left(line);
	return (0);
}
