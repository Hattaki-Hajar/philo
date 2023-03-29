/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:31:42 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/29 02:15:07 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_ph *ph, struct timeval *vl, struct timeval *init)
{
	long	time;

	pthread_mutex_lock(ph->death);
	(*ph->died) = 0;
	pthread_mutex_unlock(ph->death);
	time = timer(vl) - timer(init);
	printf("%ld: %d died\n", time, ph->pos + 1);
}

int	check_death(t_ph *ph, struct timeval *init)
{
	struct timeval	vl;
	int				i;

	while (1)
	{
		i = 0;
		while (i < ph->nb)
		{
			pthread_mutex_lock((ph + i)->eat);
			if (*((ph + i)->check) <= 0)
			{
				pthread_mutex_unlock((ph + i)->eat);
				return (0);
			}
			pthread_mutex_unlock((ph + i)->eat);
			gettimeofday(&vl, 0);
			if (timer(&(vl)) - timer(&(ph->vl)) >= ph->time_to_die)
			{
				philo_died((ph + i), &vl, init);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	create_and_wait_for_threads(int ac, char **av, t_ph *ph)
{
	struct timeval	init;
	pthread_t		*id;
	int				i;
	int				ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	id = (pthread_t *)malloc(ph_nb * sizeof(pthread_t));
	gettimeofday(&init, 0);
	while (i < ph_nb)
	{
		(ph + i)->nb = ph_nb;
		(ph + i)->pos = i;
		if (init_struct(ph + i, ac, av, &init) == -1)
			return (-1);
		pthread_create(id + i, NULL, ft_routine, ph + i);
		pthread_detach(id[i]);
		i++;
	}
	usleep(200);
	free (id);
	if (!check_death(ph, &init))
		return (0);
	return (0);
}

void	mutex_init_or_destroy(t_mutex *m, int fork_num, int mode)
{
	int	i;

	i = 0;
	if (mode == INIT)
	{
		while (i < fork_num)
		{
			pthread_mutex_init(m->forks + i, 0);
			i++;
		}
		pthread_mutex_init(&(m->eat), 0);
		pthread_mutex_init(&(m->death), 0);
	}
	else if (mode == DESTROY)
	{
		pthread_mutex_destroy(&(m->eat));
		while (i < fork_num)
		{
			pthread_mutex_destroy(m->forks + i);
			i++;
			my_usleep(50);
		}
		pthread_mutex_destroy(&(m->death));
	}
}

int	main(int ac, char **av)
{
	t_ph			*ph;
	t_mutex			*m;
	int				*died;
	int				*ph_nb;

	if (ac > 6 || ac < 5)
		return (ft_putendl_fd("Error: Wrong number of arguments"));
	ph_nb = malloc(sizeof(int));
	*ph_nb = ft_atoi(av[1]);
	if (*ph_nb <= 0)
		return (ft_putendl_fd("Error: Invalid argument"));
	ph = (t_ph *)malloc(*ph_nb * sizeof(t_ph));
	m = malloc(sizeof(t_mutex));
	m->forks = malloc((*ph_nb) * sizeof(pthread_mutex_t));
	died = malloc(sizeof(int));
	*died = 1;
	mutex_init_or_destroy(m, *ph_nb, INIT);
	init2(ph, ph_nb, m, *ph_nb);
	init(ph, *ph_nb, m, died);
	if (create_and_wait_for_threads(ac, av, ph) == -1)
		return (0);
	mutex_init_or_destroy(m, ft_atoi(av[1]), DESTROY);
}
