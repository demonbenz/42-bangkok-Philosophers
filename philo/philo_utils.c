/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:03:06 by otangkab          #+#    #+#             */
/*   Updated: 2023/04/20 00:26:52 by otangkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	my_atod(char *s)
{
	int		i;
	double	sum;

	sum = 0;
	i = 0;
	while (s[i])
	{
		sum = (sum * 10) + (s[i] - '0');
		i++;
	}
	return (sum);
}

int	check_argv(int argc, char **c)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (2);
	i = 1;
	while (c[i] != NULL)
	{
		j = 0;
		while (c[i][j] != '\0')
		{
			if (c[i][j] < '0' || c[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_data(t_data *data)
{
	if ((data->phi_num <= 0) || (data->t_die <= 0)
		|| (data->t_eat <= 0) || (data->t_sleep <= 0)
		|| (data->t_at_eat <= 0))
		return (2);
	if ((data->phi_num > 200) || (data->t_die > INT_MAX)
		|| (data->t_eat > INT_MAX) || (data->t_sleep > INT_MAX)
		|| (data->t_at_eat > INT_MAX))
		return (2);
	return (0);
}

int	print_error(int ret)
{
	if (ret == 1)
		write(2, "Error input arguement\n", 22);
	if (ret == 2)
		write(2, "Error input data(Invalid numbers.)\n", 35);
	return (ret);
}

long int	time_stamp(t_philo *p)
{
	struct timeval	cur_time;
	long int		diff;

	gettimeofday(&cur_time, NULL);
	diff = (((cur_time.tv_sec * 1000) + \
		(cur_time.tv_usec / 1000)) - (p->data->start_time));
	return (diff);
}

/*
void	print_data(t_data data)
{
	printf("Philo number\t= %d\n",data.phi_num);
	printf("Time to die\t= %d\n",data.t_die);
	printf("Time to eat\t= %d\n",data.t_eat);
	printf("Time to sleep\t= %d\n",data.t_sleep);
	printf("Number of time each philosopher must eat\t= %d\n",data.t_at_eat);
}*/
