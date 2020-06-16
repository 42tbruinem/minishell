/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_home.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:38:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 15:01:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_term.h>

void	cursor_home(t_line *line)
{
	line->cursor.row = line->cursor.row - line->inputrow;
	line->cursor.col = line->promptlen;
	line->inputrow = 0;
}
