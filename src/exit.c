/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 11:54:12 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/15 12:44:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <libft.h>

/*
** Functions to free up everything before exiting the program.
*/

void		error_exit(t_msh *prog, int err, int stage)
{
	ft_printf_fd(2, "Error %d - ", err);
	ft_printf_fd(2, error_lookup(err));
	if (stage == PRE_ENV)
		exit(err);
	if (stage == IN_ENV || stage == IN_TERM)
		env_clear(prog->env, &free);
	exit(err);
}

void		std_exit(t_msh *prog, int n)
{
	env_clear(prog->env, &free);
	exit(n);
}
