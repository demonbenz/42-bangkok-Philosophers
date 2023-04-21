/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 00:21:38 by otangkab          #+#    #+#             */
/*   Updated: 2023/04/21 17:04:37 by otangkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_died_in_eat(t_philo *p)
{
	struct timeval	cur_time;
	long int		current_time;
	long int		fix_time;

	gettimeofday(&cur_time, NULL);
	current_time = ((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
	fix_time = current_time;
	while ((current_time <= (fix_time + p->data->t_eat)) && \
		(p->data->dead != 1))
	{
		usleep(200);
		if (check_died(p))
		{
			f_died(p);
			break ;
		}
		gettimeofday(&cur_time, NULL);
		current_time = ((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
	}
}

void	f_eat(t_philo *p)
{
	struct timeval	cur_time;
	long int		time_s;

	if (check_died(p))
	{
		f_died(p);
		return ;
	}
	time_s = time_stamp(p);
	printf("\033[0;32m%ld\t[%d] is eating\033[0m\n", time_s, p->index);
	check_died_in_eat(p);
	gettimeofday(&cur_time, NULL);
	p->hungry_time = ((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
	p->eat_count++;
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

void	f_sleep(t_philo *p)
{
	long int		time_s;
	long int		current_time;
	long int		fix_time;
	struct timeval	curr_t;

	time_s = time_stamp(p);
	printf("\033[0;36m%ld\t[%d] is sleeping\033[0m\n", time_s, p->index);
	gettimeofday(&curr_t, NULL);
	current_time = ((curr_t.tv_sec * 1000) + (curr_t.tv_usec / 1000));
	fix_time = current_time;
	while (current_time <= (fix_time + p->data->t_sleep) && \
		(p->data->dead != 1))
	{
		usleep(200);
		if (check_died(p))
		{
			if (p->data->dead == 1)
				break ;
			f_died(p);
			break ;
		}
		gettimeofday(&curr_t, NULL);
		current_time = ((curr_t.tv_sec * 1000) + (curr_t.tv_usec / 1000));
	}
}

void	f_think(t_philo *p)
{
	long int		time_s;

	time_s = time_stamp(p);
	printf("\033[0;35m%ld\t[%d] is thinking\033[0m\n", time_s, p->index);
}

void	f_grab_fork(t_philo *p)
{
	long int	time_s;

	if (pthread_mutex_lock(p->r_fork) != 0)
		return ;
	else
	{
		if (p->data->dead == 1)
			return ;
		time_s = time_stamp(p);
		printf("\033[0;33m%ld\t[%d] has taken a fork\033[0m\n", time_s, p->index);
	}
	if (check_died(p))
	{
		f_died(p);
		return ;
	}
	if (pthread_mutex_lock(p->l_fork) != 0)
		return ;
	else
	{
		if (p->data->dead == 1)
			return ;
		time_s = time_stamp(p);
		printf("\033[0;33m%ld\t[%d] has taken a fork\033[0m\n", time_s, p->index);
	}
}

// void	f_died(t_philo *p)
// {
// 	long int	time_s;

// 	pthread_mutex_lock(p->data->print_dead);
// 	time_s = time_stamp(p);
// 	if (p->data->dead == 1)
// 	{
// 		pthread_mutex_unlock(p->data->print_dead);
// 		return ;
// 	}
// 	printf("\033[0;31m%ld\tPhilo[%d] is died\033[0m\n", time_s, p->index);
// 	p->data->dead = 1;
// 	pthread_mutex_unlock(p->r_fork);
// 	pthread_mutex_unlock(p->l_fork);
// 	pthread_mutex_unlock(p->data->print_dead);
// }
