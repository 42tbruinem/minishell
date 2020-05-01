/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 19:22:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/05/01 10:58:35 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

void	print_command(t_cmd *command)
{
	size_t				i;
	static const char	*commandtypes[] = {
	[EOC] = "END_OF_COMMAND",
	[PIPE] = "PIPE",
	[APPEND] = "APPEND",
	[TRUNC] = "TRUNC",
	[IN_REDIR] = "IN_REDIR",
	[DEFAULT] = "DEFAULT"
	};

	i = 0;
	ft_printf("type: %s\n", commandtypes[command->type]);
	while (command->args[i])
	{
		ft_printf("%s%c", command->args[i], command->args[i + 1] ? ' ' : '\n');
		i++;
	}
	/* sleep(5); */
}

char	**ft_str2clear(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**populate_args(t_cmd *command, t_token **start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		command->args[i] = ft_strdup((*start)->content);
		if (!command->args[i])
		{
			(void)ft_str2clear(command->args);
			return (NULL);
		}
		i++;
		(*start) = (*start)->next;
	}
	command->args[i] = 0;
	return (command->args);
}

size_t	command_len(t_token *tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens && (tokens->type != EOC && tokens->type != PIPE))
	{
		tokens = tokens->next;
		i++;
	}
	return (i);
}

t_cmd	*new_command(t_token **start, size_t type)
{
	t_cmd	*new;
	size_t	len;

	len = command_len(*start);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = malloc(sizeof(char *) * (len + 1));
	if (!new->args)
		return (NULL);
	new->next = NULL;
	if (!new->args)
	{
		free(new);
		return (NULL);
	}
	if (!populate_args(new, start, len))
		return (NULL);
	return (new);
}

t_cmd	*push_command(t_cmd **commands, t_cmd *new)
{
	t_cmd	*iter;

	if (!new)
		return (NULL);
	if (!*commands)
	{
		*commands = new;
		return (new);
	}
	iter = *commands;
	while (iter && iter->next)
		iter = iter->next;
	iter->next = new;
	return (new);
}

t_cmd	*clear_commands(t_cmd *commands)
{
	t_cmd	*iter;
	t_cmd	*del;

	iter = commands;
	while (iter)
	{
		del = iter;
		iter = iter->next;
		(void)ft_str2clear(del->args);
		free(del);
	}
	return (NULL);
}

t_cmd	*get_commands(t_token *tokens)
{
	t_cmd	*commands;
	t_token	*start;
	size_t	type;

	commands = NULL;
	start = tokens;
	if (!tokens)
		return (NULL);
	while (start)
	{
		type = start->type;
		start = (start == tokens) ? start : start->next;
		if (!start)
			break ;
		if (!push_command(&commands, new_command(&start, type)))
		{
			tokclear(tokens, &free);
			return (clear_commands(commands));
		}
	}
	tokclear(tokens, &free);
	return (commands);
}
