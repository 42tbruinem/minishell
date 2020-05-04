/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/04 21:25:28 by tbruinem      ########   odam.nl         */
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
				free(args[i]);
				args[i] = NULL;
				free(args[i + 1]);
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
				free(args[i]);
				args[i] = NULL;
				free(args[i + 1]);
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
				free(args[i]);
				args[i] = NULL;
				free(args[i + 1]);
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
	if (command->cmdtype == PIPE)
		inout[READ] = pipe[READ]; //need one pipe per chain (A | B) = 1 (A | B | C) would need 2 pipes.
	if (command->next && command->next->cmdtype == PIPE)
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

int	msh_main(t_msh *prog)
{
	int		status;
	char	buf[8];

	status = 1;
	init_readline(prog);
	while (status)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		if (!tokenize(&prog->args, &prog->argtypes, prog->line.cmd))
			error_exit(NULL, MEM_FAIL);
		prog->commands = get_commands(&prog->args, &prog->argtypes);
		if (!prog->commands)
			error_exit(NULL, MEM_FAIL);
		status = run_commands(prog, prog->commands, prog->env);
	/* Requests a Report Cursor Position response from the device */
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
