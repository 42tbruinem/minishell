/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/24 14:58:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <msh_builtin.h>
#include <msh_env.h>

void	ft_unset(t_msh *prog, int argc, char **argv)
{
	size_t	i;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i])
	{
		env_unset(&prog->env, argv[i]);
		i++;
	}
	env_update(prog);
}
