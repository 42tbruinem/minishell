/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_iostream.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 19:35:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 16:03:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <msh_io.h>

void	close_iostream(int *iostream)
{
	if (iostream[READ] != -1)
		close(iostream[READ]);
	if (iostream[WRITE] != -1)
		close(iostream[WRITE]);
}
