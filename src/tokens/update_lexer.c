/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_lexer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:18:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 17:00:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void		update_lexer(char *line, t_lexer *lex)
{
	lex->prevstate = lex->state;
	lex->state = lex_checkstate(line[lex->i], *lex);
	if (lex->prevstate == NORMAL && lex->state != NORMAL)
		lex->j = lex->i;
}
