/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:09:41 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 01:14:12 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool	check_victory(t_simul *simulation)
{
	t_philo	*philo;
	int		first_id;

	philo = simulation->first_philo;
	first_id = philo->id;
	while (philo)
	{
		if (philo->meals_eaten < simulation->victory)
			return (0);
		philo = philo->next;
		if (philo->id == first_id)
			break ;
	}
	return (1);
}

void	*victory_watcher(void *arg)
{
	t_simul	*simulation;

	simulation = (t_simul *)arg;
	while (!simulation->end_simulation)
	{
		if (check_victory(simulation))
		{
			printing_routine(simulation, 0, 'v');
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

static int	check_dead(t_simul *simulation)
{
	t_philo	*philo;
	int		first_id;
	int		time;

	philo = simulation->first_philo;
	first_id = philo->id;
	while (philo)
	{
		time = (get_time(simulation, 1)) - philo->last_meal;
		if (time >= simulation->die_t)
		{
			if (pthread_mutex_trylock(&philo->eating) == 0)
			{
				pthread_mutex_unlock(&philo->eating);
				return (philo->id);
			}
		}
		philo = philo->next;
		if (philo->id == first_id)
			break ;
	}
	return (0);
}

void	*dead_watcher(void *arg)
{
	t_simul	*simulation;
	int		dead_id;

	simulation = (t_simul *)arg;
	while (!simulation->end_simulation)
	{
		dead_id = check_dead(simulation);
		if (dead_id != 0)
		{
			printing_routine(simulation, dead_id, 'd');
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
