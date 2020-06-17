/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_ifnot.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 19:35:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 16:03:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <msh_io.h>

void	close_ifnot(t_vec *fd_arr, int *iostream)
{
	size_t	i;
	int		*fds;

	i = 0;
	fds = (int *)fd_arr->store;
	while (i < fd_arr->index)
	{
		if (fds[i] != -1 &&
			(fds[i] != iostream[READ] && fds[i] != iostream[WRITE]))
			close(fds[i]);
		i++;
	}
}
