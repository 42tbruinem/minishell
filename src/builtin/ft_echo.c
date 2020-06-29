/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/29 13:38:16 by tbruinem      ########   odam.nl         */
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

int		ft_echo(t_msh *prog, int argc, char **argv)
{
	int	i;

	i = 1;
	(void)prog;
	while (argc >= 2 && argv[i])
	{
		if (i != 1 || ft_strncmp(argv[1], "-n", 2) != 0)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (i + 1 < argc)
				write(1, " ", 1);
		}
		i++;
	}
	if (argc == 1 || ft_strncmp(argv[1], "-n", 2) != 0)
		write(1, "\n", 1);
	return (0);
}
