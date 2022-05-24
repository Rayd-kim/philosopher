#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval	now;
	struct timeval	after;
	double	a, b;
	printf ("abc\n");
	gettimeofday(&now, NULL);

	a = now.tv_sec + now.tv_usec * 0.000001;
	printf ("%lf\n", a);
	while (1)
	{
		gettimeofday (&after, NULL);
		b = after.tv_sec + after.tv_usec * 0.000001;
		if (b - a > 0.0001)
		{
			printf ("%ld 초 %d 마이크로초\n", now.tv_sec, now.tv_usec);
			printf ("%ld 초 %d 마이크로초\n", after.tv_sec, after.tv_usec);
			printf ("%lf\n", a);
			printf ("%lf\n", b);
			break ;
		}
	}
	printf("456\n");
	return (0);
}