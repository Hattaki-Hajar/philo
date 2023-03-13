/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:34:57 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/12 23:42:07 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_max(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(char *str)
{
	int		sign;
	size_t	n;

	sign = 1;
	n = 0;
	while (str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (str && (*str == '+' || *str == '-'))
		if (*str++ == '-')
			sign *= -1;
	while (str && (*str >= '0' && *str <= '9'))
	{
		n = n * 10 + *str++ - '0';
		if (n > 9223372036854775807)
			return (check_max(sign));
	}
	if (str && *str && (*str < '0' || *str > '9'))
		ft_putendl_fd("Error: Numeric argument required");
	return (n * sign);
}

void	ft_putendl_fd(char	*s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write (2, &s[i], 1);
		i++;
	}
	write (2, "\n", 1);
	exit (1);
}

void	my_usleep(int time)
{
	int	i;

	i = 0;
	while (i < time / 10)
	{
		usleep(10);
		i++;
	}
}
