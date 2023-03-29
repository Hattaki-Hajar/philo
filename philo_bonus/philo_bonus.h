/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:22:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/29 02:46:35 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include<unistd.h>
# include<semaphore.h>
# include<signal.h>
# include"../philo/philo.h"

typedef struct s_ph_b
{
	struct timeval	*init;
	struct timeval	vl;
	sem_t			*forks;
	sem_t			*ate;
	pid_t			*id;
	int				*ph_nb;
	int				pos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
}	t_ph_b;

void	init_ph(char **av, t_ph_b *ph, int *ph_nb);
void	ft_init(int ac, char **av, t_ph_b *ph);
void	*routine_b(void *tmp);
void	check_ph(t_ph_b *ph);
void	child_process(pthread_t *thread, int i, t_ph_b *ph);

#endif