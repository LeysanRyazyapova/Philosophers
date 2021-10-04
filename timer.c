#include "philo.h"

void	get_time(unsigned int *time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	*time = ((unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	timestamp_ms(unsigned int start, unsigned int *time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	*time = ((unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start;
}

int	right(int n, int phil_count)
{
	return ((n + 1) % phil_count);
}

void	mysleep(unsigned int time, unsigned int start, unsigned int tts)
{
	unsigned int	new_time;

	timestamp_ms(start, &new_time);
	while (new_time - time < tts)
	{
		usleep(25);
		timestamp_ms(start, &new_time);
	}
}

void	init_philo(pthread_mutex_t *mutex, int number,
	t_philo *philo, int phil_count)
{
	int	r;

	r = right(number, phil_count);
	philo->left_fork = &mutex[number];
	philo->right_fork = &mutex[r];
	philo->num = number + 1;
}