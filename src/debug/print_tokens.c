/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:46:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:10:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <minishell.h>
#include <msh_lex.h>

void		print_tokens(t_tok *tokens)
{
	size_t				i;
	static const char	*toktypes[] = {
		[COMMAND] = "COMMAND",
		[STANDARD] = "STANDARD",
		[WRITEFILE] = "WRITEFILE",
		[APPENDFILE] = "APPENDFILE",
		[INPUT_SENDER] = "INPUT_SENDER",
		[PIPEDCOMMAND] = "PIPEDCOMMAND"
	};

	i = 0;
	ft_printf("ID\tToken value\tType\tCommand_Num\n");
	while (tokens[i].value)
	{
		if (ft_strlen(toktypes[tokens[i].type]) > 7)
			ft_printf("[%u]\t%s\t\t%s\t%d\n", i, tokens[i].value,
					toktypes[tokens[i].type],
					tokens[i].cmd_num);
		else
			ft_printf("[%u]\t%s\t\t%s\t\t%d\n", i, tokens[i].value,
					toktypes[tokens[i].type],
					tokens[i].cmd_num);
		i++;
	}
}
