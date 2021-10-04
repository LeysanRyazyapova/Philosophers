#include "philo.h"
void	even_eating(t_philo *philo, unsigned int	time)
{
	pthread_mutex_lock(philo->left_fork);
	timestamp_ms(philo->all.start, &time);
	printf("%u %d has taken a left fork\n", time, philo->num);
	pthread_mutex_lock(philo->right_fork);
	timestamp_ms(philo->all.start, &time);
	printf("%u %d has taken a right fork\n", time, philo->num);
	timestamp_ms(philo->all.start, &time);
	printf("%u %d is eating\n", time, philo->num);
	philo->all.counter++;
	mysleep(time, philo->all.start, philo->all.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	odd_eating(t_philo *philo, unsigned int	time)
{
	pthread_mutex_lock(philo->right_fork);
	timestamp_ms(philo->all.start, &time);
	printf("%u %d has taken a right fork\n", time, philo->num);
	pthread_mutex_lock(philo->left_fork);
	timestamp_ms(philo->all.start, &time);
	printf("%u %d has taken a left fork\n",time, philo->num);
	timestamp_ms(philo->all.start, &time);
	printf("%u %d is eating\n", time, philo->num);
	philo->all.counter++;
	mysleep(time, philo->all.start, philo->all.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	waiting(unsigned int last_meal, unsigned int ttd,
	unsigned int start, unsigned int tte)
{
	unsigned int	new_time;

	timestamp_ms(start, &new_time);
	while (new_time - last_meal <= ttd - tte - 10)
	{
		usleep(25);
		timestamp_ms(start, &new_time);
	}
}
