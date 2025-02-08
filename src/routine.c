#include "philo.h"

bool    ft_eating_routine_for_one(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(sim, philo, "has taken a fork");
	usleep(sim->time_to_die * 1000 + 1000);	
	pthread_mutex_lock(&sim->stop_mutex);
	if(sim->stop)
		return(pthread_mutex_unlock(&sim->stop_mutex), pthread_mutex_unlock(philo->r_fork), NULL);
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
		if(sim->stop)
			return(pthread_mutex_unlock(&sim->stop_mutex), NULL);
		else
			pthread_mutex_unlock(&sim->stop_mutex);

		pthread_mutex_lock(&sim->tmp);
		print_log(sim, philo, "is sleeping");
		usleep(sim->time_to_sleep * 1000);
		pthread_mutex_unlock(&sim->tmp);

	}
	return (NULL);
}

bool    ft_eating_routine(t_sim *sim, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print_log(sim, philo, "has taken a fork");    
		print_log(sim, philo, "has taken a fork");
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		print_log(sim, philo, "has taken a fork");    
		print_log(sim, philo, "has taken a fork");
	}
	
	philo->meals++;
	print_log(sim, philo, "is eating");
	pthread_mutex_lock(&sim->last_meal);
	philo->last_meal = ft_time_stamp();
	pthread_mutex_unlock(&sim->last_meal);
	usleep(sim->time_to_eat * 1000);

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
	}
	pthread_mutex_unlock(&sim->full_mutex);
	pthread_mutex_unlock(philo->r_fork);
	// print_log(sim, philo, "has put down R fork");
    pthread_mutex_unlock(philo->l_fork);
	// print_log(sim, philo, "has put down L fork");
    return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int		sim_stop;
	
	philo = (t_philo *)arg;
	sim = (t_sim *)philo->sim;	
	while (1)	
	{
		pthread_mutex_lock(&sim->stop_mutex);
		sim_stop = sim->stop;
		pthread_mutex_unlock(&sim->stop_mutex);
        if(sim_stop)
            return(NULL);
        if (!ft_eating_routine(sim, philo))
            return (NULL);
		print_log(sim, philo, "is sleeping");
		usleep(sim->time_to_sleep * 1000);
		print_log(sim, philo, "is thinking");
	}
	return (NULL);
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int		i;
	long long	last;

	sim = (t_sim *)arg;
	while (1)	
	{
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
			return (pthread_mutex_unlock(&sim->stop_mutex), NULL);
		else
			pthread_mutex_unlock(&sim->stop_mutex);
		
		i = 0;
		while (i < sim->num)
		{
			philo = &sim->philos[i];
			pthread_mutex_lock(&sim->last_meal);
			last = philo->last_meal;
			pthread_mutex_unlock(&sim->last_meal);

			if ((ft_time_stamp() - last) > sim->time_to_die)
			{
				print_log(sim, philo, "died");
				pthread_mutex_lock(&sim->stop_mutex);
				sim->stop = 1;
				pthread_mutex_unlock(&sim->stop_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}