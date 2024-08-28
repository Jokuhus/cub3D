/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_task_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 06:43:23 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/21 05:38:30 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "cub3d_bonus.h"

static void	*worker_thread(void *arg)
{
	t_pool	*pool;
	t_task	*task;

	pool = arg;
	while (1)
	{
		pthread_mutex_lock(&pool->mutex);
		while (pool->queue.size == 0 && pool->shutdown == 0)
			pthread_cond_wait(&pool->condition, &pool->mutex);
		if (pool->shutdown)
		{
			pthread_mutex_unlock(&pool->mutex);
			pthread_exit(NULL);
		}
		task = pop_task(pool);
		pthread_mutex_unlock(&pool->mutex);
		task->function(task->arg);
		pthread_mutex_lock(&pool->mutex);
		pool->task_complete++;
		pthread_cond_signal(&pool->synchronize);
		pthread_mutex_unlock(&pool->mutex);
		free(task);
	}
}

void	init_thread(t_pool *pool)
{
	int	i;

	pool->num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (pool->num_threads < 0)
		error_exit("error: cub3d: sysconf\n");
	pool->queue.size = 0;
	pool->shutdown = 0;
	pool->threads = malloc(sizeof(pthread_t) * pool->num_threads);
	if (pool->threads == 0)
		error_exit("error: cub3d: cannot allocate memory\n");
	pthread_mutex_init(&pool->mutex, NULL);
	pthread_cond_init(&pool->condition, NULL);
	pthread_cond_init(&pool->synchronize, NULL);
	i = 0;
	while (i < pool->num_threads)
	{
		pthread_create(&pool->threads[i], NULL, worker_thread, (void *)pool);
		i++;
	}
}

void	thread_pool_shutdown(t_pool *pool)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&pool->mutex);
	pool->shutdown = 1;
	pthread_mutex_unlock(&pool->mutex);
	pthread_cond_broadcast(&pool->condition);
	while (i < pool->num_threads)
	{
		pthread_join(pool->threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&pool->mutex);
	pthread_cond_destroy(&pool->condition);
	pthread_cond_destroy(&pool->synchronize);
}

void	start_wait_for_threads(t_pool *pool, int total_task)
{
	pthread_mutex_lock(&pool->mutex);
	pool->total_task = total_task;
	pool->task_complete = 0;
	pthread_mutex_unlock(&pool->mutex);
}

void	wait_for_threads(t_pool *pool)
{
	pthread_mutex_lock(&pool->mutex);
	while (pool->task_complete < pool->total_task)
		pthread_cond_wait(&pool->synchronize, &pool->mutex);
	pthread_mutex_unlock(&pool->mutex);
}
