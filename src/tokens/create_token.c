/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:18:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:08:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>

static void	assign_tok_type(t_tok *token, t_lexer *lex)
{
	if (lex->nexttype == COMMAND)
	{
		lex->cmd_present = 1;
		if (lex->pipe == 1)
			lex->nexttype = PIPEDCOMMAND;
		lex->pipe = 0;
	}
	token->type = lex->nexttype;
	if (lex->cmd_present == 0)
		lex->nexttype = COMMAND;
	else
		lex->nexttype = STANDARD;
}

void		create_token(t_tok *token, t_lexer *lex)
{
	token->index = lex->i;
	token->value = (char *)1;
	token->cmd_num = lex->cmd_num;
	assign_tok_type(token, lex);
	lex->tokeni++;
}
