#include "philo.h"

void	ft_cleanup(t_sim *sim)
{
	int		i;

	i = 0;
	while (i < sim->num)
		pthread_mutex_destroy(&sim->forks[i++]);
	pthread_mutex_destroy(&sim->log);
	pthread_mutex_destroy(&sim->tmp);
	pthread_mutex_destroy(&sim->die);
	pthread_mutex_destroy(&sim->loop);
	pthread_mutex_destroy(&sim->meals_mutex);
	pthread_mutex_destroy(&sim->parent_mutex);
	free(sim->forks);
	free(sim->philos);
}

void print_log(t_sim *sim, t_philo *philo, char *msg) 
{
    pthread_mutex_lock(&sim->log);
	if (!sim->run)
		return ;
	printf("%.3ld %.3d %s\n", ft_time_stamp() - sim->sim_start_time, philo->id, msg);
    pthread_mutex_unlock(&sim->log);
}

void print_log_die(t_sim *sim, t_philo *philo, char *msg) 
{
    pthread_mutex_lock(&sim->die);
	printf("%.3ld %.3d %s\n", ft_time_stamp() - sim->sim_start_time, philo->id, msg);
    pthread_mutex_unlock(&sim->die);
}

void	*ft_sim_run(void *arg)
{
	t_sim	*sim;
	t_philo	*philo;
	int		i;

	sim = (t_sim *)arg;
	while (sim->run)
	{
		i = 0;
		while (i < sim->num)
		{
			philo = &sim->philos[i];
			if (ft_time_stamp() - philo->last_meal > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->parent_mutex);
				sim->run = 0;
				print_log(sim, philo, "died");
				pthread_mutex_unlock(&sim->parent_mutex);
				return (NULL);
			}
			i++;
		}
		// usleep(1000);
	}
	return (NULL);
}

long	ft_time_stamp(void)
{
	struct timeval time;
    gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	
	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;

	pthread_mutex_lock(&sim->loop);
	while (sim->run)	
	{	
		pthread_mutex_unlock(&sim->loop);
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		// if (!sim->run)
		// 	return (pthread_mutex_unlock(philo->r_fork), pthread_mutex_unlock(philo->l_fork), NULL);
		print_log(sim, philo, "has taken the right fork");	
		print_log(sim, philo, "has taken the left fork");
		{
			if (ft_time_stamp() - philo->last_meal > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->parent_mutex);
				sim->run = 0;
				print_log_die(sim, philo, "died");
				pthread_mutex_unlock(&sim->parent_mutex);
				return (NULL);
			}
			print_log(sim, philo, "is eating");
			usleep(sim->time_for_eating * 1000);
			philo->meals++;
			philo->last_meal = ft_time_stamp();
			if (philo->meals == sim->meals)
				return (pthread_mutex_unlock(philo->r_fork), pthread_mutex_unlock(philo->l_fork), NULL);
		}
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(&sim->tmp);
		// if (!sim->run)
		// 	return (pthread_mutex_unlock(&sim->tmp), NULL);
		// pthread_mutex_unlock(&sim->tmp);
		print_log(sim, philo, "is sleeping");	
		usleep(sim->time_for_sleeping * 1000);
		// pthread_mutex_lock(&sim->tmp);
		// if (!sim->run)
		// 	return (pthread_mutex_unlock(&sim->tmp), NULL);
		// pthread_mutex_unlock(&sim->tmp);
		print_log(sim, philo, "is thinking");	
		pthread_mutex_unlock(&sim->tmp);
		usleep(100);
	}
	return (NULL);
}

void	ft_create_threads(t_sim *sim)
{
	int		i;

	// pthread_create(&sim->parent, NULL, &ft_sim_run, sim);
	i = 0;
	while (i < sim->num)
	{
		pthread_create(&sim->philos[i].thread, NULL, &ft_routine, &sim->philos[i]);
		i++;
	}

	i = 0;
	while (i < sim->num)
		pthread_join(sim->philos[i++].thread, NULL);
	// pthread_join(sim->parent, NULL);
}
