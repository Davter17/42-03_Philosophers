/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:47:06 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 01:51:35 by mpico-bu         ###   ########.fr       */
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
		pthread_mutex_lock(&philo->l_fork->mutex);
		printing_routine(simulation, philo->id, 'f');
		pthread_mutex_lock(&philo->r_fork->mutex);
		printing_routine(simulation, philo->id, 'f');
		printing_routine(simulation, philo->id, 'e');
		pthread_mutex_lock(&philo->eating);
		usleep(simulation->eat_t * 1000);
		pthread_mutex_unlock(&philo->eating);
		philo->last_meal = get_time(simulation, 1);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		printing_routine(simulation, philo->id, 's');
		usleep(simulation->sleep_t * 1000);
		printing_routine(simulation, philo->id, 't');
	}
	return (NULL);
}

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;
	t_simul	*simulation;

	philo = (t_philo *)arg;
	simulation = philo->simulation;
	pthread_mutex_lock(&philo->l_fork->mutex);
	printing_routine(simulation, philo->id, 'f');
	return (NULL);
}

void	inicializate_simulation(t_simul *simulation)
{
	t_philo	*philo;
	int		i;

	philo = simulation->first_philo;
	simulation->start_time = get_time(simulation, 0);
	i = 0;
	while (i < simulation->philo_n)
	{
		philo->last_meal = get_time(simulation, 1);
		if (simulation->philo_n == 1)
			pthread_create(&philo->thread_id, NULL, routine_one_philo, philo);
		else
			pthread_create(&philo->thread_id, NULL, routine, philo);
		usleep(100);
		i++;
		philo = philo->next;
	}
	if (simulation->victory && simulation->victory != 0)
		pthread_create(&simulation->vict_id, NULL, victory_watcher, simulation);
	pthread_create(&simulation->dead_id, NULL, dead_watcher, simulation);
}
