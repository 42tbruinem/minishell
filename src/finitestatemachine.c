/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finitestatemachine.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:08:08 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/07 15:53:01 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static int		normal_state(int c, t_ryanlexer lex)
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
	if (c == '>' && lex.nexttype == WRITEFILE)
		return (-1); // Parsing error
	if (c == '>')
		return (OREDIRECT);
	if (c == '<')
		return (IREDIRECT);
	if (c == '$')
		return (ENV);
	if (c == '|')
		return (PIPE_PIPE);
	return (NORMAL);
}

static int		quote_state(int c, t_ryanlexer lex)
{
	if (lex.state == INDOUBLEQUOTE && c == '\"')
		return (NORMAL);
	if (lex.state == INSINGLEQUOTE && c == '\'')
		return (NORMAL);
	if (lex.state == INBACKTICK && c == '`')
		return (NORMAL);
	return (lex.state);
}

static int		special_state(int c, t_ryanlexer lex)
{
	if (lex.state == SEMICOLON && c == ';')
		 return (-1); // Parsing error
	if (lex.state == OREDIRECT && c == '>')
		return (OAPPEND);
	if (lex.state == OREDIRECT && (c == '<' || c == '|'))
		return (-1); // Parsing error
	if (lex.state == OREDIRECT && c != '>')
		return (NORMAL);
	if (lex.state == IREDIRECT)
		return (NORMAL);
	if (lex.state == OAPPEND && c == '>')
		return (-1); // Parsing error
	if (lex.state == ENV && c == ' ')
		return (NORMAL);
	return (lex.state);
}

int				checkstate(int c, t_ryanlexer lex)
{
	if (lex.escape == 1)
		return (lex.state);
	if (lex.state == NORMAL || lex.state == WHITESPACE)
		return (normal_state(c, lex));
	if (lex.state >= INDOUBLEQUOTE && lex.state <= INBACKTICK)
		return (quote_state(c, lex));
	return (special_state(c, lex));
}
