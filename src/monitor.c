/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:51:18 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/09 19:51:34 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_starvation(t_sim *sim, t_philo *philo)
{
	long long	last;

	pthread_mutex_lock(&sim->last_meal);
	last = philo->last_meal;
	pthread_mutex_unlock(&sim->last_meal);
	if ((ft_time() - last) > sim->time_to_die)
	{
		print_log(sim, philo, "died");
		pthread_mutex_lock(&sim->stop_mutex);
		sim->stop = 1;
		pthread_mutex_unlock(&sim->stop_mutex);
		return (0);
	}
	return (1);
}

void	*ft_monitor(void *arg)
{
	t_philo		*philo;
	t_sim		*sim;
	int			i;

	sim = (t_sim *)arg;
	while (1)
	{
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
		pthread_mutex_unlock(&sim->stop_mutex);
		i = 0;
		while (i < sim->num)
		{
			philo = &sim->philos[i];
			if (!ft_check_starvation(sim, philo))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
