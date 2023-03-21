/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:31:42 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/21 23:15:43 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_ph *ph, struct timeval *init)
{
	struct timeval	vl;
	int				i;
	long			time;

	while (1)
	{
		i = 0;
		while (i < ph->nb)
		{
			gettimeofday(&vl, 0);
			time = convert_time(&(vl)) - convert_time(&(ph->vl));
			if (time >= ph->time_to_die)
			{
				pthread_mutex_lock(ph->death);
				(*ph->died) = 0;
				time = convert_time(&vl) - convert_time(init);
				printf("%ld: %d died\n", time, ph->pos + 1);
				return (0);
				pthread_mutex_unlock(ph->death);
			}
			i++;
		}
	}
	return (1);
}

void	create_and_wait_for_threads(pthread_t *id, int ac, char **av, t_ph *ph)
{
	struct timeval	init;
	int				i;
	int				ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	gettimeofday(&init, 0);
	while (i < ph_nb)
	{
		(ph + i)->nb = ph_nb;
		(ph + i)->pos = i;
		init_struct(ph + i, ac, av, &init);
		pthread_create(id + i, NULL, ft_routine, ph + i);
		pthread_detach(id[i]);
		i++;
	}
	usleep(200);
	if (!check_death(ph, &init))
		return ;
}

void	mutex_init_or_destroy(pthread_mutex_t *id, int fork_num, int mode)
{
	int	i;

	i = 0;
	if (mode == INIT)
	{
		while (i <= fork_num)
		{
			pthread_mutex_init(id + i, NULL);
			i++;
		}
	}
	else
	{
		while (i <= fork_num)
		{
			pthread_mutex_destroy(id + i);
			i++;
		}
	}
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

int	main(int ac, char **av)
{
	pthread_t		*id;
	t_ph			*ph;
	pthread_mutex_t	*mutex[2];
	int				ph_nb;
	int				*died;

	(void)ac;
	if (ac > 6 || ac < 5)
		ft_putendl_fd("Error: wrong number of arguments");
	ph_nb = ft_atoi(av[1]);
	if (ft_atoi(av[1]) <= 0)
		ft_putendl_fd("Error: Invalid argument");
	id = (pthread_t *)malloc(ph_nb * sizeof(pthread_t));
	ph = (t_ph *)malloc(ph_nb * sizeof(t_ph));
	mutex[0] = (pthread_mutex_t *)malloc((ph_nb) * sizeof(pthread_mutex_t));
	mutex[1] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	died = malloc(sizeof(int));
	*died = 1;
	mutex_init_or_destroy(mutex[0], ph_nb, INIT);
	pthread_mutex_init(mutex[1], 0);
	init(ph, ph_nb, mutex, died);
	create_and_wait_for_threads(id, ac, av, ph);
	mutex_init_or_destroy(mutex[0], ph_nb, DESTROY);
	pthread_mutex_destroy(mutex[1]);
}
