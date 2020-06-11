/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tables.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 13:09:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 21:37:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*error_lookup(int err)
{
	static char	*error_array[20] = {
		[MEM_FAIL] = "Minishell was unable to allocate memory\n"
	};

	return (error_array[err]);
}
