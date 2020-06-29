/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:48:45 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/29 10:44:02 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_lex.h>

int			parse_error(char c)
{
	if (c == '\n')
		ft_printf("msh: syntax error near unexpected token `\\n'\n", c);
	else
		ft_printf("msh: syntax error near unexpected token `%c'\n", c);
	return (1);
}
