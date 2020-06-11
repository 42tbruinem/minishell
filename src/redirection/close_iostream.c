/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_iostream.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 19:35:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:42:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void	close_iostream(int *iostream)
{
	if (iostream[READ] != -1)
		close(iostream[READ]);
	if (iostream[WRITE] != -1)
		close(iostream[WRITE]);
}
