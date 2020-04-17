/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:56:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/17 23:56:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_msh	prog;

	env_init(&prog);
	env_print(prog.env);
//	return (msh_main(&prog));
}
