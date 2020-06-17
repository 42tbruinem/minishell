/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_current_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 12:01:12 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:08:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <msh_lex.h>

void		env_current_process(t_lexer *lex, t_vecstr *line, t_msh *prog)
{
	pid_t		current;
	char		*pid_string;

	current = getpid();
	pid_string = ft_itoa((int)current);
	if (!pid_string)
		error_exit(prog, MEM_FAIL);
	if (vecstr_slice(line, lex->i, lex->i + 2))
		error_exit(prog, MEM_FAIL);
	if (vecstr_insert_str(line, lex->i, pid_string))
		error_exit(prog, MEM_FAIL);
	free(pid_string);
}
