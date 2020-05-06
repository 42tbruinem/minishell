/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/06 11:05:16 by tbruinem      ########   odam.nl         */
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

int		in_out_redirection(t_msh *prog, t_cmd *command)
{
	command->iostream[0] = -1;
	command->iostream[1] = -1;
	if (command->cmdtype == PIPE)
		command->iostream[READ] = command->cmdpipe[READ];
	if (command->next && command->next->cmdtype == PIPE)
		command->iostream[WRITE] = command->next->cmdpipe[WRITE];
	if (!set_redirection(command, command->args,
		command->argtypes, &prog->file_arr))
		return (0);
	return (1);
}

int		run_commands(t_msh *prog, t_cmd *commands)
{
	print_filearr(&prog->file_arr);
	while (commands)
	{
		if (!in_out_redirection(prog, commands))
			return (0);
		print_command(commands);
		(void)execute(prog, commands);
		commands = commands->next;
	}
	vec_destroy(&prog->file_arr, NULL);
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
		prog->commands = get_commands((char **)prog->args.store,
						(int *)prog->argtypes.store, &prog->file_arr);
		if (!prog->commands)
			error_exit(NULL, MEM_FAIL);
		status = run_commands(prog, prog->commands);
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
