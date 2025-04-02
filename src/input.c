/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:02:19 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/12 00:22:25 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	limit_check(char **argv)
{
	int	j;

	j = 0;
	while (argv[j])
	{
		if (ft_atoi(argv[j]) < 0)
			return (0);
		if (ft_atoi(argv[j]) > 2147483647)
			return (0);
		j++;
	}
	return (1);
}

static bool	char_check(char **argv)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		if (argv[j][0] < '0' || argv[j][0] > '9')
			return (0);
		j++;
	}
	return (1);
}

bool	input_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	else if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0
		|| (argv[5] && ft_atoi(argv[5]) == 0))
		return (0);
	if (!char_check(argv))
		return (0);
	if (!limit_check(argv))
		return (0);
	return (1);
}
