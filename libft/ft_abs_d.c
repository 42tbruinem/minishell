/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 17:16:25 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/20 17:16:47 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

double		ft_abs_d(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}