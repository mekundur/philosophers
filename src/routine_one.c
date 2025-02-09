/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:31:50 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/09 18:32:52 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_eating_routine_for_one(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(sim, philo, "has taken a fork");
	usleep(sim->time_to_die * 1000 + 1000);
	pthread_mutex_lock(&sim->stop_mutex);
	if (sim->stop)
	{
		pthread_mutex_unlock(&sim->stop_mutex);
		pthread_mutex_unlock(philo->r_fork);
		return (NULL);
	}
	else
		pthread_mutex_unlock(&sim->stop_mutex);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

void	*ft_routine_for_one(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;
	while (1)
	{
		print_log(sim, philo, "is thinking");
		if (!ft_eating_routine_for_one(sim, philo))
			return (NULL);
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
		else
			pthread_mutex_unlock(&sim->stop_mutex);
		print_log(sim, philo, "is sleeping");
		usleep(sim->time_to_sleep * 1000);
	}
	return (NULL);
}