/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str3join.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:46:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 21:46:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

char		*ft_str3join(const char *s1, const char *s2, const char *s3)
{
	char		*newstr;

	if (!s1 || !s2 || !s3)
		return (NULL);
	newstr = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) +
			ft_strlen(s3) + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_strlcpy(newstr + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3) + 1);
	return (newstr);
}
