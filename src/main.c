/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/05 14:18:56 by rlucas        ########   odam.nl         */
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

int			checkstate(int state, int c)
{
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

	i = 0;
	inwhitespace = 1;
	sum = 0;
	while (line[i])
	{
		*state = checkstate(*state, line[i]);
		if (*state != NORMAL)
		{
			i++;
			if (!line[i])
				return (sum);
			sum++;
			*state = checkstate(*state, line[i]);
			while (*state != NORMAL && line[i])
			{
				i++;
				*state = checkstate(*state, line[i]);
				if (*state == NORMAL && line[i + 1])
					*state = checkstate(*state, line[i + 1]);
			}
		}
		if (!ft_is_whitespace(line[i]) && inwhitespace == 1)
		{
			sum++;
			inwhitespace = 0;
		}
		if (ft_is_whitespace(line[i]) && inwhitespace == 0)
			inwhitespace = 1;
		i++;
	}
	return (sum);
}

void		gen_tokens(int *state, char *line, t_ryantok **tokens)
{
	size_t		i;
	int			inwhitespace;
	size_t		tokeni;

	i = 0;
	inwhitespace = 1;
	tokeni = 0;
	while (line[i])
	{
		*state = checkstate(*state, line[i]);
		if (*state != NORMAL)
		{
			line[i] = '\0';
			i++;
			if (!line[i])
				return ;
			(*tokens)[tokeni].value = line + i;
			tokeni++;
			*state = checkstate(*state, line[i]);
			while (*state != NORMAL && line[i])
			{
				i++;
				*state = checkstate(*state, line[i]);
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
		i++;
	}
	(*tokens)[tokeni].value = NULL;
}

void		concatenate_quotes(char *line)
{
	size_t		i;
	int			state;
	int			prevstate;
	size_t		j;

	i = 0;
	state = NORMAL;
	while (line[i])
	{
		prevstate = state;
		state = checkstate(state, line[i]);
		if (prevstate == NORMAL && state != NORMAL)
			j = i;
		if ((line[i] == '\"' || line[i] == '\'') && state == NORMAL)
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
		i++;
	}
}

void		concatenate_non_spaces(char *line)
{
	size_t		i;
	int			state;
	int			prevstate;
	size_t		j;

	i = 0;
	state = NORMAL;
	while (line[i])
	{
		prevstate = state;
		state = checkstate(state, line[i]);
		if (prevstate == NORMAL && state != NORMAL)
			j = i;
		if (state == NORMAL && (prevstate == INDOUBLEQUOTE || prevstate ==
					INSINGLEQUOTE))
			if (line[i + 1] && !ft_is_whitespace(line[i + 1]))
			{
				ft_memmove(line + i, line + i + 1, ft_strlen(line + i + 1));
				ft_memmove(line + j, line + j + 1, ft_strlen(line + j + 1));
				j = ft_strlen(line);
				line[j - 1] = '\0';
				line[j - 2] = '\0';
				continue ;
			}
		i++;
	}
}

void		tokenizer(char *line)
{
	int				state;
	/* size_t		i; */
	/* t_ryantok		*tokens; */
	size_t			totaltokens;

	/* i = 0; */
	concatenate_quotes(line);
	ft_printf("after quote concat = %s\n", line);
	concatenate_non_spaces(line);
	ft_printf("after non-space concat = %s\n", line);
	state = NORMAL;
	totaltokens = sum_tokens(line, &state);
	ft_printf("sum = %u\n", totaltokens);
	/* tokens = (t_ryantok *)malloc(sizeof(t_ryantok) * (totaltokens + 1)); */
	/* state = NORMAL; */
	/* gen_tokens(&state, line, &tokens); */
    /*  */
	/* size_t		i = 0; */
	/* while (i < totaltokens) */
	/* { */
	/* 	ft_printf("%s\n", tokens[i].value); */
	/* 	i++; */
	/* } */
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
