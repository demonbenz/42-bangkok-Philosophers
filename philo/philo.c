/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:35:24 by otangkab          #+#    #+#             */
/*   Updated: 2023/04/21 20:18:29 by otangkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_and_free(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->phi_num)
	{
		pthread_mutex_destroy(philo[i]->r_fork);
		free(philo[i]->r_fork);
		free(philo[i]);
	i++;
	}
	pthread_mutex_destroy(data->print_dead);
	free(data->print_dead);
}

void	init_data(t_data *d, int argc, char **argv)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	d->phi_num = (int)my_atod(argv[1]);
	d->t_die = (int)my_atod(argv[2]);
	d->t_eat = (int)my_atod(argv[3]);
	d->t_sleep = (int)my_atod(argv[4]);
	d->t_at_eat = INT_MAX;
	if (argc == 6)
		d->t_at_eat = (int)my_atod(argv[5]);
	d->dead = 0;
	d->start_time = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
	d->print_dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(d->print_dead, NULL);
}

void	run_philo_one(t_data *data)
{
	long int	time_s;

	time_s = 0;
	printf("\033[0;35m%ld\t[%d] is thinking\033[0m\n", time_s, 1);
	printf("\033[0;33m%ld\t[%d] has taken a fork\033[0m\n", time_s, 1);
	usleep(data->t_die * 1000);
	printf("\033[0;31m%ld\t[%d] is died\033[0m\n", (long int)data->t_die, 1);
	free(data->print_dead);
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_argv(argc, argv))
		return (print_error(1));
	init_data(&data, argc, argv);
	if (check_data(&data))
		return (print_error(2));
	if (data.phi_num == 1)
	{
		run_philo_one(&data);
		return (0);
	}
	create_thread(&data);
	return (0);
}
