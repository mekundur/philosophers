/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:44:33 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/09 20:05:14 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sim_init(t_sim *sim, char **argv)
{
	sim->num = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->meals = ft_atoi(argv[5]);
	else
		sim->meals = 0;
	sim->start_time = ft_time();
	sim->full = 0;
	sim->stop = 0;
}

void	ft_mutex_init(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sim->num * sizeof(pthread_mutex_t));
	i = 0;
	while (i < sim->num)
		pthread_mutex_init(&sim->forks[i++], NULL);
	pthread_mutex_init(&sim->log, NULL);
	pthread_mutex_init(&sim->die, NULL);
	pthread_mutex_init(&sim->monitor_mutex, NULL);
	pthread_mutex_init(&sim->meals_mutex, NULL);
	pthread_mutex_init(&sim->full_mutex, NULL);
	pthread_mutex_init(&sim->stop_mutex, NULL);
	pthread_mutex_init(&sim->last_meal, NULL);
}

void	ft_forks_init(t_sim *sim, int i)
{
	if (sim->num == 1)
	{
		sim->philos[i].r_fork = &sim->forks[0];
		sim->philos[i].l_fork = NULL;
	}
	else if (sim->num == 2)
	{
		sim->philos[0].r_fork = &sim->forks[1];
		sim->philos[0].l_fork = &sim->forks[0];
		sim->philos[1].r_fork = &sim->forks[0];
		sim->philos[1].l_fork = &sim->forks[1];
	}
	else if (i == sim->num - 1)
	{
		sim->philos[i].r_fork = &sim->forks[0];
		sim->philos[i].l_fork = &sim->forks[i];
	}
	else
	{
		sim->philos[i].r_fork = &sim->forks[i];
		sim->philos[i].l_fork = &sim->forks[i + 1];
	}
}

void	ft_philos_init(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sim->num * sizeof(t_philo));
	i = 0;
	while (i < sim->num)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals = 0;
		sim->philos[i].creation_time = sim->start_time;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].sim = sim;
		ft_forks_init(sim, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (!input_check(argc, argv))
		return (0);
	ft_sim_init(&sim, argv);
	ft_mutex_init(&sim);
	ft_philos_init(&sim);
	ft_create_threads(&sim);
	ft_cleanup(&sim);
	return (0);
}
