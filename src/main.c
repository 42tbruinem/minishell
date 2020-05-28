/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/28 12:48:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <fcntl.h>
#include <stdio.h>

char	**g_termbuff;

int		in_out_redirection(t_msh *prog, t_cmd *command)
{
	command->iostream[0] = -1;
	command->iostream[1] = -1;
	if (command->cmdtype == PIPEDCOMMAND)
		command->iostream[READ] = command->cmdpipe[READ];
	if (command->next && command->next->cmdtype == PIPEDCOMMAND)
		command->iostream[WRITE] = command->next->cmdpipe[WRITE];
	if (!set_redirection(command, command->args,
		command->argtypes, &prog->file_arr))
		return (0);
	return (1);
}

int		run_commands(t_msh *prog, t_cmd *commands)
{
	while (commands)
	{
		if (!in_out_redirection(prog, commands))
		{
			dprintf(2, "bieba\n");
			return (1);
		}
//		print_filearr(&prog->file_arr);
//		print_command(commands);
		(void)execute(prog, commands);
		commands = commands->next;
	}
	close_all(&prog->file_arr);
	vec_destroy(&prog->file_arr, NULL);
	return (1);
}

void	debug_commands(t_cmd *commands)
{
	size_t	i;
	size_t	cmd;

	cmd = 0;
	ft_printf("start of command debug\n");
	while (commands)
	{
		i = 0;
		while (commands->args[i])
		{
			ft_printf("%ld | %s\n", cmd, commands->args[i]);
			i++;
		}
		cmd++;
		commands = commands->next;
	}
}

int	msh_main(t_msh *prog)
{
	t_cmd	*commands;
	t_vec	args;
	t_vec	argtypes;

	init_readline(prog);
	while (1)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		tokenizer(prog, &args, &argtypes);
		commands = get_commands(&args, (int *)argtypes.store, &(prog->file_arr));
		debug_commands(commands);
		(void)run_commands(prog, commands); //change this to update the exit_status variable, for $?
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
