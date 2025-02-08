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
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->full_mutex);
	free(sim->forks);
	free(sim->philos);
}

long	ft_time_stamp(void)
{
	struct timeval time;
    gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_log(t_sim *sim, t_philo *philo, char *log) 
{

	pthread_mutex_lock(&sim->stop_mutex);
	if (sim->stop)
	{
		pthread_mutex_unlock(&sim->stop_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&sim->stop_mutex);

	pthread_mutex_lock(&sim->log);
	printf("%.3ld %.3d %s\n", ft_time_stamp() - sim->sim_start_time, philo->id, log);
	pthread_mutex_unlock(&sim->log);
}

void	ft_create_threads(t_sim *sim)
{
	int		i;

	// pthread_create(&sim->monitor, NULL, &ft_monitor, &sim);

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
	

	// pthread_join(sim->monitor, NULL);
}
