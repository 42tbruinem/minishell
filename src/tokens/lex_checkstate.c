/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_checkstate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:08:08 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:09:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>

static int		normal_state(int c)
{
	if (ft_is_whitespace(c))
		return (WHITESPACE);
	if (c == '\"')
		return (INDOUBLEQUOTE);
	if (c == '\'')
		return (INSINGLEQUOTE);
	if (c == '`')
		return (INBACKTICK);
	if (c == ';')
		return (SEMICOLON);
	if (c == '>')
		return (OREDIRECT);
	if (c == '<')
		return (IREDIRECT);
	if (c == '$' || c == '~')
		return (ENV);
	if (c == '|')
		return (PIPE_PIPE);
	return (NORMAL);
}

static int		quote_state(int c, t_lexer lex)
{
	if (lex.state == INDOUBLEQUOTE && c == '\"')
		return (NORMAL);
	if (lex.state == INSINGLEQUOTE && c == '\'')
		return (NORMAL);
	if (lex.state == INBACKTICK && c == '`')
		return (NORMAL);
	return (lex.state);
}

int				lex_checkstate(int c, t_lexer lex)
{
	if (lex.state == NORMAL || lex.state == WHITESPACE)
		return (normal_state(c));
	return (quote_state(c, lex));
}
