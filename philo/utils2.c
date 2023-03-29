/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:23:29 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/29 01:13:52 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_ph *ph, int nb)
{
	if (ph->nb_to_eat > -1 && nb == ph->nb_to_eat)
	{
		pthread_mutex_lock(ph->eat);
		(*(ph->check))--;
		pthread_mutex_unlock(ph->eat);
	}
	return (1);
}

long	timer(struct timeval *init)
{
	long	res;

	res = (init->tv_sec * 1000) + (init->tv_usec / 1000);
	return (res);
}

int	init_struct(t_ph *ph, int ac, char **av, struct timeval *vl_init)
{
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (ft_putendl_fd("Error: Invalid argument"));
	ph->time_to_die = ft_atoi(av[2]);
	ph->time_to_eat = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		ph->nb_to_eat = ft_atoi(av[5]);
		if (ph->nb_to_eat <= 0)
			return (ft_putendl_fd("Error: Invalid argument"));
	}
	else
		ph->nb_to_eat = -1;
	ph->init = vl_init;
	return (0);
}

void	init(t_ph *ph, int ph_nb, pthread_mutex_t *m[2], int *died)
{
	int	i;

	i = 0;
	while (i < ph_nb)
	{
		(ph + i)->death = m[1];
		(ph + i)->died = died;
		(ph + i++)->mutex = m[0];
	}
}

void	init2(t_ph *ph, int *check, pthread_mutex_t *eat, int nb)
{
	int	i;

	i = 0;
	// pthread_mutex_init(eat, 0);
	i = 0;
	while (i < nb)
	{
		(ph + i)->check = check;
		(ph + i++)->eat = eat;
	}
}
