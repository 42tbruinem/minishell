/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 21:52:11 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:43:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_cmd.h>

void	debug_commands(t_cmd *commands)
{
	size_t	i;

	ft_printf("START OF DEBUG\n");
	while (commands)
	{
		i = 0;
		while (commands->args[i])
		{
			ft_printf("%s%c", commands->args[i],
			(commands->args[i + 1]) ? ' ' : '\n');
			i++;
		}
		commands = commands->next;
	}
	ft_printf("END OF DEBUG\n");
}
