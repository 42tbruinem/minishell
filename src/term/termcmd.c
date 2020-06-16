/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termcmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:42:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 14:45:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include "libft.h"
#include "msh_term.h"

void		termcmd(char *command, int p1, int p2, int lines_affected)
{
	tputs(tgoto(tgetstr(command, NULL), p1, p2),
		lines_affected, &ft_putchar);
}
