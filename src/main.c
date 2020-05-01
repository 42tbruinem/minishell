/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/01 12:10:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <fcntl.h>

char	**g_termbuff;

void	redirection_apply(char **args)
{
	int			fds[100];
	size_t		i;
	size_t		fd_index;
	int			inout[2];

	i = 0;
	fd_index = 0;
	inout[0] = 0;
	inout[1] = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">>", 2) == 0)
		{
			if (args[i + 1])
			{
				fds[fd_index] = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND);
				inout[1] = fds[fd_index];
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
				inout[1] = fds[fd_index];
				args[i] = NULL;
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
				inout[0] = fds[fd_index];
				args[i] = NULL;
				args[i + 1] = NULL;
				i++;
				fd_index++;
			}
			else
				break ;
		}
		else
			i++;
	}
	if (inout[0])
		dup2(inout[0], STDIN);
	if (inout[1])
		dup2(inout[1], STDOUT);
}

void	in_out_redirection(t_msh *prog, int *pipe, t_cmd *command)
{
	static	int stdfdsave[2];

	if (!stdfdsave[STDIN])
		if (dup(STDIN) == -1)
			error_exit(prog, 1);
	if (!stdfdsave[STDOUT])
		if (dup(STDOUT) == -1)
			error_exit(prog, 1);
	dup2(stdfdsave[STDIN], STDIN);
	dup2(stdfdsave[STDOUT], STDOUT);
	if (command->type == PIPE)
		if (dup2(pipe[READ], STDIN) == -1)
			error_exit(prog, 1);
	if (command->next && command->next->type == PIPE)
		if (dup2(pipe[WRITE], STDOUT) == -1)
			error_exit(prog, 1);
	redirection_apply(command->args);
}

int		run_commands(t_msh *prog, t_cmd *commands, t_var *env)
{
	int	redir_pipe[2];

	if (pipe(redir_pipe) == -1)
		std_exit(prog);
	while (commands)
	{
//		print_command(commands);
		in_out_redirection(prog, redir_pipe, commands);
		(void)execute(prog, commands->args, env);
		commands = commands->next;
	}
	return (1);
}

int	msh_main(t_msh *prog)
{
	t_cmd	*commands;
	int		status;
	char	buf[8];

	status = 1;
	init_readline(prog);
	while (status)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		commands = get_commands(tokenize(prog->line.cmd));
		status = run_commands(prog, commands, prog->env);
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
