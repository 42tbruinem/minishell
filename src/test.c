/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 14:55:51 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 14:56:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

/*
** Functions to test code. Should be removed prior to submission.
*/

void	test_list(t_node *head)
{
	t_node	*current;
	int		i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		ft_printf("%d --- %s\n", i, (char *)current->data);
		i++;
		current = current->next;
	}
}
