/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 00:44:53 by otangkab          #+#    #+#             */
/*   Updated: 2023/04/21 16:59:03 by otangkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*routine(void *p)
{
	t_philo	*phi;

	phi = (t_philo *)p;
	while ((phi->eat_count < phi->data->t_at_eat))
	{
		if (phi->data->dead == 1)
			break ;
		f_grab_fork(phi);
		if (phi->data->dead == 1)
			break ;
		f_eat(phi);
		if (phi->data->dead == 1)
			break ;
		f_sleep(phi);
		if (phi->data->dead == 1)
			break ;
		f_think(phi);
	}
	return (0);
}

void	create_philo(t_data *data, t_philo **philo)
{
	int				i;
	struct timeval	cur_time;

	i = 0;
	while (i < data->phi_num)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return ;
		philo[i]->data = data;
		philo[i]->index = (i + 1);
		gettimeofday(&cur_time, NULL);
		philo[i]->hungry_time = (cur_time.tv_sec * 1000) + \
			(cur_time.tv_usec / 1000);
		philo[i]->eat_count = 0;
	i++;
	}
}

void	create_fork(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->phi_num)
	{
		philo[i]->r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo[i]->r_fork)
			return ;
		pthread_mutex_init(philo[i]->r_fork, NULL);
	i++;
	}
	i = 0;
	while (i < data->phi_num)
	{
		(philo[i]->l_fork) = (philo[(i + 1) % data->phi_num]->r_fork);
		i++;
	}	
}

void	create_thread(t_data *data)
{
	int			i;
	t_philo		**philo;
	pthread_t	*ph;

	philo = (t_philo **)malloc(sizeof(t_philo *) * data->phi_num);
	ph = (pthread_t *)malloc(sizeof(pthread_t) * data->phi_num);
	create_philo(data, philo);
	create_fork(data, philo);
	i = 0;
	while (i < data->phi_num)
	{
		pthread_create(&ph[i], NULL, &routine, philo[i]);
		usleep(200);
		i++;
	}
	i = 0;
	while (i < data->phi_num)
	{
		pthread_join(ph[i], NULL);
		i++;
	}
	destroy_and_free(data, philo);
	free(ph);
	free(philo);
}
