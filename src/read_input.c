/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/18 22:24:12 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

#include <termcap.h>

#include <termios.h>

static char	*ft_realloc(char *str, int change)
{
	char	*new;

	new = (char *)ft_calloc(ft_strlen(str) + change + 1, 1);
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new, str, ft_strlen(str) + change + 1);
	free(str);
	return (new);
}

void	refresh(t_line *line)
{
	int		i;

	i = 0;
	tputs(tgetstr("sc", NULL), 1, &ft_putchar);
	while (i < line->cursor.row)
	{
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);
		tputs(tgetstr("up", NULL), 1, &ft_putchar);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, &ft_putchar);
	ft_printf("%s%s", line->prompt, line->cmd);
	tputs(tgetstr("rc", NULL), 1, &ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), line->cursor.row, line->cursor.col),
			1, &ft_putchar);
}

int		add_char(t_line *line, char buf[6])
{
	line->cmd = ft_realloc(line->cmd, 1);
	if (!line->cmd)
		return (-1);
	line->cmd[line->cmd_len] = buf[0];
	line->cmd[line->cmd_len + 1] = '\0';
	line->cmd_len++;
	line->cursor.col++;
	if (line->cursor.col >= line->max.col)
	{
		line->cursor.col = 0;
		line->cursor.row++;
	}
	refresh(line);
	return (0);
}

int		delete_char(t_line *line)
{
	if (line->cmd_len == 0)
		return (0);
	line->cmd = ft_realloc(line->cmd, -1);
	if (!line->cmd)
		return (-1);
	line->cmd_len--;
	line->cursor.col--;
	if (line->cursor.col < 0)
	{
		line->cursor.col = line->max.col;
		line->cursor.row--;
	}
	refresh(line);
	return (0);
}

int		cursor_move_or_history(t_line *line, int c)
{
	if (c == RIGHT_KEY)
	{
		line->cursor.col++;
		if (line->cursor.col >= line->max.col)
		{
			line->cursor.col = 0;
			line->cursor.row++;
		}
	}
	if (c == LEFT_KEY)
	{
		line->cursor.col--;
		if (line->cursor.col < 0)
		{
			line->cursor.col = line->max.col;
			line->cursor.row--;
		}
	}
	return (0);
}

int		esc_cursor_or_history(t_line *line, char buf[6])
{
	if (buf[1] == 0)
	{}// Toggle ESC mode - delete whole of cmd if backspace pressed
	else if (buf[4] != 0)
	{}// CTRL-ARROW pressed - more complicated cursor movement
	else
		return(cursor_move_or_history(line, buf[2]));
	return (0);
}

int		handle_in(t_line *line, char buf[6])
{
	if (ft_isalnum(buf[0]) || buf[0] == ' ')
		if(add_char(line, buf) == -1)
			return (-1);
	if (buf[0] == DEL)
		if(delete_char(line) == -1)
			return (-1);
	if (buf[0] == ESC)
		if(esc_cursor_or_history(line, buf) == -1)
			return (-1);
	/* ft_printf("entered key = {%d,%d,%d,%d,%d,%d}\n", buf[0], buf[1], buf[2], */
	/* 		buf[3], buf[4], buf[5]); */
	return (0);
}

int		read_input(t_line *line, t_msh *prog)
{
	char		buf[6];
	int			send;

	line->cursor.col = line->promptlen;
	line->cursor.row = 0;
	tputs(tgoto(tgetstr("ch", NULL), 0, line->cursor.col), 1, &ft_putchar);
	line->cmd_len = 0;
	send = 0;
	(void)prog;
	refresh(line);
	while (!send)
	{
		ft_bzero(buf, 6);
		read(STDIN, buf, 6);
		send = handle_in(line, buf);
		refresh(line);
	}
	return (0);
}
