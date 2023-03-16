/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:00:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/16 01:56:32 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	securing_forks(t_ph *ph)
{
	struct timeval	vl;
	int				mode;

	mode = 1;
	// printf("\033[0;31m%d philo n:%d\n\033[0m", ph->ph_pos, ph->ph_pos);
	pthread_mutex_lock(&(ph->mutex[ph->ph_pos]));
	gettimeofday(&vl, 0);
	if (((ph->vl.tv_sec * 1000) + ph->vl.tv_usec) - ((vl.tv_sec * 1000) + vl.tv_usec) >= ph->time_to_die)
			return (-1);
	printf("%ld: %d has taken a fork\n", (vl.tv_sec - ph->init->tv_sec), ph->ph_pos + 1);
	if (ph->ph_pos)
	{
		// printf("\033[0;31m%d here 1 philo n:%d\n\033[0m", ph->ph_pos - 1, ph->ph_pos);
		// printf("here %d\n", ph->ph_pos - 1);
		pthread_mutex_lock(&(ph->mutex[ph->ph_pos - 1]));
		gettimeofday(&vl, 0);
		if (((ph->vl.tv_sec * 1000) + ph->vl.tv_usec) - ((vl.tv_sec * 1000) + vl.tv_usec) > ph->time_to_die)
			return (-1);
	printf("%ld: %d has taken a fork\n", (vl.tv_sec - ph->init->tv_sec), ph->ph_pos + 1);
		return (1);
	}
	else
	{
		// printf("\033[0;31m%d here 0 philo n:%d\n\033[0m", ph->ph_nb - 1, ph->ph_pos);
		pthread_mutex_lock(&(ph->mutex[ph->ph_nb - 1]));
		gettimeofday(&vl, 0);
		if (((ph->vl.tv_sec * 1000) + ph->vl.tv_usec) - ((vl.tv_sec * 1000) + vl.tv_usec) > ph->time_to_die)
			return (-1);
	printf("%ld: %d has taken a fork\n", vl.tv_sec - ph->init->tv_sec, ph->ph_pos + 1);
		return (0);
	}
}

int	ft_eat(t_ph *ph)
{
	struct timeval	vl;
	int				mode;

	mode = securing_forks(ph);
	gettimeofday(&vl, 0);
	if (mode == -1)
		return (0);
	printf("%ld: %d is eating\n", vl.tv_sec - ph->init->tv_sec, ph->ph_pos + 1);
	my_usleep(ph->time_to_eat);
	// printf("\033[0;31m%d philo n:%d\n\033[0m", ph->ph_pos, ph->ph_pos);
	pthread_mutex_unlock(&(ph->mutex[ph->ph_pos]));
	if (!mode)
	{
		// printf("\033[0;31m%d here philo n:%d\n\033[0m", ph->ph_pos - 1, ph->ph_pos);
		pthread_mutex_unlock(&(ph->mutex[ph->ph_nb - 1]));
	}
	else
	{
		// printf("\033[0;31m%d philo n:%d\n\033[0m", ph->ph_nb - 1, ph->ph_pos);
		pthread_mutex_unlock(&(ph->mutex[ph->ph_pos - 1]));
	}
	return (1);
}

void	*ft_sleep(t_ph *ph)
{
	struct timeval	vl;

	gettimeofday(&vl, 0);
	printf("%ld: %d is sleeping\n", vl.tv_sec - ph->init->tv_sec, ph->ph_pos + 1);
	my_usleep(ph->time_to_sleep);
	return (0);
}

void	*ft_routine(void *tmp)
{
	struct timeval	vl;
	t_ph			*ph;
	int				r;
	int				i;

	ph = (t_ph *)tmp;
	if (ph->ph_pos % 2)
		usleep(1000);
	i = 0;
	while (1)
	{
		gettimeofday(&(ph->vl), 0);
		r = ft_eat(ph);
		if (!r)
			ph->death = 0;
		ft_sleep(ph);
		gettimeofday(&vl, 0);
		printf("%ld: %d is thinking\n", (vl.tv_sec - ph->init->tv_sec), ph->ph_pos + 1);
	}
	return (0);
}
