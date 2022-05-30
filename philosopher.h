#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_philo
{
	pthread_t	tid;
	int			num;
	int			life;
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
	int				*fork_num;
	struct timeval	start;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}		t_all;

/*
typedef struct	s_list
{
	int		*k;
	int		num;
	int		left;
	int		right;
	struct s_thread	*thread;
}		t_list;

typedef struct s_thread
{
	struct s_list	*list;
	pthread_mutex_t	*mutex;
}		t_thread;
*/

int	ft_atoi(const char *str);

#endif