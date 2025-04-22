/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:42:12 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 20:42:54 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

t_fork	*loading_philosopher_fork(int id, t_philo *philo, t_simul *simulation)
{
	t_fork	*new_fork;

	philo->id = id;
	philo->last_meal = 0;
	philo->meals_eaten = 0;
	philo->simulation = simulation;
	new_fork = malloc(sizeof(t_fork));
	if (!new_fork)
		return (NULL);
	pthread_mutex_init(&new_fork->mutex, NULL);
	pthread_mutex_init(&philo->eating, NULL);
	new_fork->id = id;
	philo->r_fork = new_fork;
	return (new_fork);
}

bool	loading_philosophers(t_simul *simulation)
{
	int		i;
	t_philo	*current_philo;
	t_philo	*prev_philo;
	t_fork	*new_fork;

	i = 0;
	prev_philo = NULL;
	while (++i <= simulation->philo_n)
	{
		current_philo = ft_calloc(1, sizeof(t_philo));
		if (!current_philo)
			return (0);
		if (i == 1)
			simulation->first_philo = current_philo;
		current_philo->l_fork = new_fork;
		new_fork = loading_philosopher_fork(i, current_philo, simulation);
		if (!new_fork)
			return (0);
		if (prev_philo)
			prev_philo->next = current_philo;
		prev_philo = current_philo;
	}
	current_philo->next = simulation->first_philo;
	simulation->first_philo->l_fork = new_fork;
	return (1);
}

bool	check_arguments(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(ft_atoi(argv[i]) > 0))
			return (0);
		if (i == 1 && ft_atoi(argv[i]) > 200)
			return (0);
		if (i != 1 && i != 5 && ft_atoi(argv[i]) < 60)
			return (0);
		i++;
	}
	return (1);
}

t_simul	*loading_simulation(int argc, char **argv)
{
	t_simul	*simulation;

	if (!check_arguments(argv))
		return (NULL);
	simulation = ft_calloc(1, sizeof(t_simul));
	if (!simulation)
		return (NULL);
	simulation->philo_n = ft_atoi(argv[1]);
	simulation->die_t = ft_atoi(argv[2]);
	simulation->eat_t = ft_atoi(argv[3]);
	simulation->sleep_t = ft_atoi(argv[4]);
	simulation->end_simulation = false;
	pthread_mutex_init(&simulation->print_lock, NULL);
	if (argc == 6)
		simulation->victory = ft_atoi(argv[5]);
	if (!loading_philosophers(simulation))
		return (NULL);
	pthread_mutex_init(&simulation->print_lock, NULL);
	return (simulation);
}
