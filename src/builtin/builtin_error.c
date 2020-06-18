/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_error.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:14:03 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/18 15:38:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <msh_builtin.h>
#include <errno.h>
#include <libft.h>
#include <string.h>

void			builtin_error(char **argv)
{
	int	i;

	i = 0;
	ft_printf_fd(2, "%s: ", argv[i]);
	ft_printf_fd(2, "%s: ", strerror(errno));
	ft_str2print(&argv[i + 1]);
}
