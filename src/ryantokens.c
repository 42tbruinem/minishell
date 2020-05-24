/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ryantokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 23:24:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/24 14:45:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void			move_through_quote(char *line, t_ryanlexer *lex)
{
	while (lex->state != NORMAL)
	{
		lex->i++;
		if (check_esc_char(line, lex))
			continue ;
		update_lexer(line, lex);
	}
}

int				determine_state(char *line, size_t i, int state)
{
	if (state != ENV)
		return (WHITESPACE);
	if (line[i + 1] && ft_is_whitespace(line[i + 1]))
		return (NORMAL);
	if (!line[i + 1])
		return (NORMAL);
	return (WHITESPACE);
}

size_t			sum_tokens(char *line)
{
	t_ryanlexer		lex;
	size_t			sum;

	init_lexer(&lex);
	sum = 0;
	while (line[lex.i])
	{
		if (check_esc_char(line, &lex))
			continue ;
		update_lexer(line, &lex);
		if (lex.state == INDOUBLEQUOTE || lex.state == INSINGLEQUOTE)
		{
			sum++;
			move_through_quote(line, &lex);
			lex.inwhitespace = 0;
		}
		if (lex.state >= SEMICOLON && lex.state <= ENV)
			lex.state = determine_state(line, lex.i, lex.state);
		if (!lex.escape && lex.state == NORMAL && lex.prevstate == WHITESPACE)
			sum++;
		lex.escape = 0;
		lex.i++;
	}
	return (sum);
}

void		add_quote_tok(char *line, t_ryantok **tokens, t_ryanlexer *lex)
{
	if (lex->nexttype == COMMAND)
	{
		if (line[lex->i] == '\'')
			lex->nexttype = CMD_SINGLEQUOTE;
		else if (line[lex->i] == '\"')
			lex->nexttype = CMD_DOUBLEQUOTE;
	}
	else
	{
		if (line[lex->i] == '\'')
			lex->nexttype = SINGLEQUOTE;
		else if (line[lex->i] == '\"')
			lex->nexttype = DOUBLEQUOTE;
	}
	line[lex->i] = '\0';
	lex->i++;
	create_token(line + lex->i, (*tokens) + lex->tokeni, lex);
	move_through_quote(line, lex);
	line[lex->i] = '\0';
	lex->i++;
}

void		add_env_tok(char *line, t_ryanlexer *lex, t_ryantok **tokens)
{
	if (!line[lex->i + 1] || ft_is_whitespace(line[lex->i + 1]))
		create_token(line + lex->i, (*tokens) + lex->tokeni, lex);
	else
	{
		if (lex->nexttype == COMMAND)
			lex->nexttype = CMD_ENV;
		else
			lex->nexttype = ENV_VALUE;
		create_token(line + lex->i + 1, (*tokens) + lex->tokeni, lex);
		while (line[lex->i] && !ft_is_whitespace(line[lex->i]) &&
				!ft_strchr("><|&", line[lex->i]))
			lex->i++;
		lex->state = WHITESPACE;
	}
}

void		state_action(char *line, t_ryanlexer *lex, t_ryantok **tokens)
{
	if (lex->state == SEMICOLON)
		lex->nexttype = COMMAND;
	if (lex->state == IREDIRECT)
		lex->nexttype = INPUT_SENDER;
	if (lex->state == OREDIRECT)
		lex->nexttype = WRITEFILE;
	if (lex->state == OAPPEND)
		lex->nexttype = APPENDFILE;
	if (lex->state == PIPE_PIPE)
		lex->nexttype = PIPEDCOMMAND;
	if (lex->state >= SEMICOLON && lex->state <= PIPE_PIPE)
		lex->state = WHITESPACE;
	if (lex->state == ENV)
		add_env_tok(line, lex, tokens);
}

void		conv_tokens(t_ryantok *tokens, t_ryanlexer lexer, t_vec *args, t_vec *types)
{
	size_t i;
	void	*nullptr;
	int		separator;

	nullptr = NULL;
	separator = SEPARATOR;
	i = 0;
	vec_new(args, sizeof(char *));
	vec_new(types, sizeof(int));
	while (i < lexer.tokeni)
	{
		if ( i && (tokens[i].type == COMMAND || tokens[i].type == PIPEDCOMMAND))
		{
			vec_add(args, &nullptr);
			vec_add(types, &separator);
		}
		vec_add(args, &tokens[i].value);
		vec_add(types, &tokens[i].type);
		i++;
	}
	vec_add(args, &nullptr);
}

void		gen_tokens(char *line, t_ryantok **tokens, t_vec *args, t_vec *types)
{
	t_ryanlexer		lex;

	init_lexer(&lex);
	while (line[lex.i])
	{
		if (check_esc_char(line, &lex))
			continue ;
		update_lexer(line, &lex);
		if (lex.state == INDOUBLEQUOTE || lex.state == INSINGLEQUOTE)
		{
			add_quote_tok(line, tokens, &lex);
			continue ;
		}
		if (lex.state >= SEMICOLON && lex.state <= ENV)
			state_action(line, &lex, tokens);
		if (lex.state == NORMAL && lex.prevstate == WHITESPACE)
			create_token(line + lex.i, (*tokens) + lex.tokeni, &lex);
		if (lex.state == WHITESPACE)
			line[lex.i] = '\0';
		lex.escape = 0;
		lex.i++;
	}
	(*tokens)[lex.tokeni].value = NULL;
	conv_tokens(*tokens, lex, args, types);
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

void		print_tokens(t_ryantok *tokens)
{
	size_t		i;
	static const char	*toktypes[] = {
		[COMMAND] = "COMMAND",
		[STANDARD] = "STANDARD",
		[WRITEFILE] = "WRITEFILE",
		[APPENDFILE] = "APPENDFILE",
		[INPUT_SENDER] = "INPUT_SENDER",
		[PIPEDCOMMAND] = "PIPEDCOMMAND",
		[ENV_VALUE] = "ENV_VALUE",
		[DOUBLEQUOTE] = "DOUBLEQUOTE",
		[SINGLEQUOTE] = "SINGLEQUOTE",
		[CMD_DOUBLEQUOTE] = "CMD_DOUBLEQUOTE",
		[CMD_SINGLEQUOTE] = "CMD_SINGLEQUOTE",
		[CMD_ENV] = "CMD_ENV"
	};

	i = 0;
	ft_printf("ID\tToken value\tType\n");
	while (tokens[i].value)
	{
		ft_printf("[%u]\t%s\t\t%s\n", i, tokens[i].value,
				toktypes[tokens[i].type]);
		i++;
	}
}

void		tokenizer(char *line, t_vec *args, t_vec *types)
{
	t_ryantok		*tokens;
	size_t			totaltokens;

	concatenate_input(line);
	totaltokens = sum_tokens(line);
	ft_printf("sum = %u\n", totaltokens);
	tokens = (t_ryantok *)malloc(sizeof(t_ryantok) * (totaltokens + 1));
	gen_tokens(line, &tokens, args, types);
	print_tokens(tokens);
}
