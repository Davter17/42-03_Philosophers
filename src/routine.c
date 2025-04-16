/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:47:06 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/16 03:15:21 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_simul	*simulation;

	philo = (t_philo *)arg;
	simulation = philo->simulation;
	while (!simulation->end_simulation)
	{
		printing_routine(simulation, philo->id, 't');
		pthread_mutex_lock(&philo->l_fork->mutex);
		printing_routine(simulation, philo->id, 'f');
		pthread_mutex_lock(&philo->r_fork->mutex);
		printing_routine(simulation, philo->id, 'f');
		printing_routine(simulation, philo->id, 'e');
		philo->eating = true;
		usleep(simulation->eat_t * 1000);
		philo->eating = false;
		philo->last_meal = get_time(simulation, 1);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		printing_routine(simulation, philo->id, 's');
		usleep(simulation->sleep_t * 1000);
	}
	return (NULL);
}

void	inicializate_simulation(t_simul *simulation)
{
	t_philo	*current_philo;
	int		i;

	current_philo = simulation->first_philo;
	simulation->start_time = get_time(simulation, 0);
	i = 0;
	while (i < simulation->philo_n)
	{
		current_philo->last_meal = get_time(simulation, 1);
		pthread_create(&current_philo->thread_id, NULL, routine, current_philo);
		usleep(100);
		i++;
		current_philo = current_philo->next;
	}
	pthread_create(&simulation->victory_id, NULL, victory_watcher, simulation);
	pthread_create(&simulation->dead_id, NULL, dead_watcher, simulation);
}
