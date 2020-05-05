/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ryantokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 23:24:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/05 23:46:44 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static int		checkstate(int c, t_ryanlexer lex)
{
	if (lex.escape == 1)
		return (lex.state);
	if (lex.state == NORMAL)
	{
		if (c == '\"')
			return (INDOUBLEQUOTE);
		if (c == '\'')
			return (INSINGLEQUOTE);
		if (c == '`')
			return (INBACKTICK);
	}
	if (lex.state == INDOUBLEQUOTE && c == '\"')
		return (NORMAL);
	if (lex.state == INSINGLEQUOTE && c == '\'')
		return (NORMAL);
	if (lex.state == INBACKTICK && c == '`')
		return (NORMAL);
	return (lex.state);
}

size_t			sum_tokens(char *line, int *state)
{
	size_t		i;
	int			inwhitespace;
	size_t		sum;
	int			escape;
	int			prevstate;

	i = 0;
	inwhitespace = 1;
	sum = 0;
	escape = 0;
	while (line[i])
	{
		prevstate = *state;
		*state = checkstate(*state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (*state != NORMAL && prevstate == NORMAL)
			sum++;
		if (!escape && !ft_is_whitespace(line[i]) && inwhitespace == 1 &&
				*state == NORMAL && prevstate == NORMAL)
		{
			sum++;
			inwhitespace = 0;
		}
		if (!escape && ft_is_whitespace(line[i]) && inwhitespace == 0 && *state
				== NORMAL)
			inwhitespace = 1;
		escape = 0;
		i++;
	}
	return (sum);
}

void		gen_tokens(int *state, char *line, t_ryantok **tokens)
{
	size_t		i;
	int			inwhitespace;
	int			escape;
	size_t		tokeni;

	i = 0;
	inwhitespace = 1;
	tokeni = 0;
	escape = 0;
	while (line[i])
	{
		*state = checkstate(*state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (*state != NORMAL)
		{
			line[i] = '\0';
			i++;
			if (!line[i])
				return ;
			(*tokens)[tokeni].value = line + i;
			tokeni++;
			*state = checkstate(*state, line[i], escape);
			while (line[i])
			{
				if (line[i] == '\\' && escape == 0)
				{
					escape = 1;
					i++;
					continue ;
				}
				*state = checkstate(*state, line[i], escape);
				if (*state == NORMAL)
					break ;
				i++;
				escape = 0;
			}
			line[i] = '\0';
		}
		else if (!ft_is_whitespace(line[i]) && inwhitespace == 1)
		{
			(*tokens)[tokeni].value = line + i;
			tokeni++;
			inwhitespace = 0;
		}
		else if (ft_is_whitespace(line[i]) && inwhitespace == 0)
		{
			line[i] = '\0';
			inwhitespace = 1;
		}
		escape = 0;
		i++;
	}
	(*tokens)[tokeni].value = NULL;
}

void		init_lexer(t_ryanlexer *lex)
{
	lex->i = 0;
	lex->j = 0;
	lex->state = NORMAL;
	lex->escape = 0;
}

void		update_lexer(char *line, t_ryanlexer *lex)
{
	lex->prevstate = lex->state;
	lex->state = checkstate(line[lex->i], lex);
}

int			check_esc_char(char *line, t_ryanlexer *lex)
{
	if (line[lex->i] == '\\' && lex->escape == 0)
	{
		lex->escape = 1;
		lex->i++;
		return (1);
	}
	return (0);
}

void		concatenate_quotes(char *line)
{
	t_ryanlexer		lex;

	init_lexer(&lex);
	while (line[lex->i])
	{
		if (check_esc_char(line, &lex))
			continue ;
		update_lexer(line, lex);
		if (lex->prevstate == NORMAL && lex->state != NORMAL)
			j = i;
		if (!escape && (line[i] == '\"' || line[i] == '\'') && state == NORMAL)
			if (line[i + 1] == '\"' || line[i + 1] == '\'')
			{
				(*ft_strchr(line + i + 2, line[i + 1])) = line[i];
				ft_memmove(line + i, line + i + 2, ft_strlen(line + i + 2));
				j = ft_strlen(line);
				line[j - 1] = '\0';
				line[j - 2] = '\0';
				i = 0;
				continue ;
			}
		escape = 0;
		i++;
	}
}

void		concatenate_non_spaces(char *line)
{
	size_t		i;
	int			state;
	int			prevstate;
	int			escape;
	size_t		j;
	unsigned char		c;

	i = 0;
	state = NORMAL;
	escape = 0;
	while (line[i])
	{
		prevstate = state;
		state = checkstate(state, line[i], escape);
		if (line[i] == '\\' && escape == 0)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (prevstate == NORMAL && state != NORMAL)
			j = i;
		if (!escape && state == NORMAL && (prevstate == INDOUBLEQUOTE ||
					prevstate == INSINGLEQUOTE))
			if (line[i + 1] && !ft_is_whitespace(line[i + 1]))
			{
				c = line[i];
				if (!ft_strchr(line + i + 1, ' '))
				{
					j = ft_strchr(line + i + 1, line[i]) - line - 1;
					ft_memmove(line + i, line + i + 1, ft_strlen(line + i + 1));
					ft_memmove(line + j, line + j + 1, ft_strlen(line + j + 1));
					j = ft_strlen(line);
					line[j - 1] = '\0';
					line[j - 2] = '\0';
					continue ;
				}
				j = ft_strchr(line + i + 1, ' ') - line - 1;
				ft_memmove(line + i, line + i + 1, j - i);
				line[j] = c;
				state = (prevstate == INDOUBLEQUOTE) ? INDOUBLEQUOTE :
					INSINGLEQUOTE;
			}
		concatenate_quotes(line);
		escape = 0;
		i++;
	}
}

void		remove_escapes(char *line)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			len = ft_strlen(line);
			ft_memmove(line + i, line + i + 1, ft_strlen(line + i + 1));
			line[len - 1] = '\0';
		}
		i++;
	}
}

void		tokenizer(char *line)
{
	int				state;
	/* size_t		i; */
	t_ryantok		*tokens;
	size_t			totaltokens;

	/* i = 0; */
	/* concatenate_quotes(line); */
	/* ft_printf("after quote concat = %s\n", line); */
	concatenate_non_spaces(line);
	ft_printf("after non-space concat = %s\n", line);
	state = NORMAL;
	totaltokens = sum_tokens(line, &state);
	ft_printf("sum = %u\n", totaltokens);
	tokens = (t_ryantok *)malloc(sizeof(t_ryantok) * (totaltokens + 1));
	state = NORMAL;
	gen_tokens(&state, line, &tokens);
	ft_printf("after token generation = %s\n", line);

	size_t		i = 0;
	while (i < totaltokens)
	{
		remove_escapes(tokens[i].value);
		ft_printf("%s\n", tokens[i].value);
		i++;
	}
}

