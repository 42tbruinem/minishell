/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/18 21:54:51 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

#include <termcap.h>
#include <termios.h>

static char	*ft_str3join(const char *s1, const char *s2, const char *s3)
{
	char		*newstring;

	if (!s1 || !s2 || !s3)
		return (NULL);
	newstring = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) +
			ft_strlen(s3) + 1, sizeof(char));
	if (!newstring)
		return (NULL);
	ft_strlcpy(newstring, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstring + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_strlcpy(newstring + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3) + 1);
	return (newstring);
}

char	*prompt(t_msh *prog, t_line *line)
{
	char	*user;
	char	*prompt;

	user = get_env_value("USER", prog->env);
	if (user != NULL)
	{
		line->promptlen = ft_strlen(user) + 4;
		prompt = ft_str3join("\033[32m", user, "\033[39m:~$ ");
		free(user);
		if (!prompt)
			return (NULL);
		return (prompt);
	}
	else
		return (ft_strdup(":~$ "));
}

static int	init_caps(t_line *line)
{
	line->cmd = ft_strdup("");
	if (!line->cmd)
		return (-1);
	line->termtype = getenv("TERM");
	if (!line->termtype)
		return (-1);
	if (tgetent(line->cap_table, line->termtype) != 1)
		return (-1);
	line->tableptr = line->cap_table;
	return (0);
}

static struct termios	*init_term(void)
{
	struct termios	*term;

	term = (struct termios *)ft_calloc(1, sizeof(struct termios));
	if (!term)
		return (NULL);
	if (!isatty(STDIN))
	{
		free(term);
		return (NULL);
	}
	if (tcgetattr(STDIN, term) < 0)
	{
		free(term);
		return (NULL);
	}
	/* term->c_iflag &= ~(INLCR) */
	term->c_iflag &= ~(IMAXBEL);
	/* INLCR - When \n is input, program recieves it as \r. */
	/* IMAXBEL - If input buffer is filled, send a BEL to the terminal. */
	term->c_lflag &= ~(ECHO | ICANON);
	/* ECHO - display input characters. */
	/* ICANON - NON-CANONICAL Input. This is required to allow our program to */
	/* 	control input editing facilities. */
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (cfsetispeed(term, B9600) < 0 || cfsetospeed(term, B9600) < 0)
	{
		free(term);
		return (NULL);
	}
	if (tcsetattr(STDIN, TCSAFLUSH, term) < 0)
	{
		free(term);
		return (NULL);
	}
	return (term);
}

int	msh_main(t_msh *prog)
{
	int		status;
	t_line	*line;

	line = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!line)
		error_exit(prog, MEM_FAIL);
	line->term = init_term();
	if (!line->term)
		error_exit(prog, TERM_FAIL);
	if (init_caps(line) == -1)
		error_exit(prog, CAP_FAIL);
	status = 1;
	line->prompt = prompt(prog, line);
	line->max.col = tgetnum("co");
	ft_printf("maxcols = %d\n", line->max.col);
	line->max.row = tgetnum("li");
	while (status)
	{
		status = read_input(line, prog);
		/* status = exec_input(&input); */
	}
	std_exit(prog);
	return (0);
}

int	main(void)
{
	t_msh	*prog;

	prog = (t_msh *)malloc(sizeof(t_msh));
	if (!prog)
		error_exit(prog, MEM_FAIL);
	init_env(prog);
	return (msh_main(prog));
}
