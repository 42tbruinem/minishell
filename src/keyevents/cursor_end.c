/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_end.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:38:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 14:59:10 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_term.h>

void	cursor_end(t_line *line)
{
	line->cursor.row = line->cursor.row - line->inputrow + line->total_rows;
	line->cursor.col = (vecstr_len(&line->cmd) - line->multiline_len +
			line->promptlen) % line->max.col;
	line->inputrow = line->total_rows;
}
