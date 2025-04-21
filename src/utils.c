/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:24:39 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/22 01:56:15 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i])
		return (0);
	return (result * sign);
}

long long	get_time(t_simul *simulation, bool actual)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	if (actual)
		time -= simulation->start_time;
	return (time);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	i;

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		((unsigned char *)arr)[i] = 0;
		i++;
	}
	return (arr);
}
