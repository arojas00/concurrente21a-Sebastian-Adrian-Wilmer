// Copyright 2021 Wilmer Araya Rivas <wilmer.araya@ucr.ac.cr> CC-BY-4

#ifndef QUEUESUMS_HPP
#define QUEUESUMS_HPP

#include <pthread.h>
#include <stdbool.h>

typedef struct queue_node {
  int64_t data;
  struct queue_node* next;
} queue_node_t;

typedef struct {
  pthread_mutex_t can_access_queue;
  queue_node_t* head;
  queue_node_t* tail;
} queue_t;

/**
 * ...
 * @remaks This subroutine is NOT thread-safe
 */
int queue_init(queue_t* queue);

int queue_destroy(queue_t* queue);

bool queue_is_empty(queue_t* queue);
int queue_enqueue(queue_t* queue, const int64_t data);
int queue_dequeue(queue_t* queue, int64_t* data);
void queue_clear(queue_t* queue);

#endif  // QUEUESUMS_HPP
