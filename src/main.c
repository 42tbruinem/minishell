/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/29 10:30:06 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <msh_lex.h>
#include <msh_cmd.h>
#include <msh_env.h>
#include <msh_term.h>

void		msh_main(t_msh *prog)
{
	init_readline(prog);
	prog->args.store = NULL;
	prog->argtypes.store = NULL;
	while (1)
	{
		if (read_input(prog) == -1)
			error_exit(prog, MEM_FAIL);
		if (tokenizer(prog, &prog->line.cmd))
		{
			if (!run_commands(prog, prog->commands))
				error_exit(prog, MEM_FAIL);
		}
		if (vecstr_reset(&prog->line.cmd))
			exit(1);
		if (prog->args.store)
			vec_destroy(&prog->args, NULL);
		if (prog->argtypes.store)
			vec_destroy(&prog->argtypes, NULL);
	}
}

int			main(void)
{
	t_msh	prog;

	g_siggy = 0;
	g_total_lines = 0;
	g_current_line = 0;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (!env_init(&prog))
		return (1);
	if (!pwd_set(&prog.env))
		return (1);
	msh_main(&prog);
	return (0);
}
