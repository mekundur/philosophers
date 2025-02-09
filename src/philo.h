/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:29:26 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/09 20:04:25 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stdbool.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "sys/time.h"
# include "unistd.h"

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				meals;
	long long		creation_time;
	long long		last_meal;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_sim
{
	pthread_t		monitor;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals;
	int				num;
	int				full;
	int				stop;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	log;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	die;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	last_meal;

}					t_sim;

bool			    input_check(char **argv);
long long			ft_time(void);
int					ft_atoi(const char *nptr);
void				ft_cleanup(t_sim *sim);
void				print_log(t_sim *sim, t_philo *philo, char *log);
void				print_death(t_sim *sim, t_philo *philo, char *log);
void				ft_create_threads(t_sim *sim);
void				*ft_routine(void *arg);
void				*ft_routine_for_one(void *arg);
void				*ft_monitor(void *arg);

#endif
