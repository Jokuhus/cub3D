/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 06:58:40 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"

t_task	*create_task(void (*function)(void *), void *arg)
{
	t_task	*return_task;

	return_task = (t_task *)malloc(sizeof(t_task));
	if (return_task == 0)
		error_exit("error: cub3D: cannot allocate memory\n");
	return_task->function = function;
	return_task->arg = arg;
	return (return_task);
}

void	add_task(t_pool *pool, t_task *task)
{
	t_task_queue	*queue;

	queue = &pool->queue;
	pthread_mutex_lock(&pool->mutex);
	if (queue->size == 0)
	{
		queue->head = task;
		queue->tail = task;
	}
	else
	{
		queue->head->prev = task;
		task->next = queue->head;
		queue->head = task;
	}
	pthread_cond_signal(&pool->condition);
	pool->queue.size++;
	pthread_mutex_unlock(&pool->mutex);
}

t_task	*pop_task(t_pool *pool)
{
	t_task_queue	*queue;
	t_task			*return_task;

	queue = &pool->queue;
	return_task = queue->tail;
	if (queue->size == 0)
		return (NULL);
	else if (queue->size == 1)
	{
		queue->head = NULL;
		queue->tail = NULL;
	}
	else
	{
		queue->tail = return_task->prev;
		return_task->prev->next = NULL;
	}
	queue->size--;
	return (return_task);
}
