/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:21:21 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/28 18:32:49 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_ph(t_ph_b *ph)
{
	struct timeval	vl;

	while (1)
	{
		gettimeofday(&vl, 0);
		sem_wait(ph->ate);
		sem_post(ph->ate);
		if (timer(&vl) - timer(&(ph->vl)) >= ph->t_die)
			exit (ph->pos + 1);
		usleep(200);
	}
}

void	wait_for_ph(pid_t *id, int nb, t_ph_b *ph)
{
	struct timeval	vl;
	long			time;
	int				status;
	int				i;
	int				j;

	i = 0;
	while(i < nb)
	{
		waitpid(id[i],&status,0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
				break;
			else
			{
				j = -1;
				while (++j < nb)
					kill(id[j], SIGKILL);
			}
		}
		i++;
	}
	if (WIFEXITED(status))
	{
		gettimeofday(&vl, 0);
		time = timer(&vl) - timer(ph->init);
		sem_wait(ph->ate);
		if (WEXITSTATUS(status) && (*(ph->ph_nb)))
			printf("%ld: %d died\n", time, WEXITSTATUS(status));
		sem_post(ph->ate);
	}
	i = -1;
	while (++i < nb)
		kill(id[i], SIGKILL);
}

sem_t	*create_process(t_ph_b *ph, pid_t *id, int nb)
{
	pthread_t		thread;
	sem_t			*forks;
	sem_t			*ate;
	int				i;

	i = -1;
	forks = sem_open("forks", O_CREAT, 0644, nb);
	ate = sem_open("ate", O_CREAT, 0644, 1);
	while (++i < nb)
	{
		(ph + i)->forks = forks;
		(ph + i)->ate = ate;
	}
	i = 0;
	while (i < nb)
	{
		id[i] = fork();
		gettimeofday(&((ph + i)->vl), 0);
		if (!id[i])
		{
			pthread_create(&thread, 0, routine_b, ph + i);
			pthread_detach(thread);
			check_ph(ph + i);
			exit(0);
		}
		i++;
	}
	wait_for_ph(id, nb, ph);
	sem_close(ate);
	return (forks);
}

int	main(int ac, char **av)
{
	pid_t	*id;
	t_ph_b	*ph;
	int		*ph_nb;
	sem_t	*forks;

	if (ac < 5 || ac > 6)
		return (ft_putendl_fd("Error: Wrong number of arguments"));
	ph_nb = malloc(sizeof(int));
	*ph_nb = ft_atoi(av[1]);
	if (*ph_nb <= 0)
		return (ft_putendl_fd("Error: Invalid argument"));
	sem_unlink("forks");
	sem_unlink("ate");
	id = (pid_t *)malloc(*ph_nb * sizeof(pid_t));
	ph = (t_ph_b *)malloc(*ph_nb * sizeof(t_ph_b));
	init_ph(av, ph, ph_nb);
	ft_init(ac, av, ph);
	forks = create_process(ph, id, *ph_nb);
	sem_close(forks);
	sem_unlink("forks");
	sem_unlink("ate");
}
