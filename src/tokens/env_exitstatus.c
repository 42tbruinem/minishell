/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_exitstatus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 18:20:45 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 23:09:40 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_lex.h>

void	env_exitstatus(t_lexer *lex, t_vecstr *line, t_msh *prog)
{
	char	*number;

	number = ft_itoa(prog->exit_status);
	if (!number)
		exit(1);
	if (vecstr_slice(line, lex->i, lex->i + 2))
		error_exit(prog, MEM_FAIL);
	if (vecstr_insert_str(line, lex->i, number))
		error_exit(prog, MEM_FAIL);
	lex->i += ft_strlen(number) - 1;
	free(number);
	if (lex->state != INDOUBLEQUOTE)
		lex->state = NORMAL;
}
