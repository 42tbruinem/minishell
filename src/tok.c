/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 17:15:28 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/18 15:35:03 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

typedef void (*t_escapef)(t_lexer *lex, char *last);

enum	e_tokentypes
{
	PIPE,
	TRUNC,
	APPEND,
	REDIRECT,
	ENDOFARG,
	DEFAULT,
};

void	tokprint(t_token *list)
{
	size_t				i;
	static const char	*tokentypes[] = {
	[PIPE] = "PIPE",
	[ENDOFARG] = "END_OF_ARG",
	[REDIRECT] = "<",
	[TRUNC] = "TRUNC",
	[APPEND] = "APPEND",
	[DEFAULT] = "DEFAULT"
	};

	i = 1;
	while (list)
	{
		ft_printf("token %ld = %12s | %s\n", i, list->content, tokentypes[list->type]);
		list = list->next;
		i++;
	}
}

void	tokclear(t_token *list, void (*del)(void *))
{
	t_token *clear;

	while (list)
	{
		clear = list;
		list = list->next;
		del(clear->content);
		free(clear);
	}
}

void	toksuffix(t_token **list, t_token *add)
{
	t_token	*tmp;

	if (!list)
		return ;
	tmp = *list;
	if (!tmp)
	{
		*list = add;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = add;
}

//obsolete
/*
int		get_token_type(char *tok)
{
	long long			type;
	static const char	*specialtokens[] = {
	[PIPE] = "|",
	[TRUNC] = ">",
	[APPEND] = ">>",
	[REDIRECT] = "<",
	[ENDOFARG] = ";",
	[5] = NULL,
	};

//	type = ft_str2cmpstr(specialtokens, tok);
	if (type == -1)
		return (DEFAULT);
	return (type);
}
*/

t_token	*new_tok(char *tok, size_t type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = tok;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_to_tok(t_lexer *lex, char *last, char *exception)
{
	if (!ft_strchr(exception, *lex->raw))
	{
		lex->token[lex->index] = *lex->raw;
		lex->index++;
	}
	*last = *lex->raw;
	lex->raw++;
}

void	escaper(t_lexer *lex, char *last)
{
	add_to_tok(lex, last, "");
}

void	stringquote(t_lexer *lex)
{
	char	last;

	last = 0;
	lex->raw++;
	while (*lex->raw && (*lex->raw != '"' || last == '\\'))
	{
		if (last == '\\')
			escaper(lex, &last);
		else if (*(lex->raw + 1) == '\"')
			add_to_tok(lex, &last, "\\");
		else
			add_to_tok(lex, &last, "");
	}
	if (*lex->raw != '"')
	{
//		parse_error;
		perror("Unterminated stringquote");
		exit(1);
	}
	lex->raw++;
}

void	literalquote(t_lexer *lex)
{
	char	last;

	last = 0;
	lex->raw++;
	while (*lex->raw && *lex->raw != '\'')
	{
		if (last == '\\')
			escaper(lex, &last);
		else
			add_to_tok(lex, &last, "\'");
	}
	if (*lex->raw != '\'')
	{
//		parse_error;
		perror("Unterminated literalquote");
		exit(1);
	}
	lex->raw++;
}

t_token	*special_tok(t_lexer *lex)
{
	char	*raw;

	raw = lex->raw;
	lex->raw++;
	if (raw[0] == '>' && raw[1] == '>')
		return (new_tok(ft_strdup(">>"), APPEND));
	if (raw[0] == '>')
		return (new_tok(ft_strdup(">"), TRUNC));
	if (raw[0] == '|')
		return (new_tok(ft_strdup("|"), PIPE));
	if (raw[0] == '<')
		return (new_tok(ft_strdup("<"), REDIRECT));
	if (raw[0] == ';')
		return (new_tok(ft_strdup(";"), ENDOFARG));
	return (NULL);
}

void	token_creation(t_lexer *lex, char *last)
{
	if (*last == '\\')
		escaper(lex, last);
	else if (*lex->raw == '"')
		stringquote(lex);
	else if (*lex->raw == '\'')
		literalquote(lex);
	else
		add_to_tok(lex, last, "\\");
}

t_token	*gen_token(char *raw)
{
	char			last;
	static t_lexer	lex;

	last = 0;
	if (raw)
		lex.raw = raw;
	lex.index = 0;
	if (ft_strchr(";|><", *lex.raw))
		return (special_tok(&lex));
	while (lex.index < MAX_TOKSIZE && *lex.raw &&
	(!ft_strchr("; |><", *lex.raw) || last == '\\'))
		token_creation(&lex, &last);
	lex.token[lex.index] = '\0';
	if (lex.index == 0 && *lex.raw != ' ')
		return (NULL);
	if (*lex.raw == ' ')
		lex.raw++;
	return ((lex.index) ?
		new_tok(ft_strdup(lex.token), DEFAULT) :
		gen_token(NULL));
}

t_token	*tokenize(char *raw)
{
	t_token	*tokens;
	t_token	*tmp;

	tokens = NULL;
	tmp = gen_token(raw);
	while (tmp)
	{
		toksuffix(&tokens, tmp);
		tmp = gen_token(NULL);
	}
	return (tokens);
}
