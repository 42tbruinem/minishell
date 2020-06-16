/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:59:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:52:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>
#include <msh_term.h>

int		char_input(t_line *line, char buf[6])
{
	size_t		i;

	i = 1;
	if (buf[0] >= 32 && buf[0] <= 126)
		if (add_char(line, buf[0]) == -1)
			return (-1);
	while (buf[i])
	{
		refresh_cursor(line);
		if (!(buf[i] >= 32 && buf[i] <= 126))
		{
			handle_input(line, buf);
			break ;
		}
		if (add_char(line, buf[i]) == -1)
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
