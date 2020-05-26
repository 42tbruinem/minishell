/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gen_tokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 13:10:59 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/26 19:43:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static int	state_action(char *line, t_ryanlexer *lex)
{
	if (lex->state == SEMICOLON || lex->state == PIPE_PIPE)
	{
		lex->cmd_num++;
		lex->cmd_present = 0;
		lex->nexttype = COMMAND;
		if (lex->state == PIPE_PIPE)
			lex->pipe = 1;
	}
	if (lex->state == OREDIRECT)
	{
		if (lex->nexttype == WRITEFILE || lex->nexttype == APPENDFILE)
			return (1); /* Parsing error */
		if (line[lex->i + 1] == '>')
		{
			lex->nexttype = APPENDFILE;
			lex->i++;
		}
		else
			lex->nexttype = WRITEFILE;
	}
	if (lex->state == IREDIRECT)
		lex->nexttype = INPUT_SENDER;
	lex->state = WHITESPACE;
	return (0);
}

void		mash_string(char *line, size_t dest, size_t src)
{
	size_t		tail;

	tail = ft_strlen(line + src) + src - (src - dest);
	ft_memmove(line + dest, line + src, ft_strlen(line + src));
	while (line[tail])
	{
		line[tail] = '\0';
		tail++;
	}
}

char		*env_val_get_n(const char *name, t_var *env, size_t len)
{
	t_var		*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, len) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

void		insert_into_string(char **lineptr, t_ryanlexer *lex, t_msh *prog,
		char *env_value)
{
	size_t		end;
	char		*line;
	size_t		env_value_len;

	line = *lineptr;
	env_value_len = ft_strlen(env_value);
	end = ft_strlen(line + lex->i) + lex->i;
	if (end + env_value_len > prog->line.alloced_cmd)
	{
		*lineptr = ft_realloc(line, end + env_value_len);
		prog->line.alloced_cmd = end + env_value_len;
		line = *lineptr;
	}
	ft_memmove(line + lex->i + env_value_len, line + lex->i,
			ft_strlen(line + lex->i));
	ft_memmove(line + lex->i, env_value, ft_strlen(env_value));
}

void		add_env_value(char **lineptr, t_ryanlexer *lex, t_msh *prog,
		size_t env_name_len)
{
	char		*env_value;
	char		*line;

	line = *lineptr;
	env_value = env_val_get_n(line + lex->i + 1, prog->env, env_name_len);
	ft_printf("env_value = %s\n", env_value);
	ft_printf("line + lex.i = %s\n", line + lex->i);
	mash_string(line, lex->i, lex->i + env_name_len + 1);
	if (!env_value)
	{
		insert_into_string(lineptr, lex, prog, " ");
		line[lex->i] = '\0';
		return ;
	}
	else
		insert_into_string(lineptr, lex, prog, env_value);
	line = *lineptr;
	lex->i = lex->i + ft_strlen(env_value);
	ft_printf("line + lex.i = %s\n", line + lex->i);
}

size_t		env_strclen(char *line, const char *chars)
{
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			if (!line[i + 1])
				return (i + 1);
			i += 2;
			continue;
		}
		if (ft_strchr(chars, line[i]))
			return (i);
		i++;
	}
	return (i);
}

void		expand_env_value(char **lineptr, t_ryanlexer *lex, t_msh *prog)
{
	size_t		env_name_len;
	char		*line;

	line = *lineptr;
	env_name_len = env_strclen(line + lex->i + 1, " \";<>");
	if (lex->state == INDOUBLEQUOTE && ft_strclen(line + lex->i + 1, '"') <
			env_name_len)
		env_name_len = ft_strclen(line + lex->i + 1, '"');
	add_env_value(lineptr, lex, prog, env_name_len);
}

void		evaluate_env(char **lineptr, t_ryanlexer *lex, t_msh *prog)
{
	char		*line;

	line = *lineptr;
	if (!line[lex->i + 1])
		return ;
	if (line[lex->i + 1] == '(')
		(void)prog; /* Initiate subshell */
	if (line[lex->i + 1] == '$')
		(void)prog; /* Get process id of shell */
	if (ft_isalpha(line[lex->i + 1]))
		expand_env_value(lineptr, lex, prog);
}

void		quote_toks(char **lineptr, t_ryantok **tokens, t_ryanlexer *lex,
		t_msh *prog)
{
	char		*line;

	line = *lineptr;
	mash_string(line, lex->i, lex->i + 1);
	if (lex->prevstate == WHITESPACE)
		create_token((*tokens) + lex->tokeni, lex);
	while (line[lex->i])
	{
		if (check_esc_char(line, lex))
			continue ;
		if (line[lex->i] == '$' && lex->state != INSINGLEQUOTE)
		{
			evaluate_env(lineptr, lex, prog);
			continue ;
		}
		update_lexer(line, lex);
		if (lex->state == NORMAL)
			break ;
		lex->i++;
	}
	mash_string(line, lex->i, lex->i + 1);
	lex->i--;
}

void		gen_tokens(char **lineptr, t_ryantok **tokens, t_msh *prog)
{
	t_ryanlexer		lex;
	char			*line;

	init_lexer(&lex);
	line = *lineptr;
	while (line[lex.i])
	{
		if (check_esc_char(line, &lex))
			continue ;
		update_lexer(line, &lex);
		if (lex.state >= INDOUBLEQUOTE && lex.state <= INSINGLEQUOTE)
			quote_toks(lineptr, tokens, &lex, prog);
		if (lex.state >= SEMICOLON && lex.state <= PIPE_PIPE)
			if(state_action(line, &lex))
				exit(1); /* Error in parsing */
		if (lex.state != WHITESPACE && lex.prevstate == WHITESPACE)
			create_token((*tokens) + lex.tokeni, &lex);
		if (line[lex.i] == '$' && lex.state != INSINGLEQUOTE)
			evaluate_env(lineptr, &lex, prog);
		if (lex.state == WHITESPACE)
			line[lex.i] = '\0';
		lex.i++;
	}
	(*tokens)[lex.tokeni].value = NULL;
}
