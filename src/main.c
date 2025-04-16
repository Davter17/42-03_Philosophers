/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:07:22 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/16 01:03:21 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	wait_for_threads(t_simul *simulation)
{
	t_philo	*current;
	int		i;

	current = simulation->first_philo;
	i = 0;
	while (i < simulation->philo_n)
	{
		pthread_join(current->thread_id, NULL);
		current = current->next;
		i++;
	}
	pthread_join(simulation->dead_id, NULL);
	pthread_join(simulation->victory_id, NULL);
}

int	main(int argc, char **argv)
{
	t_simul	*simulation;

	if (argc != 5 && argc != 6)
		return (1);
	simulation = loading_simulation(argc, argv);
	if (!simulation)
		return (free_simulation(simulation), 1);
	inicializate_simulation(simulation);
	wait_for_threads(simulation);
	free_simulation(simulation);
	return (0);
}
