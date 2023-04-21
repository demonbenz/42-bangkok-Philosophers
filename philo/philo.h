/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:36:41 by otangkab          #+#    #+#             */
/*   Updated: 2023/04/20 17:54:30 by otangkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	int					phi_num;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					t_at_eat;
	int					dead;
	long int			start_time;
	pthread_mutex_t		*print_dead;
}t_data;

typedef struct s_philo
{
	int					index;
	int					eat_count;
	long int			hungry_time;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	t_data				*data;
}t_philo;

//philo.c
void	destroy_and_free(t_data *data, t_philo **philo);
void	init_data(t_data *d, int argc, char **argv);
void	run_philo_one(t_data *data);

//philo_creates.c
void	*routine(void *p);
void	create_philo(t_data *data, t_philo **philo);
void	create_fork(t_data *data, t_philo **philo);
void	create_thread(t_data *data);

//philo_actions.c
void	check_died_in_eat(t_philo *p);
void	f_eat(t_philo *p);
void	f_sleep(t_philo *p);
void	f_think(t_philo *p);
void	f_grab_fork(t_philo *p);

//philo_died.c
void	f_died(t_philo *p);
int		check_died(t_philo *philo);

//philo_utils.c
double	my_atod(char *s);
long	int	time_stamp(t_philo *p);
int		check_argv(int argc, char **c);
int		check_data(t_data *data);
int		print_error(int ret);
//void	print_data(t_data data);
#endif
