/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/17 23:48:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

void	prompt(t_msh *prog)
{
	char	*user;

	user = get_env_value("USER", prog->env);
	if (user != NULL)
		ft_printf("%s:~$ ", user);
	else
		ft_printf(":~$ ");
}

int	msh_main(t_msh *prog)
{
	int		status;
	char	*input;

	status = 1;
	while (status)
	{
		prompt(prog);
		status = read_input(&input);
	}
	std_exit(prog);
	return (0);
}

int	main(void)
{
	t_msh	prog;

	env_init(&prog);
	env_print(prog.env);
//	return (msh_main(&prog));
}
