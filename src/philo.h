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
    // pthread_t       parent;
    t_philo         *philos;
    pthread_mutex_t *forks;    
    long            sim_start_time;
    long            time_to_die;
    long            time_for_eating;
    long            time_for_sleeping;
    int             meals;   
    int             num;
    pthread_mutex_t meals_mutex;
    pthread_mutex_t log;
    pthread_mutex_t tmp;

    int count;
    int test;
} t_sim;

void    ft_create_threads(t_sim *sim);
long	ft_time_stamp(void);
int     ft_atoi(const char *nptr);
void	ft_cleanup(t_sim *sim);

#endif
