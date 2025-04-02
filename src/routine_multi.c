/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:54:56 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/12 13:45:39 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating_routine_cont(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->full_mutex);
	if (philo->meals == sim->meals)
		sim->full++;
	pthread_mutex_unlock(&sim->full_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_eating_routine(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	print_log(sim, philo, "has taken a fork");
	print_log(sim, philo, "has taken a fork");
	pthread_mutex_lock(&sim->last_meal);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(&sim->last_meal);
	pthread_mutex_lock(&sim->meals_mutex);
	philo->meals++;
	pthread_mutex_unlock(&sim->meals_mutex);
	print_log(sim, philo, "is eating");
	custom_time(sim->time_to_eat);
	ft_eating_routine_cont(sim, philo);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		ft_eating_routine(sim, philo);
		print_log(sim, philo, "is sleeping");
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
		pthread_mutex_unlock(&sim->stop_mutex);
		custom_time(sim->time_to_sleep);
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
		pthread_mutex_unlock(&sim->stop_mutex);
		print_log(sim, philo, "is thinking");
	}
	return (NULL);
}
