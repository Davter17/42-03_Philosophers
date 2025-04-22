/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:19:34 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 16:49:07 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	free_simulation(t_simul *simulation)
{
	t_philo	*current_philo;
	t_philo	*next_philo;
	int		i;

	if (!simulation)
		return ;
	if (simulation ->first_philo)
	{
		current_philo = simulation->first_philo;
		i = 0;
		while (i < simulation->philo_n)
		{
			free(current_philo->r_fork);
			if (current_philo->next)
				next_philo = current_philo->next;
			free (current_philo);
			current_philo = next_philo;
			i++;
		}
	}
	free(simulation);
}

void	print_simulation(t_simul *simulation)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	current_philo = simulation->first_philo;
	while (i < simulation->philo_n)
	{
		printf("ID: %i, ", current_philo->id);
		printf("l_fork: %p, ", current_philo->l_fork);
		printf("r_fork: %p, \n", current_philo->r_fork);
		current_philo = current_philo->next;
		i++;
	}
}

void	printing_routine(t_simul *simulation, int id, char state)
{
	pthread_mutex_lock(&simulation->print_lock);
	pthread_mutex_lock(&simulation->end_lock);
	if (simulation->end_simulation)
		simulation->end_simulation = true;
	else if (state == 't')
		printf("%lld %d is thinking\n", get_time(simulation, 1), id);
	else if (state == 'f')
		printf("%lld %d has taken a fork\n", get_time(simulation, 1), id);
	else if (state == 'e')
		printf("%lld %d is eating\n", get_time(simulation, 1), id);
	else if (state == 's')
		printf("%lld %d is sleeping\n", get_time(simulation, 1), id);
	else if (state == 'd')
	{
		simulation->end_simulation = true;
		printf("%lld %d died\n", get_time(simulation, 1), id);
	}
	else if (state == 'v')
	{
		simulation->end_simulation = true;
		printf("%lld Philosophers have eaten.\n", get_time(simulation, 1));
	}
	pthread_mutex_unlock(&simulation->end_lock);
	pthread_mutex_unlock(&simulation->print_lock);
}
