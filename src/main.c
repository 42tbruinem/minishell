/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/05 19:06:54 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <fcntl.h>
#include <stdio.h>

char	**g_termbuff;

void	redirection_apply(char **args, int *inout)
{
	int			fds[100];
	size_t		i;
	size_t		fd_index;

	i = 0;
	fd_index = 0;
	while (args[i])
	{
//		ft_printf("%ld | %s\n", i, args[i]);
		if (ft_strncmp(args[i], ">>", 3) == 0)
		{
			if (args[i + 1])
			{
				fds[fd_index] = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND);
				inout[WRITE] = fds[fd_index];
				dprintf(2, ">> detected, setting OUT.\n");
				args[i] = NULL;
				args[i + 1] = NULL;
				i++;
				fd_index++;
			}
			else
				break ;
		}
		else if (ft_strncmp(args[i], ">", 2) == 0)
		{
			if (args[i + 1])
			{
				fds[fd_index] = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC);
				inout[WRITE] = fds[fd_index];
				dprintf(2, "> detected, setting OUT.\n");
				//free(args[i]);
				args[i] = NULL;
				//free(args[i + 1]);
				args[i + 1] = NULL;
				i++;
				fd_index++;
			}
			else
				break ;
		}
		else if (ft_strncmp(args[i], "<", 2) == 0)
		{
			if (args[i + 1])
			{
				fds[fd_index] = open(args[i + 1], O_RDONLY);
				inout[READ] = fds[fd_index];
				dprintf(2, "< detected, setting IN.\n");
				args[i] = NULL;
				args[i + 1] = NULL;
				i++;
				fd_index++;
			}
			else
				break ;
		}
		i++;
	}
}

void	in_out_redirection(t_msh *prog, int *pipe, t_cmd *command)
{
	int			inout[2];

	inout[READ] = 0;
	inout[WRITE] = 0;
	if (command->type == PIPE)
		inout[READ] = pipe[READ];
	if (command->next && command->next->type == PIPE)
		inout[WRITE] = pipe[WRITE];
	redirection_apply(command->args, inout);
	if (inout[READ])
		if (dup2(inout[READ], STDIN) == -1)
			error_exit(prog, 1);
	if (inout[WRITE])
		if (dup2(inout[WRITE], STDOUT) == -1)
			error_exit(prog, 1);
}

int		run_commands(t_msh *prog, t_cmd *commands, t_var *env)
{
	int	redir_pipe[2];
	static	int stdfdsave[2];

	if (!stdfdsave[STDIN])
		if (dup(STDIN) == -1)
			error_exit(prog, 1);
	if (!stdfdsave[STDOUT])
		if (dup(STDOUT) == -1)
			error_exit(prog, 1);
	if (pipe(redir_pipe) == -1)
		std_exit(prog);
	while (commands)
	{
		in_out_redirection(prog, redir_pipe, commands);
		print_command(commands);
		(void)execute(prog, commands->args, env);
		dup2(stdfdsave[STDIN], STDIN);
		dup2(stdfdsave[STDOUT], STDOUT);
		commands = commands->next;
	}
	return (1);
}

int			checkstate(int state, int c, int escape)
{
	if (escape == 1)
		return (state);
	if (state == NORMAL)
	{
		if (c == '\"')
			return (INDOUBLEQUOTE);
		if (c == '\'')
			return (INSINGLEQUOTE);
		if (c == '`')
			return (INBACKTICK);
	}
	if (state == INDOUBLEQUOTE && c == '\"')
		return (NORMAL);
	if (state == INSINGLEQUOTE && c == '\'')
		return (NORMAL);
	if (state == INBACKTICK && c == '`')
		return (NORMAL);
	return (state);
}

size_t			sum_tokens(char *line, int *state)
{
	size_t		i;
	int			inwhitespace;
	size_t		sum;
	int			escape;
	int			prevstate;

	i = 0;
	inwhitespace = 1;
	sum = 0;
	escape = 0;
	while (line[i])
	{
		prevstate = *state;
		*state = checkstate(*state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (*state != NORMAL && prevstate == NORMAL)
			sum++;
		if (!escape && !ft_is_whitespace(line[i]) && inwhitespace == 1 &&
				*state == NORMAL && prevstate == NORMAL)
		{
			sum++;
			inwhitespace = 0;
		}
		if (!escape && ft_is_whitespace(line[i]) && inwhitespace == 0 && *state
				== NORMAL)
			inwhitespace = 1;
		escape = 0;
		i++;
	}
	return (sum);
}

void		gen_tokens(int *state, char *line, t_ryantok **tokens)
{
	size_t		i;
	int			inwhitespace;
	int			escape;
	size_t		tokeni;

	i = 0;
	inwhitespace = 1;
	tokeni = 0;
	escape = 0;
	while (line[i])
	{
		*state = checkstate(*state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (*state != NORMAL)
		{
			line[i] = '\0';
			i++;
			if (!line[i])
				return ;
			(*tokens)[tokeni].value = line + i;
			tokeni++;
			*state = checkstate(*state, line[i], escape);
			while (line[i])
			{
				if (line[i] == '\\' && escape == 0)
				{
					escape = 1;
					i++;
					continue ;
				}
				*state = checkstate(*state, line[i], escape);
				if (*state == NORMAL)
					break ;
				i++;
				escape = 0;
			}
			line[i] = '\0';
		}
		else if (!ft_is_whitespace(line[i]) && inwhitespace == 1)
		{
			(*tokens)[tokeni].value = line + i;
			tokeni++;
			inwhitespace = 0;
		}
		else if (ft_is_whitespace(line[i]) && inwhitespace == 0)
		{
			line[i] = '\0';
			inwhitespace = 1;
		}
		escape = 0;
		i++;
	}
	(*tokens)[tokeni].value = NULL;
}

void		concatenate_quotes(char *line)
{
	size_t		i;
	int			state;
	int			prevstate;
	int			escape;
	size_t		j;

	i = 0;
	state = NORMAL;
	escape = 0;
	while (line[i])
	{
		prevstate = state;
		state = checkstate(state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (prevstate == NORMAL && state != NORMAL)
			j = i;
		if (!escape && (line[i] == '\"' || line[i] == '\'') && state == NORMAL)
			if (line[i + 1] == '\"' || line[i + 1] == '\'')
			{
				(*ft_strchr(line + i + 2, line[i + 1])) = line[i];
				ft_memmove(line + i, line + i + 2, ft_strlen(line + i + 2));
				j = ft_strlen(line);
				line[j - 1] = '\0';
				line[j - 2] = '\0';
				i = 0;
				continue ;
			}
		escape = 0;
		i++;
	}
}

void		concatenate_non_spaces(char *line)
{
	size_t		i;
	int			state;
	int			prevstate;
	int			escape;
	size_t		j;
	unsigned char		c;

	i = 0;
	state = NORMAL;
	escape = 0;
	while (line[i])
	{
		prevstate = state;
		state = checkstate(state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (prevstate == NORMAL && state != NORMAL)
			j = i;
		if (!escape && state == NORMAL && (prevstate == INDOUBLEQUOTE ||
					prevstate == INSINGLEQUOTE))
			if (line[i + 1] && !ft_is_whitespace(line[i + 1]))
			{
				c = line[i];
				if (!ft_strchr(line + i + 1, ' '))
				{
					j = ft_strchr(line + i + 1, line[i]) - line - 1;
					ft_memmove(line + i, line + i + 1, ft_strlen(line + i + 1));
					ft_memmove(line + j, line + j + 1, ft_strlen(line + j + 1));
					j = ft_strlen(line);
					line[j - 1] = '\0';
					line[j - 2] = '\0';
					continue ;
				}
				j = ft_strchr(line + i + 1, ' ') - line - 1;
				ft_memmove(line + i, line + i + 1, j - i);
				line[j] = c;
				state = (prevstate == INDOUBLEQUOTE) ? INDOUBLEQUOTE :
					INSINGLEQUOTE;
			}
		concatenate_quotes(line);
		escape = 0;
		i++;
	}
}
/* "e"c"h"'o 'hello "th"er"e" */

void		remove_escapes(char *line)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			len = ft_strlen(line);
			ft_memmove(line + i, line + i + 1, ft_strlen(line + i + 1));
			line[len - 1] = '\0';
		}
		i++;
	}
}

void		tokenizer(char *line)
{
	int				state;
	/* size_t		i; */
	t_ryantok		*tokens;
	size_t			totaltokens;

	/* i = 0; */
	/* concatenate_quotes(line); */
	/* ft_printf("after quote concat = %s\n", line); */
	concatenate_non_spaces(line);
	ft_printf("after non-space concat = %s\n", line);
	state = NORMAL;
	totaltokens = sum_tokens(line, &state);
	ft_printf("sum = %u\n", totaltokens);
	tokens = (t_ryantok *)malloc(sizeof(t_ryantok) * (totaltokens + 1));
	state = NORMAL;
	gen_tokens(&state, line, &tokens);
	ft_printf("after token generation = %s\n", line);

	size_t		i = 0;
	while (i < totaltokens)
	{
		remove_escapes(tokens[i].value);
		ft_printf("%s\n", tokens[i].value);
		i++;
	}
}

int	msh_main(t_msh *prog)
{
	/* t_cmd	*commands; */
	int		status;
	char	buf[8];

	status = 1;
	init_readline(prog);
	while (status)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		tokenizer(prog->line.cmd);
		/* commands = get_commands(tokenize(prog->line.cmd)); */
		/* status = run_commands(prog, commands, prog->env); */
	/* This helps calibrate cursor following command output for some reason */
		ft_printf_fd(STDOUT, "\033[6n");
		read(STDIN, buf, 8);
	}
	std_exit(prog);
	return (0);
}

int	main(void)
{
	t_msh	prog;

	env_init(&prog);
	return (msh_main(&prog));
}
