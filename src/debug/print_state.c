/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:47:23 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 14:47:36 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void			print_state(int c, t_lexer lex)
{
	static const char	*state_table[] = {
		[NORMAL] = "NORMAL",
		[WHITESPACE] = "WHITESPACE",
		[INDOUBLEQUOTE] = "INDOUBLEQUOTE",
		[INSINGLEQUOTE] = "INSINGLEQUOTE",
		[INBACKTICK] = "INBACKTICK",
		[SEMICOLON] = "SEMICOLON",
		[OREDIRECT] = "OREDIRECT",
		[IREDIRECT] = "IREDIRECT",
		[OAPPEND] = "OAPPEND",
		[PIPE_PIPE] = "PIPE_PIPE",
		[ENV] = "ENV"
	};

	ft_printf("%c:\tnum = %d\tescape: %d\tstate: %s\n",
			c, lex.state, lex.escape, state_table[lex.state]);
}
