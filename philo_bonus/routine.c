/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:02:56 by hhattaki          #+#    #+#             */
/*   Updated: 2023/04/01 00:57:03 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_b(t_ph_b *ph)
{
	struct timeval	vl;
	long			time;

	sem_wait(ph->forks);
	gettimeofday(&vl, 0);
	time = timer(&vl) - timer(ph->init);
	printf("%ld: %d has taken a fork\n", time, ph->pos + 1);
	sem_wait(ph->forks);
	gettimeofday(&vl, 0);
	time = timer(&vl) - timer(ph->init);
	printf("%ld: %d has taken a fork\n", time, ph->pos + 1);
	gettimeofday(&(ph->vl), 0);
	time = timer(&(ph->vl)) - timer(ph->init);
	printf("%ld: %d \033[34mis eating\033[0m\n", time, ph->pos + 1);
	my_usleep(ph->t_eat);
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	sleep_b(t_ph_b *ph)
{
	struct timeval	vl;
	long			time;

	gettimeofday(&vl, 0);
	time = timer(&vl) - timer(ph->init);
	printf("%ld: %d is sleeping\n", time, ph->pos + 1);
	my_usleep(ph->t_sleep);
}

void	*routine_b(void *tmp)
{
	struct timeval	vl;
	t_ph_b			*ph;
	long			time;

	ph = (t_ph_b *)tmp;
	gettimeofday(&(ph->vl), 0);
	while (1)
	{
		eat_b(ph);
		ph->meals_nb++;
		if (ph->meals_nb >= ph->nb_eat)
			exit (0);
		sleep_b(ph);
		gettimeofday(&vl, 0);
		time = timer(&vl) - timer(ph->init);
		printf("%ld: %d is thinking\n", time, ph->pos + 1);
	}
	return (0);
}
