/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sum_tokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 12:30:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/26 12:31:04 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

void	edit_string(char **line, size_t i, t_msh *prog, char *env_value)
{
	size_t		env_len;
	size_t		extension;
	size_t		tmp;

	env_len = ft_strclen((*line) + i + 1, ' ');
	if (ft_strclen((*line) + i + 1, '"') < env_len)
		env_len = ft_strclen((*line) + i + 1, '"');
	if (!env_value)
	{
		tmp = ft_strlen((*line)) - env_len;
		ft_memmove((*line) + i, (*line) + i + env_len,
				ft_strlen((*line) + i + env_len));
		line[tmp] = '\0';
	}
	else
	{
		if (ft_strlen(env_value) > env_len)
		{
			extension = ft_strlen(env_value) - env_len;
			if (ft_strlen((*line) + i) + extension > prog->line.cmd_len)
			{
				(*line) = ft_realloc((*line), prog->line.cmd_len + 100);
				prog->line.cmd_len += 100;
			}
			ft_printf("line b4 memmove: %s\n", (*line));
			ft_memmove((*line) + i + ft_strlen(env_value),
					(*line) + i + env_len + 1, ft_strlen((*line) + i + env_len));
			ft_memmove((*line) + i, env_value, ft_strlen(env_value));
			ft_printf("line after memmove: %s\n", (*line));
		}
	}
}

char	*env_val_get_n(const char *name, t_var *env, size_t len)
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

void	expand_env_value(char **line, t_msh *prog, size_t i)
{
	size_t		env_len;
	char		*env_value;

	env_len = ft_strclen((*line) + i + 1, ' ');
	if (ft_strclen((*line) + i + 1, '"') < env_len)
		env_len = ft_strclen((*line) + i + 1, '"');
	env_value = env_val_get_n((*line) + i + 1, prog->env, env_len);
	ft_printf("line in = %s\n", (*line));
	ft_printf("env_value in = %s\n", env_value);
	edit_string(line, i, prog, env_value);
}

void	evaluate_double_quotes(char **line, t_ryanlexer *lex, t_msh *prog)
{
	char		c;
	size_t		i;
	int			escape;

	if (lex->state == INSINGLEQUOTE)
		return ;
	i = lex->i + 1;
	escape = 0;
	while ((*line)[i] != '"' && escape != 1)
	{
		c = (*line)[i];
		escape = 0;
		if (c == '$')
		{
			if ((*line)[i + 1] == '(')
				(void)c; /* initiate_subshell */
			if ((*line)[i + 1] == '$')
				(void)c; /* Get process id of shell */
			if (ft_isalpha((*line)[i + 1]))
			{
				expand_env_value(line, prog, i);
				continue ;
			}
		}
		if (c == '\\')
			escape = 1;
		i++;
	}
	ft_printf("line out = %s\n", (*line));
}

size_t			sum_tokens(char **line)
{
	t_ryanlexer		lex;
	size_t			sum;

	init_lexer(&lex);
	sum = 0;
	while ((*line)[lex.i])
	{
		if (check_esc_char((*line), &lex))
			continue ;
		update_lexer((*line), &lex);
		if (lex.state == INDOUBLEQUOTE || lex.state == INSINGLEQUOTE)
		{
			sum++;
			/* evaluate_double_quotes(line, &lex, prog); */
			lex.i++;
			move_through_quote((*line), &lex);
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
