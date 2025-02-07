#include "philo.h"

void	ft_cleanup(t_sim *sim)
{
	int		i;

	i = 0;
	while (i < sim->num)
		pthread_mutex_destroy(&sim->forks[i++]);
	pthread_mutex_destroy(&sim->log);
	pthread_mutex_destroy(&sim->tmp);
	pthread_mutex_destroy(&sim->meals_mutex);
	free(sim->forks);
	free(sim->philos);
}

long	ft_time_stamp(void)
{
	struct timeval time;
    gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_log(t_sim *sim, t_philo *philo, char *msg) 
{
    pthread_mutex_lock(&sim->log);
        printf("%.3ld %.3d %s\n", ft_time_stamp() - sim->sim_start_time, philo->id, msg);
    pthread_mutex_unlock(&sim->log);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	long	time;
	
	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;	
	while (1)	
	{
		time = ft_time_stamp();
		if ((time - philo->last_meal) > sim->time_to_die)
			return (NULL);
		pthread_mutex_lock(sim->philos->r_fork);
		pthread_mutex_lock(sim->philos->l_fork);
		print_log(sim, philo, "has taken the right fork");	
		print_log(sim, philo, "has taken the left fork");
		{
			print_log(sim, philo, "is eating");
			usleep(sim->time_for_eating * 1000);
			philo->meals++;
			philo->last_meal = ft_time_stamp();
			if (philo->meals == sim->meals)
				return (pthread_mutex_unlock(sim->philos->r_fork), pthread_mutex_unlock(sim->philos->l_fork), NULL);
		}
		pthread_mutex_unlock(sim->philos->r_fork);
		pthread_mutex_unlock(sim->philos->l_fork);

		pthread_mutex_lock(&sim->tmp);
		print_log(sim, philo, "is sleeping");	
		usleep(sim->time_for_sleeping * 1000);
		print_log(sim, philo, "is thinking");	
		pthread_mutex_unlock(&sim->tmp);
	}
	return (NULL);
}

void	ft_create_threads(t_sim *sim)
{
	int		i;

	// pthread_create(&sim->parent, NULL, &ft_sim_run, &sim);

	i = 0;
	while (i < sim->num)
	{
		pthread_create(&sim->philos[i].thread, NULL, &ft_routine, &sim->philos[i]);
		// printf("%p\n", &sim->philos[i]);
		i++;
	}

	i = 0;
	while (i < sim->num)
		pthread_join(sim->philos[i++].thread, NULL);
			
	// pthread_join(sim->parent, NULL);
}
