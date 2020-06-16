/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:48:45 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 16:48:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int			parse_error(char c)
{
	ft_printf("msh: syntax error near unexpected token `%c'\n", c);
	return (1);
}
