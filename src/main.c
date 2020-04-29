/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/29 20:34:25 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

char	**g_termbuff;

int	msh_main(t_msh *prog)
{
	t_cmd	*commands;
	t_cmd	*current;
	int		status;

	status = 1;
	init_readline(prog);
	while (status)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		commands = get_commands(tokenize(prog->line.cmd));
		current = commands;
		while (current)
		{
			print_command(current);
			current = current->next;
		}
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
