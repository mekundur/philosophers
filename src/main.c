#include "philo.h"

void	ft_init(t_sim *sim, char **argv)
{
	int	i;

	sim->num = ft_atoi(argv[1]);
	// printf("num of philos: %d\n", sim->num);
	sim->time_to_die = ft_atoi(argv[2]);
	// printf("time to die: %ld\n", sim->time_to_die);
	sim->time_for_eating = ft_atoi(argv[3]);
	// printf("time to eat: %ld\n", sim->time_for_eating);
	sim->time_for_sleeping = ft_atoi(argv[4]);
	if (argv[5])
	{
		sim->meals = ft_atoi(argv[5]);
		// printf("num of meals: %d\n", sim->meals);
	}
	else
		sim->meals = 0;
	sim->sim_start_time = ft_time_stamp();
	sim->count = 0;	
	sim->test = 0;
	// printf("sim_start_time: %lu\n", sim->sim_start_time);
	// printf("count: %d\n", sim->count);
	// printf("test_num: %d\n", sim->test);
	sim->philos = malloc(sim->num * sizeof(t_philo));
	sim->forks = malloc(sim->num * sizeof(pthread_mutex_t));
	i = 0;
	pthread_mutex_init(&sim->meals_mutex, NULL);
	while (i < sim->num)
		pthread_mutex_init(&sim->forks[i++], NULL);
	pthread_mutex_init(&sim->log, NULL);
	pthread_mutex_init(&sim->tmp, NULL);
	i = 0;
	while(i < sim->num)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals = 0;
		sim->philos[i].creation_time = sim->sim_start_time;
		sim->philos[i].last_meal = sim->sim_start_time;
		sim->philos[i].r_fork = &sim->forks[(i) % sim->num];
		sim->philos[i].l_fork = &sim->forks[(i + 1) % sim->num];
		sim->philos[i].sim = sim;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	// int		i;

	if (argc < 5 || argc > 6)
		return (0);

	// printf("thread_ID: %lu\n", pthread_self());

	ft_init(&sim, argv);
	ft_create_threads(&sim);
	
	// i = 0;
	// while(i < sim.num)
	// 	printf("%p\n", &philo.philos[i++]);

	ft_stop_sim(&sim);

	// ft_cleanup(&sim);
	// printf("thread_ID: %lu\n", pthread_self());
	return (0);
}
