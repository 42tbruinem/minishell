/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_right.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:38:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:08:37 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_term.h>

void	cursor_right(t_line *line)
{
	if (line->inputrow * line->max.col + (line->cursor.col + 1) >
			vecstr_len(&line->cmd) - line->multiline_len + line->promptlen)
		return ;
	line->cursor.col++;
	if (line->cursor.col >= line->max.col)
	{
		line->cursor.col = 0;
		line->cursor.row++;
		line->inputrow++;
	}
}
