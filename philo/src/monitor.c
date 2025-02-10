/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:51:18 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/10 18:13:58 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_starvation(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->last_meal);
	if (((ft_time() - philo->last_meal) > sim->time_to_die))
	{
		pthread_mutex_unlock(&sim->last_meal);
		print_log(sim, philo, "died");
		pthread_mutex_lock(&sim->stop_mutex);
		sim->stop = 1;
		pthread_mutex_unlock(&sim->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&sim->last_meal);
	return (1);
}

void	ft_full_check(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->meals_mutex);
	if (philo->meals == sim->meals)
	{
		pthread_mutex_unlock(&sim->meals_mutex);
		pthread_mutex_lock(&sim->full_mutex);
		if (sim->full >= sim->num)
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
		}
		pthread_mutex_unlock(&sim->full_mutex);
		return ;
	}
	pthread_mutex_unlock(&sim->meals_mutex);
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->num)
		{
			philo = &sim->philos[i];
			ft_full_check(sim, philo);
			pthread_mutex_lock(&sim->stop_mutex);
			if (sim->stop)
				return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
			pthread_mutex_unlock(&sim->stop_mutex);
			if (!ft_check_starvation(sim, philo))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
