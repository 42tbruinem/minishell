/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/30 14:23:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

typedef int		(*t_inputf)(t_line *line, char buf[6]);

int		send_EOF(t_line *line, char buf[6])
{
	(void)buf;
	if (line->cmd_len == 0)
	{
		ft_printf("exit\n");
		return (CTRL_D);
	}
	return (0);
}

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

int		special_command(t_line *line, char buf[6])
{
	if (buf[1] == 0)
		line->escmode = 1;
	else if (buf[4] != 0)
	{}// CTRL-ARROW pressed - more complicated cursor movement
	else
		return (cursor_move(line, buf[2]));
	return (0);
}

int		send_input(t_line *line, char buf[6])
{
	(void)line;
	(void)buf;
	return (1);
}

int		char_input(t_line *line, char buf[6])
{
	size_t		i;

	i = 1;
	if (add_char(line, buf[0]) == -1)
		return (-1);
	while (buf[i])
	{
		if (add_char(line, buf[0]) == -1)
			return (-1);
		i++;
		if (i == 6)
		{
			ft_bzero(buf, 6);
			read(STDIN, buf, 6);
			i = 0;
		}
	}
	return (0);
}

int		backspace(t_line *line, char buf[6])
{
	(void)buf;
	if (line->escmode == 1)
	{
		if (esc_delete(line) == -1)
			return (-1);
		line->escmode = 0;
		return (0);
	}
	if (delete_char(line) == -1)
		return (-1);
	return (0);
}
