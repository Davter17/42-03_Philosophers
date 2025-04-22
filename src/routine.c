/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:47:06 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 14:38:27 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	routine(pthread_mutex_t *first, pthread_mutex_t *second,
			t_philo *philo, t_simul *simulation)
{
	if (&philo->l_fork->mutex < &philo->r_fork->mutex)
	{
		first = &philo->l_fork->mutex;
		second = &philo->r_fork->mutex;
	}
	else
	{
		first = &philo->r_fork->mutex;
		second = &philo->l_fork->mutex;
	}
	pthread_mutex_lock(first);
	printing_routine(simulation, philo->id, 'f');
	pthread_mutex_lock(second);
	printing_routine(simulation, philo->id, 'f');
	printing_routine(simulation, philo->id, 'e');
	pthread_mutex_lock(&philo->eating);
	usleep(simulation->eat_t * 1000);
	philo->last_meal = get_time(simulation, 1);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	printing_routine(simulation, philo->id, 's');
	usleep(simulation->sleep_t * 1000);
	printing_routine(simulation, philo->id, 't');
}

void	*routine_preparation(void *arg)
{
	t_philo			*philo;
	t_simul			*simulation;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)arg;
	simulation = philo->simulation;
	first = ft_calloc(1, sizeof(pthread_mutex_t *));
	second = ft_calloc(1, sizeof(pthread_mutex_t *));
	while (1)
	{
		pthread_mutex_lock(&simulation->end_lock);
		if (simulation->end_simulation)
		{
			pthread_mutex_unlock(&simulation->end_lock);
			break ;
		}
		pthread_mutex_unlock(&simulation->end_lock);
		routine(first, second, philo, simulation);
	}
	free(first);
	free(second);
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
			pthread_create(&philo->thread_id, NULL, routine_preparation, philo);
		usleep(100);
		i++;
		philo = philo->next;
	}
	if (simulation->victory && simulation->victory != 0)
		pthread_create(&simulation->vict_id, NULL, victory_watcher, simulation);
	pthread_create(&simulation->dead_id, NULL, dead_watcher, simulation);
}
