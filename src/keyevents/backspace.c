/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   backspace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:52:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

int		backspace(t_line *line, char buf[6])
{
	(void)buf;
	if (line->escmode == 1)
	{
		if (delete_word(line) == -1)
			return (-1);
		line->escmode = 0;
		return (0);
	}
	if (delete_char(line) == -1)
		return (-1);
	return (0);
}
