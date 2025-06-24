#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct thread_info {
	pthread_t thread_id;
	int       thread_num;
	char     *argv_string;
	struct task_struct *task;
};

struct task_struct {
	int state;				/* 1: running, 0: waiting */
	int pid;
	struct task_struct *next, *prev;
	struct thread_info tinfo;
	int num;
};

void create(void);
struct task_struct *dequeue();
void enqueue(struct task_struct *);
static void *p(void *);
void schedule(void);

int pid = 0;
int tnum = 0;

struct task_struct *run_queue;
struct task_struct *wait_queue;

#define N 5

void schedule(void) {
	if (run_queue != NULL) {
		if (run_queue->state == 1) {
			/* stop current process */
			run_queue->state = 0;

			/* place current process at top of wait queue */
			enqueue(run_queue);

			/* get current process of the run queue */
			run_queue = NULL;

			/* rotate wait queue*/
			wait_queue = wait_queue->next;
		}
	}

	/* take next one from wait queue and put it on run queue */
	run_queue = dequeue();
	/* run current process */
	run_queue->state = 1;

	return;
}

int main(int argc, char** argv) {
	int i;

	run_queue  = NULL;
	wait_queue = NULL;

	for (i=0; i<N; i++) {
		create();
	}

	/* call the scheduler every 5 min */
	while(1) {
		schedule();
		for (i=0; i<5; i++) {
			sleep(1);
		}
	}

	return 0;
}

void create(void) {
	pthread_t id;
	struct thread_info *tinfo;
	struct task_struct *task;

	tinfo = calloc(1, sizeof(struct thread_info));
	if (tinfo == NULL) {
		printf("calloc failed for tinfo");
		exit(-1);
	}
	tinfo->thread_num = tnum++;

	task = calloc(1, sizeof(struct task_struct));
	if (task == NULL) {
		printf("calloc failed for task");
		exit(-2);
	}
	task->pid = pid++;
	/* put new task on top of wait queue */
	enqueue(task);

	tinfo->task = task;

	pthread_create(&id, NULL, p, tinfo);

	return;
}

struct task_struct *dequeue() {
	struct task_struct *last, *e;

	e = wait_queue;

	if (e == wait_queue->next) {
		wait_queue = NULL;
	} else {
		last = wait_queue->prev;
		wait_queue = wait_queue->next;
		wait_queue->prev = last;
	}

	e->next = e;
	e->prev = e;

	return e;
}

void enqueue(struct task_struct *e) {
	struct task_struct *last;

	if (wait_queue == NULL) {
		wait_queue = e;
		wait_queue->prev = e;
		wait_queue->next = e;
	} else {
		last = wait_queue->prev;

		last->next = e;
		e->prev = last;
		e->next = wait_queue;
		wait_queue->prev = e;

		wait_queue = e;
	}

	return;
}

static void *p(void *arg) {
	char *uargv;
	struct thread_info *tinfo = (struct thread_info *) arg;
	struct task_struct *task = tinfo->task;

	while(1) {
		if (task->state == 1) {
	    		printf("p   %d  %d\n", tinfo->thread_num, task->state);
		}
		sleep(1);
	}

	uargv = strdup(tinfo->argv_string);

	return uargv;
}
