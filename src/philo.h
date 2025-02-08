#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdbool.h"
# include "pthread.h"
# include "sys/time.h"
# include "string.h"

typedef struct s_philo
{
    pthread_t       thread;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    int             id;
    int             meals; 
    long            creation_time;
    long            last_meal;
    struct s_sim    *sim;
} t_philo;

typedef struct s_sim
{
    pthread_t       monitor;
    t_philo         *philos;
    pthread_mutex_t *forks;    
    long            sim_start_time;
    long            time_to_die;
    long            time_for_eating;
    long            time_for_sleeping;
    int             meals;   
    int             num;
    int             full;
    int             stop;
    pthread_mutex_t meals_mutex;
    pthread_mutex_t log;
    pthread_mutex_t tmp;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t full_mutex;
    pthread_mutex_t die;

} t_sim;

long	ft_time_stamp(void);
int     ft_atoi(const char *nptr);
void	ft_cleanup(t_sim *sim);
void    print_log(t_sim *sim, t_philo *philo, char *log);
void    print_death(t_sim *sim, t_philo *philo, char *log);
void    ft_create_threads(t_sim *sim);
void	*ft_routine(void *arg);
void	*ft_monitor(void *arg);


#endif
