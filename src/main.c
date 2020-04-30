/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/30 14:37:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

char	**g_termbuff;

int	run_commands(t_msh *prog, t_cmd *commands, t_var *env)
{
	while (commands)
	{
		print_command(commands);
		(void)execute(prog, commands->args, env);
		commands = commands->next;
	}
	return (1);
}

/* static int	get_row2(void) */
/* { */
/* 	char		buf[8]; */
/* 	int			row; */
/*  */
/* 	ft_printf_fd(STDOUT, "\033[6n"); */
/* 	read(STDIN, buf, 8); */
/* 	row = ft_atoi(buf + 2); */
/* 	return (row); */
/* } */
/*  */

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
