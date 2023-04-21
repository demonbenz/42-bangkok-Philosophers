/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 00:35:25 by otangkab          #+#    #+#             */
/*   Updated: 2023/04/20 01:24:21 by otangkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_died(t_philo *p)
{
	long int	time_s;

	pthread_mutex_lock(p->data->print_dead);
	time_s = time_stamp(p);
	if (p->data->dead == 1)
	{
		pthread_mutex_unlock(p->data->print_dead);
		return ;
	}
	printf("\033[0;31m%ld\t[%d] is died\033[0m\n", time_s, p->index);
	p->data->dead = 1;
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->data->print_dead);
}

int	check_died(t_philo *philo)
{
	struct timeval	cur_time;
	long int		current_time;

	gettimeofday(&cur_time, NULL);
	current_time = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
	if ((current_time - philo->hungry_time) > (long int)philo->data->t_die)
	{
		return (1);
	}
	return (0);
}
