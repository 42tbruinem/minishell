/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_checkstate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:08:08 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/24 10:48:16 by rlucas        ########   odam.nl         */
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

static int		env_state(int c, t_lexer lex)
{
	if (c == ' ')
		return (NORMAL);
	if (c == '>')
		return (OREDIRECT);
	if (c == '<')
		return (IREDIRECT);
	if (c == ';')
		return (SEMICOLON);
	if (c == '|')
		return (PIPE_PIPE);
	if (c == '\"')
		return (INDOUBLEQUOTE);
	if (c == '\'')
		return (INSINGLEQUOTE);
	return (lex.state);
}

static int		special_state(int c, t_lexer lex)
{
	if (ft_is_whitespace(c))
		return (WHITESPACE);
	if (lex.state == SEMICOLON && c == ';')
		return (-1);
	if (lex.state == OREDIRECT && c == '>')
		return (OAPPEND);
	if (lex.state == OREDIRECT && (c == '<' || c == '|'))
		return (-1);
	if (lex.state == OREDIRECT && c != '>')
		return (NORMAL);
	if (lex.state == IREDIRECT)
		return (NORMAL);
	if (lex.state == OAPPEND && c == '>')
		return (-1);
	if (lex.state == ENV)
		return (env_state(c, lex));
	return (lex.state);
}

int				lex_checkstate(int c, t_lexer lex)
{
	if (lex.escape == 1)
	{
		if (!ft_is_whitespace(c))
		{
			if (lex.state == INDOUBLEQUOTE || lex.state == INSINGLEQUOTE)
				return (lex.state);
			return (NORMAL);
		}
		return (WHITESPACE);
	}
	if (lex.state == NORMAL || lex.state == WHITESPACE)
		return (normal_state(c));
	if (lex.state >= INDOUBLEQUOTE && lex.state <= INBACKTICK)
		return (quote_state(c, lex));
	return (special_state(c, lex));
}
