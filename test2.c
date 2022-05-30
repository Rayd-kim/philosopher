#include "philosopher.h"

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

void	*t_funtion(void *data)
{
	t_list		*list;
	t_thread	*thread;

	list = (t_list *)data;
	thread = list->thread;
	pthread_mutex_lock(&thread->mutex[list->left]);
	pthread_mutex_lock(&thread->mutex[list->right]);
	printf ("%d 스레드가 %d 포크를 들었다.\n", list->num, list->left);
	printf ("%d 스레드가 %d 포크를 들었다.\n", list->num, list->right);
	usleep (1000 * 2000);
	pthread_mutex_unlock(&thread->mutex[list->left]);
	pthread_mutex_unlock(&thread->mutex[list->right]);
	return (0);
}

int main(void)
{
	int		n = 10;
    pthread_t	a[n];
    int			thr_id;
	int			status;
	int			b = 0;

	//memset (b, 0, sizeof(int) * n);
	t_thread	*thread = malloc(sizeof(t_thread));
	thread->mutex = malloc (sizeof(pthread_mutex_t) * n);
	thread->list = (t_list *)malloc(sizeof(t_list) * n);


	for (int i = 0; i < n; i++)
	{
		thread->list[i].num = i;
		thread->list[i].k = &b;
		thread->list[i].thread = thread;
		thread->list[i].left = i;
		thread->list[i].right = (i + 1) % n;
		pthread_mutex_init(&thread->mutex[i], NULL);
	}
	
	for (int i = 0; i < n; i++)
	{
		thr_id = pthread_create(&a[i], NULL, t_funtion, (void *)&thread->list[i]);
		usleep (50);
	}
	
	for (int i = 0; i < n; i++)
		pthread_join(a[i], (void **)&status);
	printf("program_end\n");
	return 0;
}
