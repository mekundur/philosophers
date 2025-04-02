/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:44:33 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/10 19:08:53 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
