/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_word.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:15:21 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 14:39:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msh_term.h"

static size_t	get_start_of_word(size_t cursor, t_line *line)
{
	int		charfound;
	size_t	start_of_word;

	start_of_word = 1;
	charfound = 0;
	while (1)
	{
		if (cursor == start_of_word)
		{
			start_of_word++;
			break ;
		}
		if (vecstr_val(&line->cmd, cursor - start_of_word) != ' ' &&
			charfound == 0)
			charfound = 1;
		if (vecstr_val(&line->cmd, cursor - start_of_word) == ' ' &&
			charfound == 1)
			break ;
		start_of_word++;
	}
	return (start_of_word);
}

int				delete_word(t_line *line)
{
	size_t		cursor;
	size_t		start_of_word;

	if (line->inputrow == 0 && line->cursor.col == (int)line->promptlen)
		return (0);
	cursor = line->inputrow * line->max.col +
			line->cursor.col - line->promptlen;
	start_of_word = get_start_of_word(cursor, line);
	while (start_of_word > 1)
	{
		if (delete_char(line) == -1)
			return (-1);
		start_of_word--;
	}
	return (0);
}
