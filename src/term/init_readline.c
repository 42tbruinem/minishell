/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_readline.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:17:50 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:43:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <libft.h>

static int	init_caps(t_line *line)
{
	line->termtype = getenv("TERM");
	if (!line->termtype)
		return (-1);
	if (tgetent(line->cap_table, line->termtype) != 1)
		return (-1);
	return (0);
}

static int	init_term(struct termios *term)
{
	if (!isatty(STDIN) || tcgetattr(STDIN, term) < 0)
		return (1);
	term->c_iflag &= ~(IMAXBEL);
	term->c_lflag &= ~(ECHO | ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (cfsetispeed(term, B9600) < 0 || cfsetospeed(term, B9600) < 0 ||
		tcsetattr(STDIN, TCSAFLUSH, term) < 0)
		return (1);
	return (0);
}

void		init_readline(t_msh *prog)
{
	prog->line = (t_line){0};
	if (init_term(&prog->line.term) || init_caps(&prog->line) == -1)
		error_exit(prog, CAP_FAIL, IN_TERM);
	prog->line.prompt = prompt(prog, &prog->line);
	if (!prog->line.prompt)
		error_exit(prog, MEM_FAIL, IN_TERM);
	if (vecstr_init(&prog->line.cmd))
		error_exit(prog, CAP_FAIL, IN_TERM);
	prog->line.max.col = tgetnum("co");
	prog->line.max.row = tgetnum("li");
}
