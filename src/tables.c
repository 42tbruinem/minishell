/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tables.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 13:09:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/18 13:22:29 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*error_lookup(int err)
{
	static char	*error_array[20] = {
		[MEM_FAIL] = "Minishell was unable to allocate memory\n",
		[CAP_FAIL] = "Failed to initialize termcaps\n",
	};

	return (error_array[err]);
}
