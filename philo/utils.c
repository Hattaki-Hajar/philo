/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:34:57 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/27 03:12:49 by hhattaki         ###   ########.fr       */
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
		return (-1);
	return (n * sign);
}

int	ft_putendl_fd(char	*s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write (2, &s[i], 1);
		i++;
	}
	write (2, "\n", 1);
	return (-1);
}

void	my_usleep(int time)
{
	struct timeval	t0;
	struct timeval	rn;

	gettimeofday(&t0, 0);
	gettimeofday(&rn, 0);
	while ((convert_time(&rn) - convert_time(&t0)) < time)
	{
		usleep(100);
		gettimeofday(&rn, 0);
	}
}

void	ft_printf(char *str, t_ph *ph)
{
	struct timeval	vl;
	long			time;

	gettimeofday(&vl, 0);
	time = convert_time(&vl) - convert_time(ph->init);
	pthread_mutex_lock(ph->death);
	pthread_mutex_lock(ph->eat);
	if ((*ph->died) && *(ph->check) > 0)
		printf("%ld: %d %s\n", time, (ph->pos + 1), str);
	pthread_mutex_unlock(ph->eat);
	pthread_mutex_unlock(ph->death);
}
