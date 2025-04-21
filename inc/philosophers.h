/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:01:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 01:56:25 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	struct s_philo	*next;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_mutex_t	eating;
	long long		last_meal;
	int				meals_eaten;
	struct s_simul	*simulation;
}	t_philo;

typedef struct s_simul
{
	int				philo_n;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				victory;
	t_philo			*first_philo;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_t		vict_id;
	pthread_t		dead_id;
	bool			end_simulation;
}	t_simul;

t_simul		*loading_simulation(int argc, char **argv);
void		inicializate_simulation(t_simul *simulation);
void		*victory_watcher(void *arg);
void		*dead_watcher(void *arg);

// PHILO UTILS //
void		free_simulation(t_simul *simulation);
void		print_simulation(t_simul *simulation);
void		printing_routine(t_simul *simulation, int id, char state);

// UTILS //
int			ft_atoi(const char *nptr);
long long	get_time(t_simul *simulation, bool actual);
void	*ft_calloc(size_t nmemb, size_t size);

#endif