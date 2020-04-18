/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:35:55 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/18 14:07:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

void	prompt(t_msh *prog)
{
	char	*user;

	user = env_val_get("USER", prog->env);
	if (user)
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
	return (msh_main(&prog));
}
