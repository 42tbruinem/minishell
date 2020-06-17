/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 11:54:12 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:53:07 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <libft.h>
#include <msh_env.h>

/*
** Functions to free up everything before exiting the program.
*/

void		error_exit(t_msh *prog, int err)
{
	env_clear(prog->env, &free);
	ft_printf_fd(2, "Error %d - ", err);
	ft_printf_fd(2, error_lookup(err));
	exit(err);
}

void		std_exit(t_msh *prog, int n)
{
	env_clear(prog->env, &free);
	exit(n);
}
