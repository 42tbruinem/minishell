/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 20:29:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int		in_out_redirection(t_msh *prog, t_cmd *command)
{
	command->iostream[0] = -1;
	command->iostream[1] = -1;
	if (command->cmdtype == PIPEDCOMMAND)
		command->iostream[READ] = command->cmdpipe[READ];
	if (command->next && command->next->cmdtype == PIPEDCOMMAND)
		command->iostream[WRITE] = command->next->cmdpipe[WRITE];
	return (set_redirection(command, command->args,
		command->argtypes, &prog->file_arr));
}

void	collect_souls(t_msh *prog)
{
	size_t	i;

	i = 0;
	while (i < g_pid.index)
	{
		waitpid(-1, &prog->exit_status, 0);
		i++;
	}
	vec_destroy(&g_pid, NULL);
}

int		run_commands(t_msh *prog, t_cmd *commands)
{
	t_cmd	*del;

	if (!vec_new(&g_pid, sizeof(int)))
		return (0);
	while (commands)
	{
		if (!in_out_redirection(prog, commands))
			return (0);
		(void)execute(prog, commands);
		del = commands;
		commands = commands->next;
		free(del);
	}
	vec_destroy(&prog->args, NULL);
	vec_destroy(&prog->argtypes, NULL);
	close_all(&prog->file_arr);
	vec_destroy(&prog->file_arr, NULL);
	collect_souls(prog);
	return (1);
}

void	debug_commands(t_cmd *commands)
{
	size_t	i;

	ft_printf("START OF DEBUG\n");
	while (commands)
	{
		i = 0;
		while (commands->args[i])
		{
			ft_printf("%s%c", commands->args[i], (commands->args[i + 1]) ? ' ' : '\n');
			i++;
		}
		commands = commands->next;
	}
	ft_printf("END OF DEBUG\n");
}

void	refresh_prog(t_msh *prog)
{
	if (vecstr_reset(&prog->line.cmd))
		exit (-1);
}

void	msh_main(t_msh *prog)
{
	init_readline(prog);
	while (1)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL, IN_INPUT);
		prog->line.term.c_lflag |= ECHO;
		prog->line.term.c_lflag |= ICANON;
		tcsetattr(STDIN, TCSAFLUSH, &prog->line.term);
		if (!tokenizer(prog, &prog->line.cmd))
			error_exit(prog, MEM_FAIL, IN_INPUT);
		if (!run_commands(prog, prog->commands))
			error_exit(prog, MEM_FAIL, IN_INPUT);
		refresh_prog(prog);
		prog->line.term.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(STDIN, TCSAFLUSH, &prog->line.term);
		tcflush(STDIN, TCIFLUSH);
	}
}

int	main(void)
{
	t_msh	prog;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (!env_init(&prog))
		return (1);
	msh_main(&prog);
	return (0);
}
