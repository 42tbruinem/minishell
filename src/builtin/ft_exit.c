/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:03:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <msh_builtin.h>

void	ft_exit(t_msh *prog, int argc, char **argv)
{
	int n;

	n = 0;
	if (argc == 2)
		n = ft_atoi(argv[1]);
	if (argc > 2)
	{
		ft_printf("msh: too many arguments to exit.\n");
		return ;
	}
	std_exit(prog, (n % 256));
}
