/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/30 00:04:14 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

char	**g_termbuff;

int	run_commands(t_cmd *commands, t_var *env)
{
	while (commands)
	{
		print_command(commands);
		(void)execute(commands->args, env);
		commands = commands->next;
	}
	return (1);
}

int	msh_main(t_msh *prog)
{
	t_cmd	*commands;
	int		status;

	status = 1;
	init_readline(prog);
	while (status)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		commands = get_commands(tokenize(prog->line.cmd));
		if (!run_commands(commands, prog->env))
			break ;
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
