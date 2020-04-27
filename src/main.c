/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/27 22:44:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <termcap.h>
#include <termios.h>

char	*ft_str3join(const char *s1, const char *s2, const char *s3)
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

	user = env_val_get("USER", prog->env);
	if (user != NULL)
	{
		line->promptlen = ft_strlen(user) + 4;
		prompt = ft_str3join("\033[32m", user, "\033[39m:~$ ");
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

int	init_term(struct termios *term)
{
	if (!isatty(STDIN) || tcgetattr(STDIN, term) < 0)
		return (1);
	/* term->c_iflag &= ~(INLCR) */
	term->c_iflag &= ~(IMAXBEL); //change certain attributes in termios 1/4
	/* INLCR - When \n is input, program recieves it as \r. */
	/* IMAXBEL - If input buffer is filled, send a BEL to the terminal. */
	term->c_lflag &= ~(ECHO | ICANON); //change certain attributes in termios 2/4
	/* ECHO - display input characters. */
	/* ICANON - NON-CANONICAL Input. This is required to allow our program to */
	/* 	control input editing facilities. */
	term->c_cc[VMIN] = 1; //change certain attributes in termios 3/4
	term->c_cc[VTIME] = 0; //change certain attributes in termios  4/4

	/* The change occurs after all output written to the file descriptor has been */
	/* 	transmitted, and all input so far received but not read is discarded */
	/* 	before the change is made */
	if (cfsetispeed(term, B9600) < 0 || cfsetospeed(term, B9600) < 0 ||
		tcsetattr(STDIN, TCSAFLUSH, term) < 0)
		return (1);
	return (0);
}

void	init_line(t_msh *prog, t_line *line)
{
	*line = (t_line){0};
	if (init_term(&line->term) || init_caps(line) == -1)
		error_exit(prog, CAP_FAIL);
	line->prompt = prompt(prog, line);
	line->max.col = tgetnum("co");
	ft_printf("maxcols = %d\n", line->max.col);
	line->max.row = tgetnum("li");
}

void	get_cmd(t_msh *prog, t_line *line)
{
	int	status;

	status = 1;
	while (status)
	{
		status = read_input(line, prog);
		/* status = exec_input(&input); */
	}
}

int	msh_main(t_msh *prog)
{
	t_line	line;
	t_token	*args;

	init_line(prog, &line);
	get_cmd(prog, &line);
	ft_printf("\nInput was: %s\n", line.cmd);
	args = tokenize(line.cmd);
	tokprint(args);
	std_exit(prog);
	return (0);
}

int	main(void)
{
	t_msh	prog;

	env_init(&prog);
	return (msh_main(&prog));
}
