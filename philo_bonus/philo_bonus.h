/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:22:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/26 02:34:44 by hhattaki         ###   ########.fr       */
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
	sem_t			*forks;
	struct timeval	*init;
	pid_t			*id;
	struct timeval	vl;
	int				*ph_nb;
	int				pos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
} t_ph_b;

void	*routine_b(void *tmp);

#endif