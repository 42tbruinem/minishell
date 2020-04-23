/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 11:54:12 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/23 23:19:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <libft.h>

/*
** Functions to free up everything before exiting the program.
*/

void		free_list(t_node *head)
{
	t_node		*current;
	t_node		*prev;

	current = head;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
		free(prev->data);
		free(prev);
	}
}

void		free_hashtable(t_env table[ENV_SIZE])
{
	size_t		i;

	i = 0;
	while (i < ENV_SIZE)
	{
		if (table[i].varname != NULL)
		{
			free(table[i].varname);
			free(table[i].value);
			table[i].varname = NULL;
		}
		i++;
	}
}

void		error_exit(t_msh *prog, int err)
{
	ft_printf_fd(2, "Error %d - ", err);
	ft_printf_fd(2, error_lookup(err));
	free_hashtable(prog->env);
	exit(err);
}

void		std_exit(t_msh *prog)
{
	free_hashtable(prog->env);
	exit(0);
}
