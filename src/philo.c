#include "philo.h"

void	ft_stop_sim(t_sim *sim)
{
	// t_philo	philo;
	int		i;

	i = 0;
	// while (i < sim->num)
	// {
	// 	philo = sim->philos[i];
	// 	// pthread_detach(philo.thread);
	// 	// printf("%p\n", &sim->philos[i]);
	// 	i++;
	// }

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
    // if (!table->stop_simulation)
        printf("%.3ld %.3d %s\n", ft_time_stamp() - sim->sim_start_time, philo->id, msg);
    pthread_mutex_unlock(&sim->log);
}

// bool	ft_check_meals(t_sim *sim)
// {
// 	t_philo philo;
// 	int		i;

// 	if (!sim->meals)
// 		return(true);
// 	pthread_mutex_lock(&sim->meals_mutex);		
// 	i = 0;
// 	while(i < sim->num)
// 	{
// 		philo = sim->philos[i];
// 		if (philo.meals < sim->meals)
// 			return (true);
// 		i++;
// 		pthread_mutex_unlock(&sim->meals_mutex);	
// 	}
// 	return (false);
// }

// bool	ft_starvation_check(t_sim *sim, t_philo *philo)
// {
// 	long	time;

// 	time = ft_time_stamp();
// 	if ((time - philo->last_meal) >= sim->time_to_die)
// 		return (false);
// 	return (true);
// }

void	*ft_routine(void *arg)
{
	// int	*i;
	// int	random = 0;
	// random++;
	t_philo	*philo;
	t_sim	*sim;
	long	time;
	
	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;
	// printf("philo_num: %.3d, thread_ID: %lu, %p\n", sim->count, pthread_self(), (sim->philos + sim->count - 1));
	// sim->creation_time[sim->count] = ft_time_stamp();
	// printf("%lu %d is created\n", sim->creation_time[sim->count] - sim->sim_start_time, sim->count);
	// if (!ft_starvation_check(sim, philo))
	// 	return (ft_stop_sim(sim), NULL);
	// while (ft_starvation_check(sim, philo))	
	while (1)	
	{
	// if ((sim->meals && philo->meals < sim->meals) || !sim->meals){
	time = ft_time_stamp();
	if ((time - philo->last_meal) > sim->time_to_die)
		return (NULL);
	pthread_mutex_lock(sim->philos->r_fork);
	pthread_mutex_lock(sim->philos->l_fork);
		// printf("1locked mutex:   %p by %lu\n", &sim->forks[sim->count % sim->num], pthread_self());
		// printf("2locked mutex:   %p by %lu\n", &sim->forks[(sim->count + 1) % sim->num], pthread_self());
	print_log(sim, philo, "has taken the right fork");	
	print_log(sim, philo, "has taken the left fork");
	{
	print_log(sim, philo, "is eating");
	usleep(sim->time_for_eating * 1000);
	philo->meals++;
	philo->last_meal = ft_time_stamp();
	// printf("%.3d has %d meals_eaten\n", philo->id, philo->meals);
	if (philo->meals == sim->meals){
			pthread_mutex_unlock(sim->philos->r_fork);
			pthread_mutex_unlock(sim->philos->l_fork);
			return (NULL);
	}}
	// if (!ft_check_meals(sim))
	//  	return (ft_stop_sim(sim), NULL);
		// printf("1unlocked mutex: %p by %lu\n", &sim->forks[(sim->count - 1) % sim->num], pthread_self());
		// printf("2unlocked mutex: %p by %lu\n\n", &sim->forks[(sim->count) % sim->num], pthread_self());
	pthread_mutex_unlock(sim->philos->r_fork);
	pthread_mutex_unlock(sim->philos->l_fork);
	// printf("count: %d\n", sim->count);
	
	// if (!ft_check_meals(sim))
	// 	return (ft_stop_sim(sim), NULL);
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

	// printf("RETURN_ft_create_thread\n");
}
