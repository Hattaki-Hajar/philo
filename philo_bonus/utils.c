/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:36:32 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/31 22:39:09 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_ph(char **av, t_ph_b *ph, int *ph_nb)
{
	int	i;
	int	args[3];

	args[0] = ft_atoi(av[2]);
	args[1] = ft_atoi(av[3]);
	args[2] = ft_atoi(av[4]);
	if (args[0] <= 0 || args[1] <= 0 || args[2] <= 0)
	{
		ft_putendl_fd("Error: Inavlid argument");
		exit(-1);
	}
	i = 0;
	while (i < *ph_nb)
	{
		(ph + i)->ph_nb = ph_nb;
		(ph + i)->t_die = args[0];
		(ph + i)->t_eat = args[1];
		(ph + i)->t_sleep = args[2];
		(ph + i)->meals_nb = 0;
		i++;
	}
}

void	ft_init(int ac, char **av, t_ph_b *ph)
{
	struct timeval	*init;
	int				nb_eat;
	int				nb;
	int				i;

	i = 0;
	nb = ft_atoi(av[1]);
	nb_eat = 0;
	if (ac == 6)
	{
		nb_eat = ft_atoi(av[5]);
		if (nb_eat <= 0)
			exit (ft_putendl_fd("Error: Invalid argument"));
	}
	init = malloc(sizeof(struct timeval));
	gettimeofday(init, 0);
	while (i < nb)
	{
		(ph + i)->nb_eat = nb_eat;
		(ph + i)->pos = i;
		(ph + i)->init = init;
		i++;
	}
}

void	child_process(pthread_t *thread, int i, t_ph_b *ph)
{
	pthread_create(thread, 0, routine_b, ph + i);
	pthread_detach(*thread);
	check_ph(ph + i);
	exit(0);
}
