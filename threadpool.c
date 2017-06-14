/**
 * threadpool.c
 *
 * This file will contain your implementation of a threadpool.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "threadpool.h"

// use this struc to record the work perform by thread
typedef struct record_t {
	void (*routine) (void*);
	void * arg;
	struct record* next;
} record_t;

// _threadpool is the internal threadpool structure that is
// cast to type "threadpool" before it given out to callers
typedef struct _threadpool_st {
    int threadsize;
    pthread_mutex_t lock_x;
    pthread_cond_t lock_x_empty;   // use to check whether is running
    pthread_cond_t lock_x_nonempty; // check wether is it not running
    pthread_t *thrd;
    int quesz; // record number of queue
    record_t* front;
    record_t* back;
    int close;
    int block;
} _threadpool;


void *worker_thread(void *args) {
    while (1) {
        // wait for a signal
        // l
        // mark itself as busy
        // run a given function
        //
    }
}


threadpool create_threadpool(int num_threads_in_pool) {
  _threadpool *pool;

  // sanity check the argument
  if ((num_threads_in_pool <= 0) || (num_threads_in_pool > MAXT_IN_POOL))
    return NULL;

  pool  = (_threadpool *) malloc(sizeof(_threadpool));
  if (pool == NULL) {
    fprintf(stderr, "Out of memory creating a new threadpool!\n");
    return NULL;
  }

  // add your code here to initialize the newly created threadpool
  pool -> thrd = (pthread_t*) malloc(sizeof(pthread_t) * num_threads_in_pool); // basically malloc the thread input size
  if(!pool -> thrd){ // check wether we sucess malloc or not
    fprintf(stderr, "Out of memory creating a new threadpool!\n");
    return NULL;
  }
  pool -> threadsize = num_threads_in_pool;
  pool -> quesz = 0;
  pool -> front = NULL;
  pool -> back = NULL;
  pool -> close = 0;
  pool -> block = 0;

  if(pthread_mutex_init(&pool -> lock_x,NULL)){ // initiallize mutex
     fprintf(stderr, "mut error!\n"); // if error print it out
	   return NULL;
  }

  if(pthread_cond_init(&(pool -> lock_x_empty),NULL)){ // inintiallize conditional var
    fprintf(stderr,"conditional var error!"); // if error print it out
    return NULL;
  }

  if(pthread_cond_init(&(pool -> lock_x_nonempty),NULL)){ // inintiallize conditional var
    fprintf(stderr,"conditional var error!"); // if error print it out
    return NULL;
  }

  for(int i = 0; i < num_threads_in_pool;i++){  // create the thread one by one using do_work function
    if(pthread_create(&(pool -> thrd[i]),NULL,worker_thread,pool)){
      fprintf(stderr, "thread create error!\n"); // check if it error in create thread print error
		  return NULL;
    }
  }

  return (threadpool) pool;
}


void dispatch(threadpool from_me, dispatch_fn dispatch_to_here,
	      void *arg) {
  _threadpool *pool = (_threadpool *) from_me;

  // add your code here to dispatch a thread


}

void destroy_threadpool(threadpool destroyme) {
  _threadpool *pool = (_threadpool *) destroyme;

  // add your code here to kill a threadpool
}
