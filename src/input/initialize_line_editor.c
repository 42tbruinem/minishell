/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_line_editor.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 12:57:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 17:30:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	get_col(int row)
{
	char		buf[10];
	int			col;

	col = 0;
	ft_printf_fd(STDOUT, "\033[6n");
	read(STDIN, buf, 10);
	if (row < 10)
		col = ft_atoi(buf + 4);
	else if (row >= 10 && row < 100)
		col = ft_atoi(buf + 5);
	else if (row > 100)
		col = ft_atoi(buf + 6);
	return (col);
}

static int	get_row(void)
{
	char		buf[10];
	int			row;

	ft_printf_fd(STDOUT, "\033[6n");
	read(STDIN, buf, 10);
	row = ft_atoi(buf + 2);
	return (row);
}

int			initialize_line_editor(t_line *line)
{
	line->cursor.row = get_row() - 1;
	line->cursor.col = get_col(line->cursor.row + 1) - 1;
	line->promptlen = line->cursor.col;
	line->total_rows = 0;
	line->inputrow = 0;
	line->escmode = 0;
	g_current_line = line->inputrow;
	g_total_lines = line->total_rows;
	return (0);
}
