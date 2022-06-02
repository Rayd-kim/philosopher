/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:14:52 by youskim           #+#    #+#             */
/*   Updated: 2022/06/02 15:14:53 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t	tid;
	int			num;
	double		life_time;
	int			eat_time;
	int			sleep_time;
	int			eat_num;
	int			left;
	int			right;
}		t_philo;

typedef struct s_all
{
	int				num;
	int				philo_num;
	int				eat_num;
	int				life;
	int				death;
	double			start;
	pthread_mutex_t	*write;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}		t_all;

int				ft_atoi(const char *str);
pthread_mutex_t	*make_fork(t_all *all);
t_all			*make_all(int argc, char *argv[]);
int				make_philo(t_philo *p, int argc, char *argv[]);
void			check_time(double *time);
void			ft_usleep(int spend_time);
void			printf_with_time(double start, int philo, \
				char *str, t_all *all);
#endif
