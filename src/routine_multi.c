/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:54:56 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/09 19:51:00 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_eating_routine_cont(t_sim *sim, t_philo *philo)
{
	philo->meals++;
	pthread_mutex_lock(&sim->full_mutex);
	if (philo->meals == sim->meals)
	{
		sim->full++;
		if (sim->full >= sim->num)
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
		}
		pthread_mutex_unlock(&sim->full_mutex);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pthread_mutex_unlock(&sim->full_mutex);
	return (1);
}

bool	ft_eating_routine(t_sim *sim, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(100);
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print_log(sim, philo, "has taken a fork");
		print_log(sim, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		print_log(sim, philo, "has taken a fork");
		print_log(sim, philo, "has taken a fork");
	}
	pthread_mutex_lock(&sim->last_meal);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(&sim->last_meal);
	print_log(sim, philo, "is eating");
	usleep(sim->time_to_eat * 1000);
	if (!ft_eating_routine_cont(sim, philo))
		return (0);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}
// print_log(sim, philo, "has put down R fork");
// print_log(sim, philo, "has put down L fork");

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&sim->stop_mutex);
		pthread_mutex_unlock(&sim->stop_mutex);
		if (!ft_eating_routine(sim, philo))
			return (NULL);
		pthread_mutex_lock(&sim->stop_mutex);
		pthread_mutex_unlock(&sim->stop_mutex);
		print_log(sim, philo, "is sleeping");
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
		pthread_mutex_unlock(&sim->stop_mutex);
		usleep(sim->time_to_sleep * 1000);
		print_log(sim, philo, "is thinking");
	}
	return (NULL);
}

// bool	ft_check_starvation(t_sim *sim, t_philo *philo, long long last)
// {
// 	if ((ft_time() - last) > sim->time_to_die)
// 	{
// 		print_log(sim, philo, "died");
// 		pthread_mutex_lock(&sim->stop_mutex);
// 		sim->stop = 1;
// 		pthread_mutex_unlock(&sim->stop_mutex);
// 		return (0);
// 	}
// 	return (1);
// }

// void	*ft_monitor(void *arg)
// {
// 	t_philo		*philo;
// 	t_sim		*sim;
// 	int			i;
// 	long long	last;

// 	sim = (t_sim *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&sim->stop_mutex);
// 		if (sim->stop)
// 			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
// 		pthread_mutex_unlock(&sim->stop_mutex);
// 		i = 0;
// 		while (i < sim->num)
// 		{
// 			philo = &sim->philos[i];
// 			pthread_mutex_lock(&sim->last_meal);
// 			last = philo->last_meal;
// 			pthread_mutex_unlock(&sim->last_meal);
// 			if (!ft_check_starvation(sim, philo, last))
// 				return (NULL);
// 			i++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }
