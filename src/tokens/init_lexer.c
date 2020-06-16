/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:18:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 17:01:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void		init_lexer(t_lexer *lex)
{
	lex->i = 0;
	lex->j = 0;
	lex->state = WHITESPACE;
	lex->escape = 0;
	lex->tokeni = 0;
	lex->nexttype = COMMAND;
	lex->cmd_present = 0;
	lex->cmd_num = 0;
	lex->pipe = 0;
}
