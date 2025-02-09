#include "philo.h"

void	ft_cleanup(t_sim *sim)
{
	int		i;

	i = 0;
	while (i < sim->num)
		pthread_mutex_destroy(&sim->forks[i++]);
	pthread_mutex_destroy(&sim->log);
	pthread_mutex_destroy(&sim->die);
	pthread_mutex_destroy(&sim->monitor_mutex);
	pthread_mutex_destroy(&sim->meals_mutex);
	pthread_mutex_destroy(&sim->full_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->last_meal);

	free(sim->forks);
	free(sim->philos);
}

long long	ft_time_stamp(void)
{
	struct timeval time;
    gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000LL));
}

void	print_log(t_sim *sim, t_philo *philo, char *log) 
{
	pthread_mutex_lock(&sim->stop_mutex);
	if (sim->stop)
	{
		pthread_mutex_unlock(&sim->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&sim->stop_mutex);
	pthread_mutex_lock(&sim->log);
	printf("%.3lld %.3d %s\n", ft_time_stamp() - sim->start_time, philo->id, log);
	pthread_mutex_unlock(&sim->log);
}

void	ft_create_threads(t_sim *sim)
{
	int		i;

	pthread_create(&sim->monitor, NULL, &ft_monitor, sim);
	
	i = 0;
	if (sim->num == 1)
		pthread_create(&sim->philos[i].thread, NULL, &ft_routine_for_one, &sim->philos[i]);
	else
	{
		i = 0;
		while (i < sim->num && sim->num > 1)
		{
			pthread_create(&sim->philos[i].thread, NULL, &ft_routine, &sim->philos[i]);
			i++;
		}
	}
	i = 0;
	while (i < sim->num)
		pthread_join(sim->philos[i++].thread, NULL);
	pthread_join(sim->monitor, NULL);
}
